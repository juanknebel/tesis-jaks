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
#include <string>
#include "../util/system/Logger.h"

class Dao {
protected:
    std::string database_;
    std::string password_;
    std::string user_;
    std::string server_;
	bool isConnected_;
    std::string error_;
	int fields_;
    void init(std::string database, std::string user, std::string password, std::string server);
public:
	Dao() {
		this->init("", "", "", "");
	};
    Dao(std::string database, std::string user, std::string password, std::string server) {
		this->init(database, user, password, server);
	};
    virtual ~Dao() {}
	
	bool isConnected() const;
    std::string showConnection() const;
    std::string getError() const;
	int getNumberOfFields() const;
	
	virtual bool connect() = 0;
	virtual bool disconnect() = 0;
	
    virtual bool executeCustomConsultativeQuery(std::string query) = 0;
    virtual bool executeCustomModifiableQuery(std::string query) = 0;
	virtual bool fetch() = 0;
    virtual std::string getField(int index) = 0;
    virtual std::string getField(std::string fieldName) = 0;
};

#endif // DAO_H
