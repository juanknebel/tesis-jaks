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

#ifndef PROBLEMINSTANCEFROMDATABASE_H
#define PROBLEMINSTANCEFROMDATABASE_H

#include "problemInstance.h"
#include "../dao/dao.h"
//#include "../util/vectorToAngleSimilarity.h"

class ProblemInstanceFromDataBase :  public ProblemInstance {
private:
    std::string tableCosts_;
    std::string tableCompat_;
    std::string tableCover_;
    std::string tableConvertElementItem_;
    std::string costField_;
    std::string compatField_;
    std::string coverField_;
    std::string primaryField_;
    std::string primaryDescription_;
    std::string item_;
    std::string itemCompat1_;
    std::string itemCompat2_;
	Dao *dao_;
	
    void init(Dao *dao, std::string tableCosts, std::string tableCompat, std::string tableCover, std::string tableConvertElementItem, std::string costField, std::string compatField, std::string coverField, std::string primaryField, std::string primaryDescription, std::string item, std::string itemCompat1, std::string itemCompat2);
	int getPrimaryId(int id);
public:
	ProblemInstanceFromDataBase();
    ProblemInstanceFromDataBase(Dao *dao, std::string tableCosts, std::string tableCompat, std::string tableCover, std::string tableConvertElementItem, std::string costField, std::string compatField, std::string coverField, std::string primaryField, std::string primaryDescription, std::string item, std::string itemCompat1, std::string itemCompat2, double budget);
	~ProblemInstanceFromDataBase();
	
	std::set<int>& getIds();
	int numNodes();
    double getCost(int id);
	const std::set<int>* getCover(int id);
    double getCompat(int id1, int id2);
    MatrixWrapper* getCompat();
	void normalizeNodeCompat();
    std::string getNode(int id);
};

#endif // PROBLEMINSTANCEFROMDATABASE_H
