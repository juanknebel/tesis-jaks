/*
 * <one line to give the program's name and a brief idea of what it does.>
 * Copyright (C) 2013  Juan <email>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 */

#include "daoMySql.h"

bool DaoMySql::executeConsultativeQuery(std::string query)
{
	if (this->res_) {
		delete this->res_;
		this->res_ = NULL;
	}

	this->lastQueryExecute_ = query;
	bool result = true;

	try {
		this->stmt_ = this->con_->createStatement();
		this->res_ = this->stmt_->executeQuery(query);
		this->res_meta_ = this->res_->getMetaData();
		this->fields_ = this->res_meta_->getColumnCount();
	}

	catch (sql::SQLException &e) {
		this->manageException(e);
		result = false;
	}

	delete this->stmt_;
	return result;
}

bool DaoMySql::executeModifiableQuery(std::string query)
{
	if (this->res_) {
		delete this->res_;
		this->res_ = NULL;
	}

	this->lastQueryExecute_ = query;
	bool result = true;

	try {
		this->stmt_ = this->con_->createStatement();
		this->stmt_->execute(query);
	}

	catch (sql::SQLException &e) {
		this->manageException(e);
		result = false;
	}

	delete this->stmt_;
	return result;
}

void DaoMySql::manageException(sql::SQLException &e)
{
	std::stringstream error;
	this->error_.clear();
	error <<  "Error: " << e.what() << "\nMySqlErrorCode: " << e.getErrorCode() << "\nMySqlState: " << e.getSQLState() << "\n";
	this->error_ = error.str();
}

DaoMySql::~DaoMySql()
{
	this->disconnect();
}

bool DaoMySql::connect()
{
	this->res_ = NULL;
	this->stmt_ = NULL;
	this->pstmt_ = NULL;
	this->con_ = NULL;
	this->res_meta_ = NULL;

	try {
		this->driver_ = get_driver_instance();
		this->con_ = driver_->connect(this->server_, this->user_, this->password_);
		this->con_->setSchema(this->database_);
		this->isConnected_ = true;
	}

	catch (sql::SQLException &e) {
		this->manageException(e);
	}

	return this->isConnected_;
}

bool DaoMySql::disconnect()
{
	bool result = true;

	try {
		delete this->res_;
		delete this->pstmt_;
		this->con_->close();
		delete this->con_;
	}

	catch (sql::SQLException &e) {
		this->manageException(e);
		result = false;
	}

	return result;
}

bool DaoMySql::executeCustomConsultativeQuery(std::string query)
{
	return this->executeConsultativeQuery(query);
}

bool DaoMySql::executeCustomModifiableQuery(std::string query)
{
	return this->executeModifiableQuery(query);
}

bool DaoMySql::fetch()
{
	return this->res_->next();
}

std::string DaoMySql::getField(int index)
{
	return this->res_->getString(index);
}

std::string DaoMySql::getField(std::string fieldName)
{
	return this->res_->getString(fieldName);
}
