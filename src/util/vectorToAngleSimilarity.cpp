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

#include "vectorToAngleSimilarity.h"
#include "exception.h"
#include <cmath>
#include <cstdlib>

VectorToAngleSimilarity* VectorToAngleSimilarity::instance_;

VectorToAngleSimilarity::VectorToAngleSimilarity() {
	this->distributionOrder_ = new std::map<String, int>;
}

void VectorToAngleSimilarity::DestroySingleton() {
	if (instance_ == NULL) {
		delete instance_;
		delete instance_->distributionOrder_;
	}
}

int VectorToAngleSimilarity::getPrimaryId(Dao* dao, int id) {
	int theId = -1;
	std::stringstream query;
	query << "SELECT ArticleId FROM ARTICLE_ITEM WHERE item = " <<id;
	if (dao->executeCustomConsultativeQuery(query.str())) {
		theId = atoi(dao->getNextRow()[0]);
	}
	else {
		throw Exception(__FILE__, __LINE__, dao->getError());
	}
	
	return theId;
}

void VectorToAngleSimilarity::createDistributionKeyMap(Dao *dao) {
	if (this->distributionOrder_->empty()) {
		int order = 0;
		if (dao->executeCustomConsultativeQuery(
			"SELECT distinct distribution_KEY FROM TopicProfile_distribution ORDER BY distribution_KEY ASC")) {
			const char **result;
			while (result = dao->getNextRow()) {
				(*this->distributionOrder_)[String(result[0])] = order;
				++order;
			}
		}
		else {
			throw Exception(__FILE__, __LINE__, dao->getError());
		}
	}
}

DblVector* VectorToAngleSimilarity::vectorizeElement(Dao *dao, int id, int len) {
	std::stringstream query;
	query << "SELECT ArticleId, distribution, distribution_KEY FROM ARTICLES a, TopicProfile_distribution t ";
	query << "WHERE a.topicProfile_identifier = t.topicProfile_identifier AND a.ArticleId = " << id;
	DblVector* theVector = new DblVector(len, 0.00);
	if (dao->executeCustomConsultativeQuery(query.str())) {
		const char **result;
		while (result = dao->getNextRow()) {
			int indexKey = (*this->distributionOrder_)[String(result[2])];
			(*theVector)[indexKey] = atof(result[1]);
		}
	}
	
	return theVector;
}

Double VectorToAngleSimilarity::angleBetweenVectors(DblVector *vector, DblVector *vector2) {
	float norm1 = this->normOf(vector);
	float norm2 = this->normOf(vector2);
	float dotProduct = dotProductOf(vector, vector2);

	return dotProduct / (norm1 * norm2);
}

Double VectorToAngleSimilarity::normOf(DblVector *vector) {
	Double norm = 0.0;
	for (DblVector::iterator it = vector->begin(); it != vector->end(); ++it) {
		norm += std::pow(*it, 2);
	}

	return std::sqrt(norm);
}

Double VectorToAngleSimilarity::dotProductOf(DblVector *vector, DblVector *vector2) {
	float product = 0.0;
	int size = vector->size();
	for (unsigned i = 0; i < size; ++i) {
		product += (*vector)[i] * (*vector2)[i];
	}

	return product;
}

VectorToAngleSimilarity::~VectorToAngleSimilarity() {
}

VectorToAngleSimilarity* VectorToAngleSimilarity::getInstance() {
	if (instance_ == NULL) {
		instance_ = new VectorToAngleSimilarity();
		atexit(&DestroySingleton); 
	}
	
	return instance_;
}

Double VectorToAngleSimilarity::getAngleBetweenVectors(Dao* dao, int item, int item2) {
	this->createDistributionKeyMap(dao);
	int len = this->distributionOrder_->size();
	int originalId = this->getPrimaryId(dao, item);
	int originalId2 = this->getPrimaryId(dao, item2);
	DblVector* vectorElement = this->vectorizeElement(dao, originalId, len);
	DblVector* vectorElement2 = this->vectorizeElement(dao, originalId2, len);
	Double angle = this->angleBetweenVectors(vectorElement, vectorElement2);
	delete vectorElement;
	delete vectorElement2;
	return angle;
}
