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
std:: map<int, int> *mappedId;

void createMappedId(Dao* dao, String tableName, String fieldId) {
    std::stringstream query;
    mappedId = new std::map<int, int>;
    query << "SELECT Item, " + fieldId + " FROM " + tableName;
    if (dao->executeCustomConsultativeQuery(query.str())) {
        while(dao->fetch()) {
            (*mappedId)[convertToInt(dao->getField(2))] = convertToInt(dao->getField(1));
        }
    }
    else {
        //throw Exception(__FILE__, __LINE__, this->dao_->getError());
    }
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

float dotProductOf(std::vector<float> *vector1, std::vector<float> *vector2) {
	float product = 0.0;
	int size = vector1->size();
	for (unsigned i = 0; i < size; i++) {
		product += (*vector1)[i] * (*vector2)[i];
	}

	return product;
}

float normOf(std::vector<float> *vector) {
    float norm = 0.0;
    for (std::vector<float>::iterator it = vector->begin(); it != vector->end(); ++it) {
        norm += std::pow(*it, 2);
    }

    return std::sqrt(norm);
}

float differenceBetweenVectors(std::vector<float> *vector1, std::vector<float> *vector2) {
	int size = vector1->size();
	std::vector<float> *differenceVector = new std::vector<float>(size, 0);
	for (unsigned i = 0; i < size; ++i) {
		(*differenceVector)[i] = vector1->at(i) - vector2->at(i);
	}
	float norm = normOf(differenceVector);
}

float angleBetweenVectors(std::vector<float> *vector1, std::vector<float> *vector2) {
	float norm1 = normOf(vector1);
	float norm2 = normOf(vector2);
	float dotProduct = dotProductOf(vector1, vector2);

	return dotProduct / (norm1 * norm2);
}

int indexOf(String key) {
	return (*distributionOrder)[key];
}

int internalId(int key) {
    return (*mappedId)[key];
}

void deleteTheMapping() {
    delete distributionOrder;
    delete mappedId;
}

void insertSimilarity(String tableName, String fieldId, String tableNameSimilarity, String query) {
    Dao *dao = new DaoMySql(db_database, db_user, db_password, db_server);
    bool connect = dao->connect();
    if (!connect) {
        std::cerr << "Error al conectarse a la base de datos" << std::endl;
        std::cerr << dao->getError() << std::endl;
        return ;
    }
    int len = createDistributionKeyMap(dao);
    createMappedId(dao, tableName, fieldId);
    std::map<int, std::vector<float>* > topicProfile;
    bool hasresult = dao->executeCustomConsultativeQuery(query);
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
    for (std::map<int, std::vector<float>* >::iterator it = topicProfile.begin(); it != topicProfile.end(); ++it) {
        for (std::map<int, std::vector<float>* >::iterator it2 = it; it2 != topicProfile.end(); ++it2) {
            if (it == it2) {
                continue;
            }
            float angle = angleBetweenVectors(it->second, it2->second);
            if (angle > 0.0001) {
                std::stringstream query;
                int item = internalId(it->first);
                int item2 = internalId(it2->first);
                query << "INSERT INTO " + tableNameSimilarity + " (Item, Item2, Similarity) VALUES (" << item << "," << item2 << "," << angle << ")";
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
    deleteTheMapping();
}

void insertSimilarity() {
    /*
    String tableNameArticles = "ARTICLE_ITEM";
    String fieldIdArticles = "ArticleId";
    String queryArticles = "SELECT ArticleId, distribution, distribution_KEY FROM ARTICLES a, TopicProfile_distribution t WHERE a.topicProfile_identifier = t.topicProfile_identifier ORDER BY ArticleId";
    String tableNameSimilarityArticles = "SIMILARITY";

    String tableNameAuthors = "AUTHOR_ITEM";
    String fieldIdAuthors = "AuthorId";
    String queryAuthors = "SELECT authors_AuthorId, distributionAuthor, distribution_KEY FROM tesis.TopicProfileAuthors ORDER BY authors_AuthorId";
    String tableNameSimilarityAuthors = "SIMILARITY_AUTHOR";
    */
    String tableNameAffiliations = "AFFILIATION_ITEM";
    String fieldIdAffiliations = "affiliationId";
    String queryAffiliations = "SELECT AFFILIATION_affiliationId, distributionAffiliation, distribution_KEY FROM tesis.TopicProfileAffiliations ORDER BY AFFILIATION_affiliationId";
    String tableNameSimilarityAffiliations = "SIMILARITY_AFFILIATIONS";

    //insertSimilarity(tableNameArticles, fieldIdArticles, queryArticles, tableNameSimilarityArticles);
    //insertSimilarity(tableNameAuthors, fieldIdAuthors, queryAuthors, tableNameSimilarityAuthors);
    insertSimilarity(tableNameAffiliations, fieldIdAffiliations, tableNameSimilarityAffiliations, queryAffiliations);
}

void insertSimilarity(std::vector<float> *vector1) {
    /*
    String tableNameArticles = "ARTICLE_ITEM";
    String fieldIdArticles = "ArticleId";
    String queryArticles = "SELECT ArticleId, distribution, distribution_KEY FROM ARTICLES a, TopicProfile_distribution t WHERE a.topicProfile_identifier = t.topicProfile_identifier ORDER BY ArticleId";
    String tableNameSimilarityArticles = "SIMILARITY";

    String tableNameAuthors = "AUTHOR_ITEM";
    String fieldIdAuthors = "AuthorId";
    String queryAuthors = "SELECT authors_AuthorId, distributionAuthor, distribution_KEY FROM tesis.TopicProfileAuthors ORDER BY authors_AuthorId";
    String tableNameSimilarityAuthors = "SIMILARITY_AUTHOR";
    */
    String tableNameAffiliations = "AFFILIATION_ITEM";
    String fieldIdAffiliations = "affiliationId";
    String queryAffiliations = "SELECT AFFILIATION_affiliationId, distributionAffiliation, distribution_KEY FROM tesis.TopicProfileAffiliations ORDER BY AFFILIATION_affiliationId";
    String tableNameSimilarityAffiliations = "SIMILARITY_AFFILIATIONS";

    //insertSimilarity(tableNameArticles, fieldIdArticles, queryArticles, tableNameSimilarityArticles);
    //insertSimilarity(tableNameAuthors, fieldIdAuthors, queryAuthors, tableNameSimilarityAuthors);
    insertSimilarity(tableNameAffiliations, fieldIdAffiliations, tableNameSimilarityAffiliations, queryAffiliations);
}

void calculateSpecificSimilarity(std::vector<float> *vector1,String tableName, String fieldId, String tableNameSimilarity, String query){
	Dao *dao = new DaoMySql(db_database, db_user, db_password, db_server);
	bool connect = dao->connect();
	if (!connect) {
		std::cerr << "Error al conectarse a la base de datos" << std::endl;
		std::cerr << dao->getError() << std::endl;
		return ;
	}
	int len = createDistributionKeyMap(dao);
	createMappedId(dao, tableName, fieldId);
	std::map<int, std::vector<float>* > topicProfile;
	bool hasresult = dao->executeCustomConsultativeQuery(query);

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

	for (std::map<int, std::vector<float>* >::iterator it = topicProfile.begin(); it != topicProfile.end(); ++it) {
		float angle = angleBetweenVectors(it->second, vector1);
		if (angle > 0.0001) {
			std::stringstream query;
			int item = internalId(it->first);
			query << "INSERT INTO " + tableNameSimilarity + " (Item, Similarity) VALUES (" << item << ","  << angle << ")";
			if (!dao->executeCustomModifiableQuery(query.str())) {
				std::cerr<<"No se pudo insertar el ángulo entre los vectores"<<std::endl;
				std::cerr<<dao->getError()<<std::endl;
			}
		}
	}
}
