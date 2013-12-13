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

class DaoMySql : public Dao {
private:
	MYSQL *conn_;
	MYSQL_RES *res_;
	char **row_;
	String lastQueryExecute_;
	void freeConnection();
	bool executeQuery(String query);
	bool executeConsultativeQuery(String query);
	bool executeModifiableQuery(String query);
public:
	DaoMySql();
	DaoMySql(String database, String user, String password, String server);
	DaoMySql(const DaoMySql& dao);
	~DaoMySql();
	
	bool connect();
	bool disconnect();
	
	bool executeCustomConsultativeQuery(String query);
	bool executeCustomModifiableQuery(String query);
	const char** getNextRow();
	
	bool executeCountAllFrom(String tableName);
	bool executeSelectAllFrom(String tableName);
	bool executeSelectAllFromProject(String tableName, String fieldToProjet);
	bool executeSelectProjectFromWithAndConditions(String tableName, String fieldToProjet, const char *fields[], const char *values[], int count);
	bool executeInsertQueryWithValues(String tableName, const char *fields[], const char *values[], int count);
	
};

#endif // DAOMYSQL_H
