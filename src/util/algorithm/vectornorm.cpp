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
#include "../../dao/daoQt.h"
#include "../system/stringUtilities.h"

#define db_database "tesis"
#define db_user "root"
#define db_password "passw0rd"
#define db_server "localhost"

std::map<std::string, int> *distributionOrder;
std:: map<int, int> *mappedId;

float distanceBetweenVectors(std::vector<float> *pVector, std::vector<float> *second);

float similarityBetweenVectors(float angle, float distance, float theA);

void createMappedId(Dao* dao, std::string tableName, std::string fieldId)
{
	std::stringstream query;
	mappedId = new std::map<int, int>;
	query << "SELECT Item, " + fieldId + " FROM " + tableName;

	if (dao->executeCustomConsultativeQuery(query.str())) {
		while(dao->fetch()) {
			(*mappedId)[convertToInt(dao->getField(1))] = convertToInt(dao->getField(0));
		}
	}

	else {
		//throw Exception(__FILE__, __LINE__, this->dao_->getError());
	}
}

int createDistributionKeyMap(Dao *dao)
{
	bool hasResult =
	    dao->executeCustomConsultativeQuery(
	        "select distinct distribution_KEY from TopicProfile_distribution order by distribution_KEY asc");
	int order = 0;

	if (hasResult) {
		distributionOrder = new std::map<std::string, int>;

		while (dao->fetch()) {
			(*distributionOrder)[dao->getField(0)] = order;
			++order;
		}
	}

	return order + 1;
}

float dotProductOf(std::vector<float> *vector1, std::vector<float> *vector2)
{
	float product = 0.0;
	auto size = vector1->size();

	for (unsigned i = 0; i < size; i++) {
		product += (*vector1)[i] * (*vector2)[i];
	}

	return product;
}

float normOf(std::vector<float> *vector)
{
	float norm = 0.0;

	for (std::vector<float>::iterator it = vector->begin(); it != vector->end(); ++it) {
		norm += std::pow(*it, 2);
	}

	return std::sqrt(norm);
}

float differenceBetweenVectors(std::vector<float> *vector1, std::vector<float> *vector2)
{
	auto size = vector1->size();
	std::vector<float> *differenceVector = new std::vector<float>(size, 0);

	for (unsigned i = 0; i < size; ++i) {
		(*differenceVector)[i] = vector1->at(i) - vector2->at(i);
	}

	float norm = normOf(differenceVector);
	return norm;
}

float angleBetweenVectors(std::vector<float> *vector1, std::vector<float> *vector2)
{
	float norm1 = normOf(vector1);
	float norm2 = normOf(vector2);
	float dotProduct = dotProductOf(vector1, vector2);

	return dotProduct / (norm1 * norm2);
}

float distanceBetweenVectors(std::vector<float> *vector1, std::vector<float> *vector2)
{
	return normOf(vector1) - normOf(vector2);
}

float similarityBetweenVectors(float angle, float distance, float theA)
{
	return static_cast<float> (pow(theA, distance) * angle);
}

int indexOf(std::string key)
{
	return (*distributionOrder)[key];
}

int internalId(int key)
{
	return (*mappedId)[key];
}

void deleteTheMapping()
{
	delete distributionOrder;
	delete mappedId;
}

void insertSimilarity(std::string tableName, std::string fieldId, std::string tableNameSimilarity, std::string query)
{
	Dao *dao = new DaoQt(db_database, db_user, db_password, db_server);
	bool connect = dao->connect();

	if (!connect) {
		std::cerr << "Error al conectarse a la base de datos" << std::endl;
		std::cerr << dao->getError() << std::endl;
		return ;
	}

	int len = createDistributionKeyMap(dao);
	createMappedId(dao, tableName, fieldId);
	std::map<int, std::vector<float>* > topicProfile;
	bool hasResult = dao->executeCustomConsultativeQuery(query);

	if (hasResult) {
		int lastItemId = 0;

		while (dao->fetch()) {
			int itemId = convertToInt(dao->getField(0));

			if (lastItemId != itemId) {
				lastItemId = itemId;
				topicProfile[itemId] = new std::vector<float>(len, 0);
			}

			int indexKey = indexOf(dao->getField(2));
			(*topicProfile[itemId])[indexKey] = convertToDouble(dao->getField(1));
		}
	}

	std::ofstream myFile;
	myFile.open("insert_similarity.csv");

	for (std::map<int, std::vector<float>* >::iterator it = topicProfile.begin(); it != topicProfile.end(); ++it) {
		for (std::map<int, std::vector<float>* >::iterator it2 = it; it2 != topicProfile.end(); ++it2) {
			if (it == it2) {
				continue;
			}

			float theA = 0.8;
			float angle = angleBetweenVectors(it->second, it2->second);
			float distance = std::abs(distanceBetweenVectors(it->second, it2->second));
			float similarity = similarityBetweenVectors(angle, distance, theA);

			if (angle > 0.0001) {
				int item = internalId(it->first);
				int item2 = internalId(it2->first);
				myFile << item << ";" << item2 << ";" << distance << ";" << angle << ";" << similarity << std::endl;
				/*std::stringstream query;
				query << "INSERT INTO " + tableNameSimilarity + " (Item, Item2, Similarity) VALUES (" << item << "," << item2 << "," << angle << ")";
				if (!dao->executeCustomModifiableQuery(query.str())) {
				    std::cerr<<"No se pudo insertar el ángulo entre los vectores"<<std::endl;
				    std::cerr<<dao->getError()<<std::endl;
				}*/
			}
		}
	}

	myFile.close();

	for (std::map<int, std::vector<float>* >::iterator it = topicProfile.begin(); it != topicProfile.end(); ++it) {
		delete it->second;
	}

	deleteTheMapping();
}

void calculateSpecificSimilarity(std::vector<float> vector1,std::string tableName, std::string fieldId, std::string tableNameSimilarity, std::string query)
{
	Dao *dao = new DaoQt(db_database, db_user, db_password, db_server);
	bool connect = dao->connect();

	if (!connect) {
		std::cerr << "Error al conectarse a la base de datos" << std::endl;
		std::cerr << dao->getError() << std::endl;
		return ;
	}

	int len = createDistributionKeyMap(dao);
	createMappedId(dao, tableName, fieldId);
	std::map<int, std::vector<float>* > topicProfile;
	bool hasResult = dao->executeCustomConsultativeQuery(query);

	if (hasResult) {
		int lastItemId = 0;

		while (dao->fetch()) {
			int itemId = convertToInt(dao->getField(0));

			if (lastItemId != itemId) {
				lastItemId = itemId;
				topicProfile[itemId] = new std::vector<float>(len, 0);
			}

			int indexKey = indexOf(dao->getField(2));
			(*topicProfile[itemId])[indexKey] = convertToDouble(dao->getField(1));
		}
	}

	for (std::map<int, std::vector<float>* >::iterator it = topicProfile.begin(); it != topicProfile.end(); ++it) {
		float angle = angleBetweenVectors(it->second, &vector1);

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

void insertSimilarity()
{
	/*std::string tableNameArticles = "ARTICLE_ITEM";
	std::string fieldIdArticles = "ArticleId";
	std::string queryArticles = "SELECT ArticleId, distribution, distribution_KEY FROM ARTICLES a, TopicProfile_distribution t WHERE a.topicProfile_identifier = t.topicProfile_identifier ORDER BY ArticleId";
	std::string tableNameSimilarityArticles = "SIMILARITY";
	insertSimilarity(tableNameArticles, fieldIdArticles, tableNameSimilarityArticles, queryArticles);*/

	/*std::string tableNameAuthors = "AUTHOR_ITEM";
	std::string fieldIdAuthors = "AuthorId";
	std::string queryAuthors = "SELECT authors_AuthorId, distributionAuthor, distribution_KEY FROM TopicProfileAuthors ORDER BY authors_AuthorId";
	std::string tableNameSimilarityAuthors = "SIMILARITY_AUTHOR";
	insertSimilarity(tableNameAuthors, fieldIdAuthors, tableNameSimilarityAuthors, queryAuthors);*/

	std::string tableNameAffiliations = "AFFILIATION_ITEM";
	std::string fieldIdAffiliations = "affiliationId";
	std::string queryAffiliations = "SELECT AFFILIATION_affiliationId, distributionAffiliation, distribution_KEY FROM TopicProfileAffiliations ORDER BY AFFILIATION_affiliationId";
	std::string tableNameSimilarityAffiliations = "SIMILARITY_AFFILIATIONS";
	insertSimilarity(tableNameAffiliations, fieldIdAffiliations, tableNameSimilarityAffiliations, queryAffiliations);
}

void insertSimilarity(std::vector<float> vector1)
{
	std::string tableNameArticles = "ARTICLE_ITEM";
	std::string fieldIdArticles = "ArticleId";
	std::string queryArticles = "SELECT ArticleId, distribution, distribution_KEY FROM "
	                       "ARTICLES a, TopicProfile_distribution t WHERE a.topicProfile_identifier = t.topicProfile_identifier ORDER BY ArticleId";
	std::string tableNameSimilarityArticles = "SIMILARITY_AUX";

	calculateSpecificSimilarity(vector1,tableNameArticles, fieldIdArticles, tableNameSimilarityArticles, queryArticles);
}
