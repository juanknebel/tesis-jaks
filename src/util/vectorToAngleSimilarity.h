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

#ifndef VECTORTOANGLESIMILARITY_H
#define VECTORTOANGLESIMILARITY_H

#include "../dao/daoMySql.h"

class VectorToAngleSimilarity {
private:
	static VectorToAngleSimilarity* instance_;
	std::map<String, int> *distributionOrder_;
protected:
	VectorToAngleSimilarity();
	static void DestroySingleton();
	int getPrimaryId(Dao* dao, int id);
	void createDistributionKeyMap(Dao* dao);
	DblVector* vectorizeElement(Dao* dao, int id, int len);
	Double angleBetweenVectors(DblVector* vector, DblVector* vector2);
	Double normOf(DblVector* vector);
	Double dotProductOf(DblVector* vector, DblVector* vector2);
public:
	virtual ~VectorToAngleSimilarity();
	static VectorToAngleSimilarity* getInstance();
 	Double getAngleBetweenVectors(Dao* dao, int item, int item2);
};

#endif // VECTORTOANGLESIMILARITY_H
