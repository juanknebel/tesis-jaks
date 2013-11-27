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

#ifndef DAO_H
#define DAO_H
#include "../util/redefinitions.h"
#include <mysql/mysql.h>

class Dao {
protected:
	String database_;
	String password_;
	String user_;
	String server_;
	bool isConnected_;
	String error_;
	MYSQL *conn_;
	MYSQL_RES *res_;
	char **row_;
	int fields_;
	void init(String database, String user, String password, String server);
public:
	Dao();
	Dao(String database, String user, String password, String server);
	bool connect();
	bool disconnect();
	bool isConnected() const;
	String showConnection() const;
	String getError() const;
	bool getAllFrom(String tableName);
	int getNumberOfFields() const;
	const char** getNextRow();
	~Dao();
    
};

#endif // DAO_H
