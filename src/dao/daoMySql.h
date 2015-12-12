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

#ifndef DAOMYSQL_H
#define DAOMYSQL_H
#include "dao.h"

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>
#include <sstream>

class DaoMySql : public Dao {
private:
	sql::Driver *driver_;
	sql::Connection *con_;
	sql::Statement *stmt_;
	sql::PreparedStatement *pstmt_;
	sql::ResultSet *res_;
	sql::ResultSetMetaData *res_meta_;
	String lastQueryExecute_;
	bool executeConsultativeQuery(String query);
	bool executeModifiableQuery(String query);
	void manageException(sql::SQLException& e);
public:
	DaoMySql(String database, String user, String password, String server) : Dao(database, user, password, server) {}
	DaoMySql(const DaoMySql& dao) : Dao(dao.database_, dao.user_, dao.password_, dao.server_) {}
	~DaoMySql();
	
	bool connect();
	bool disconnect();
	
	bool executeCustomConsultativeQuery(String query);
	bool executeCustomModifiableQuery(String query);
	bool fetch();
	String getField(int index);
	String getField(String fieldName);
};

#endif // DAOMYSQL_H
