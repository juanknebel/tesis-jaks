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

#include "vectornorm.h"
#include "../dao/daoMySql.h"
#include "../util/stringUtilities.h"
#include <cstdlib>
#include <iostream>

#define db_database "tesis"
#define db_user "tesis"
#define db_password "tesis"
#define db_server "localhost"

std::map<String, int> *distributionOrder;

int getMappedId(Dao *dao, int id) {
	int theId = -1;
	std::stringstream query;
	query << "SELECT Item FROM ARTICLE_ITEM WHERE ArticleId = " <<id;
	if (dao->executeCustomConsultativeQuery(query.str())) {
		if (dao->fetch()) {
			theId = convertToInt(dao->getField(1));
		}
	}
	else {
		//throw Exception(__FILE__, __LINE__, this->dao_->getError());
	}
	return theId;
}

int getMappedIdForAuthor(Dao *dao, int id) {
	int theId = -1;
	std::stringstream query;
	query << "SELECT Item FROM AUTHOR_ITEM WHERE AuthorId = " <<id;
	if (dao->executeCustomConsultativeQuery(query.str())) {
		if (dao->fetch()) {
			theId = convertToInt(dao->getField(1));
		}
	}
	else {
		//throw Exception(__FILE__, __LINE__, this->dao_->getError());
	}
	return theId;
}

float dotProductOf(std::vector<float> *vector1, std::vector<float> *vector2) {
	float product = 0.0;
	int size = vector1->size();
	for (unsigned i = 0; i < size; i++) {
		product += (*vector1)[i] * (*vector2)[i];
	}

	return product;
}

float angleBetweenVectors(std::vector<float> *vector1, std::vector<float> *vector2) {
	float norm1 = normOf(vector1);
	float norm2 = normOf(vector2);
	float dotProduct = dotProductOf(vector1, vector2);

	return dotProduct / (norm1 * norm2);
}

float normOf(std::vector<float> *vector) {
	float norm = 0.0;
	for (std::vector<float>::iterator it = vector->begin(); it != vector->end(); ++it) {
		norm += std::pow(*it, 2);
	}

	return std::sqrt(norm);
}

int createDistributionKeyMap(Dao *dao) {
	bool hasresult =
	    dao->executeCustomConsultativeQuery(
	        "select distinct distribution_KEY from TopicProfile_distribution order by distribution_KEY asc");
	int order = 0;
	if (hasresult) {
		distributionOrder = new std::map<String, int>;
		while (dao->fetch()) {
			(*distributionOrder)[dao->getField(1)] = order;
			++order;
		}
	}

	return order + 1;
}

int indexOf(String key) {
	return (*distributionOrder)[key];
}

void insertSimilarity() {
	Dao *dao = new DaoMySql(db_database, db_user, db_password, db_server);
	bool connect = dao->connect();
	if (!connect) {
		std::cerr << "Error al conectarse a la base de datos" << std::endl;
		std::cerr << dao->getError() << std::endl;
		return ;
	}

	int len = createDistributionKeyMap(dao);

	std::map<int, std::vector<float>* > topicProfile;
	bool hasresult =
	    dao->executeCustomConsultativeQuery(
	        "SELECT ArticleId, distribution, distribution_KEY \
FROM ARTICLES a, TopicProfile_distribution t \
WHERE a.topicProfile_identifier = t.topicProfile_identifier \
ORDER BY ArticleId");

	if (hasresult) {
		int lastItemId = 0;
		while (dao->fetch()) {
			int itemId = convertToInt(dao->getField(1));
			if (lastItemId != itemId) {
				lastItemId = itemId;
				topicProfile[itemId] = new std::vector<float>(len, 0);
			}
			int indexKey = indexOf(dao->getField(3));
			(*topicProfile[itemId])[indexKey] = convertToDouble(dao->getField(2));
		}
	}
	//hasta aca tengo los vectores con el itemId del articulo y y el profile
	for (std::map<int, std::vector<float>* >::iterator it = topicProfile.begin(); it != topicProfile.end(); ++it) {
		for (std::map<int, std::vector<float>* >::iterator it2 = it; it2 != topicProfile.end(); ++it2) {
			if (it == it2) {
				continue;
			}
			float angle = angleBetweenVectors(it->second, it2->second);
			if (angle > 0.0001) {
				std::stringstream query;
				int item = getMappedId(dao, it->first);
				int item2 = getMappedId(dao, it2->first);
				query << "INSERT INTO SIMILARITY (Item, Item2, Similarity) VALUES (" << item << "," << item2 << "," << angle << ")";
				if (!dao->executeCustomModifiableQuery(query.str())) {
					std::cerr<<"No se pudo insertar el ángulo entre los vectores"<<std::endl;
					std::cerr<<dao->getError()<<std::endl;
				}
			}
		}
	}
	for (std::map<int, std::vector<float>* >::iterator it = topicProfile.begin(); it != topicProfile.end(); ++it) {
		delete it->second;
	}
}

void insertSimilarityOfTheAuthor() {
	Dao *dao = new DaoMySql(db_database, db_user, db_password, db_server);
	bool connect = dao->connect();
	if (!connect) {
		std::cerr << "Error al conectarse a la base de datos" << std::endl;
		std::cerr << dao->getError() << std::endl;
		return ;
	}

	int len = createDistributionKeyMap(dao);

	std::map<int, std::vector<float>* > topicProfile;
	bool hasresult =
	    dao->executeCustomConsultativeQuery(
	        "SELECT authors_AuthorId, distributionAuthor, distribution_KEY \
			FROM tesis.TopicProfileAuthors ORDER BY authors_AuthorId");

	if (hasresult) {
		int lastItemId = 0;
		while (dao->fetch()) {
			int itemId = convertToInt(dao->getField(1));
			if (lastItemId != itemId) {
				lastItemId = itemId;
				topicProfile[itemId] = new std::vector<float>(len, 0);
			}
			int indexKey = indexOf(dao->getField(3));
			(*topicProfile[itemId])[indexKey] = convertToDouble(dao->getField(2));
		}
	}
	//hasta aca tengo los vectores con el itemId del articulo y y el profile
	for (std::map<int, std::vector<float>* >::iterator it = topicProfile.begin(); it != topicProfile.end(); ++it) {
		for (std::map<int, std::vector<float>* >::iterator it2 = it; it2 != topicProfile.end(); ++it2) {
			if (it == it2) {
				continue;
			}
			float angle = angleBetweenVectors(it->second, it2->second);
			if (angle > 0.0001) {
				std::stringstream query;
				int item = getMappedIdForAuthor(dao, it->first);
				int item2 = getMappedIdForAuthor(dao, it2->first);
				query << "INSERT INTO SIMILARITY_AUTHOR (Item, Item2, Similarity) VALUES (" << item << "," << item2 << "," << angle << ")";
				if (!dao->executeCustomModifiableQuery(query.str())) {
					std::cerr<<"No se pudo insertar el ángulo entre los vectores"<<std::endl;
					std::cerr<<dao->getError()<<std::endl;
				}
			}
		}
	}
	for (std::map<int, std::vector<float>* >::iterator it = topicProfile.begin(); it != topicProfile.end(); ++it) {
		delete it->second;
	}
	
}