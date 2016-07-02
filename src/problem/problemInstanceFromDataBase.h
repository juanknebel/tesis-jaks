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
	String tableCosts_;
	String tableCompat_;
	String tableCover_;
	String tableConvertElementItem_;
	String costField_;
	String compatField_;
	String coverField_;
	String primaryField_;
	String primaryDescription_;
	String item_;
	String itemCompat1_;
	String itemCompat2_;
	Dao *dao_;

	void init(Dao *dao, String tableCosts, String tableCompat, String tableCover, String tableConvertElementItem, String costField, String compatField, String coverField, String primaryField, String primaryDescription, String item, String itemCompat1, String itemCompat2);
	int getPrimaryId(int id);
public:
	ProblemInstanceFromDataBase();
	ProblemInstanceFromDataBase(Dao *dao, String tableCosts, String tableCompat, String tableCover, String tableConvertElementItem, String costField, String compatField, String coverField, String primaryField, String primaryDescription, String item, String itemCompat1, String itemCompat2, Double budget);
	~ProblemInstanceFromDataBase();

	IntSet& getIds();
	int numNodes();
	Double getCost(int id);
	const IntSet* getCover(int id);
	Double getCompat(int id1, int id2);
	SparseDoubleMatrix2D* getCompat();
	void normalizeNodeCompat();
	String getNode(int id);
};

#endif // PROBLEMINSTANCEFROMDATABASE_H
