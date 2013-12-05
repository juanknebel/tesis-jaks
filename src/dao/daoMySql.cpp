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

bool DaoMySql::executeQuery(String query) {
	this->lastQueryExecute_ = query;
	DEBUG(DBG_DEBUG,"Se ejecuto la query: "<<this->lastQueryExecute_);
	if(mysql_query(this->conn_, query.c_str())) {
		this->error_ = String(mysql_error(this->conn_));
		return false;
	}
	return true;
}

bool DaoMySql::executeConsultativeQuery(String query) {
	bool wasOk = false;
	if (this->isConnected_) {
		wasOk = this->executeQuery(query);
		if (wasOk){
			this->res_ = mysql_use_result(this->conn_);
			this->fields_ = mysql_num_fields(this->res_);
		}
	}
	else {
		this->error_ = "Not connected to database";
	}
	return wasOk;
}

bool DaoMySql::executeModifiableQuery(String query) {
	bool wasOk = false;
	if (this->isConnected_) {
		wasOk = this->executeQuery(query);
	}
	else {
		this->error_ = "Not connected to database";
	}
	return wasOk;
}

DaoMySql::DaoMySql() : Dao() {
	this->conn_ = mysql_init(NULL);
	this->row_ = NULL;
	this->res_ = NULL;
}

DaoMySql::DaoMySql(String database, String user, String password, String server) : Dao(database, user, password, server) {
	this->conn_ = mysql_init(NULL);
	this->row_ = NULL;
	this->res_ = NULL;
}

DaoMySql::DaoMySql(const DaoMySql& dao) : Dao(dao.database_, dao.user_, dao.password_, dao.server_) {
	this->conn_ = mysql_init(NULL);
	this->row_ = NULL;
	this->res_ = NULL;
}
	
DaoMySql::~DaoMySql() {
	this->disconnect();
	this->row_ = NULL;
	this->res_ = NULL;
}

bool DaoMySql::connect() {
	if (!this->isConnected_) {
		if (!mysql_real_connect(this->conn_, this->server_.c_str(), 
this->user_.c_str(), this->password_.c_str(), this->database_.c_str(), 0, NULL, 
0)) {
			this->isConnected_ = false;
			this->error_ = String(mysql_error(this->conn_));
		}
		else {
			this->isConnected_ = true;
		}
	}
	return this->isConnected_;
}

bool DaoMySql::disconnect() {
	mysql_free_result(this->res_);
	mysql_close(this->conn_);
	this->init(this->database_, this->user_, this->password_, this->server_);
	return true;
}

bool DaoMySql::executeCustomConsultativeQuery(String query) {
	return this->executeConsultativeQuery(query);
}

bool DaoMySql::executeCustomModifiableQuery(String query) {
	return this->executeModifiableQuery(query);
}

const char** DaoMySql::getNextRow() {
	MYSQL_ROW row;
	if ((row = mysql_fetch_row(this->res_)) != NULL) {
		for (int i = 0; i < this->fields_; ++i) {
			this->row_ = row;
		}
		return (const_cast<const char**> (this->row_));
	}
	else {
		return NULL;
	}
}

bool DaoMySql::executeCountAllFrom(String tableName) {
	return this->executeSelectAllFromProject(tableName, "COUNT(*)");
}

bool DaoMySql::executeSelectAllFrom(String tableName) {
	return this->executeSelectAllFromProject(tableName, "*");
}

bool DaoMySql::executeSelectAllFromProject(String tableName, String fieldToProjet) {
	return this->executeSelectProjectFromWithAndConditions(tableName, fieldToProjet, 0, 0, 0);
}

bool DaoMySql::executeSelectProjectFromWithAndConditions(String tableName, String fieldToProjet,const char *fields[], const char *values[], int count) {
	String query = "SELECT " + fieldToProjet + " FROM " + tableName;
	
	if (count > 0) {
		query.append(" WHERE ");
	}
	
	for (int i = 0;i < count; ++i) {
		query.append(fields[i]);
		query.append(" = ");
		query.append(values[i]);
		if (i != count - 1) {
			query.append(" AND ");
		}
	}
	query.append(";");
	return this->executeCustomConsultativeQuery(query);
}

//INSERT INTO tableName SET field1 = value1,field2 = value2;
bool DaoMySql::executeInsertQueryWithValues(String tableName, const char *fields[], const char *values[], int count) {
	String query = "INSERT INTO " + tableName + " SET ";
	for (int i = 0;i < count; ++i) {
		query.append(fields[i]);
		query.append(" = ");
		query.append(values[i]);
		if (i != count - 1) {
			query.append(", ");
		}
	}
	query.append(";");
	return this->executeCustomModifiableQuery(query);
}
