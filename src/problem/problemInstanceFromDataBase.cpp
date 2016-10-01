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

#include "problemInstanceFromDataBase.h"
#include "../util/system/stringUtilities.h"
#include "../util/system/exception.h"
#include "../dao/factoryDao.h"

void ProblemInstanceFromDataBase::init(std::string tableCosts, std::string tableCompat, std::string tableCover, std::string tableConvertElementItem,
									   std::string costField, std::string compatField, std::string coverField, std::string primaryField,
									   std::string primaryDescription, std::string item, std::string itemCompat1, std::string itemCompat2)
{
	//TODO: hay que mejorar esta porqueria!!!!!!!!!!!
	std::shared_ptr<FactoryDao> theFactoryDao = FactoryDao::getInstance("RELEASE");
	Dao& dao = theFactoryDao.get()->getDaoInstance();
	this->tableCosts_ = tableCosts;//ARTICLES
	this->tableCompat_ = tableCompat;//SIMILARITY
	this->tableCover_ = tableCover;//ARTICLES
	this->tableConvertElementItem_ = tableConvertElementItem;//ARTICLE_ITEM
	this->costField_ = costField;//Cost
	this->compatField_ = compatField;//Similarity
	this->coverField_ = coverField;//venue_Venue_Id
	this->primaryField_ = primaryField;//ArticleId
	this->primaryDescription_ = primaryDescription;//title
	this->item_ = item;//item
	this->itemCompat1_ = itemCompat1;//item
	this->itemCompat2_ = itemCompat2;//item2
	this->getIds();
	this->nodeCompat_ = new SparseDoubleMatrix2DImplementation(this->numNodes(), this->numNodes());
	std::stringstream query, query1;
	query<<"select "<<this->itemCompat1_<<","<<this->itemCompat2_<<","<<this->compatField_<<" from "<<this->tableCompat_;

	if (dao.executeCustomConsultativeQuery(query.str())) {
		while(dao.fetch()) {
			this->nodeCompat_->set(convertToInt(dao.getField(0)), convertToInt(dao.getField(1)), convertToDouble(dao.getField(2)));
		}
	}

	this->nodeSpecificCompat_ = new std::map<int, double>;
	query1<<"select * from SIMILARITY_AUX";

	if (dao.executeCustomConsultativeQuery(query1.str())) {
		while(dao.fetch()) {
			(*this->nodeSpecificCompat_)[convertToInt(dao.getField(0))] = convertToDouble(dao.getField(1));
		}
	}
}

int ProblemInstanceFromDataBase::getPrimaryId(int id)
{
	std::shared_ptr<FactoryDao> theFactoryDao = FactoryDao::getInstance("RELEASE");
	Dao& dao = theFactoryDao.get()->getDaoInstance();
	int theId = -1;
	std::stringstream query;
	query<<"select "<<this->primaryField_<<" from "<<this->tableConvertElementItem_<<" where "<<this->item_<<" = "<<id;

	if (dao.executeCustomConsultativeQuery(query.str())) {
		if (dao.fetch()) {
			theId = convertToInt(dao.getField(0));
		}
	}

	else {
		throw Exception(__FILE__, __LINE__, dao.getError());
	}

	return theId;
}

ProblemInstanceFromDataBase::ProblemInstanceFromDataBase() : ProblemInstance()
{
	this->init("", "", "", "",
			   "", "", "", "",
			   "", "", "", "");
}

ProblemInstanceFromDataBase::ProblemInstanceFromDataBase(std::string tableCosts, std::string tableCompat, std::string tableCover,
                                                         std::string tableConvertElementItem, std::string costField, std::string compatField,
                                                         std::string coverField, std::string primaryField, std::string primaryDescription,
                                                         std::string item, std::string itemCompat1, std::string itemCompat2, double budget)
        : ProblemInstance(budget)
{
	this->init(tableCosts, tableCompat, tableCover, tableConvertElementItem,
			   costField, compatField, coverField, primaryField,
			   primaryDescription, item, itemCompat1, itemCompat2);
}

ProblemInstanceFromDataBase::~ProblemInstanceFromDataBase()
{
}

std::set<int>& ProblemInstanceFromDataBase::getIds()
{
	std::shared_ptr<FactoryDao> theFactoryDao = FactoryDao::getInstance("RELEASE");
	Dao& dao = theFactoryDao.get()->getDaoInstance();
	if (this->ids_->empty()) {
		std::stringstream query;
		query<<"select "<<this->item_<<" from "<<this->tableConvertElementItem_;

		if (dao.executeCustomConsultativeQuery(query.str())) {
			while(dao.fetch()) {
				this->ids_->insert(convertToInt(dao.getField(0)));
			}
		}

		else {
			throw Exception(__FILE__, __LINE__, dao.getError());
		}
	}

	return *(this->ids_);
}

int ProblemInstanceFromDataBase::numNodes()
{
	return this->ids_->size();
}

double ProblemInstanceFromDataBase::getCost(int id)
{
	return 1.0;
	/*double cost = -1.0;
	int primaryId = this->getPrimaryId(id);
	std::stringstream query;
	query<<"select "<<this->costField_<<" from "<<this->tableCosts_<<" where "<<this->primaryField_<<" = "<<primaryId;
	if (dao.executeCustomConsultativeQuery(query.str())) {
		cost = atof(dao.getNextRow()[0]);
	}
	else {
		throw Exception(__FILE__, __LINE__, dao.getError());
	}

	return cost;*/
}

const std::set<int>* ProblemInstanceFromDataBase::getCover(int id)
{
	std::shared_ptr<FactoryDao> theFactoryDao = FactoryDao::getInstance("RELEASE");
	Dao& dao = theFactoryDao.get()->getDaoInstance();
	if (this->nodeCover_->count(id) == 0) {
		int primaryId = this->getPrimaryId(id);
		std::stringstream query;
		query<<"select "<<this->coverField_<<" from "<<this->tableCosts_<<" where "<<this->primaryField_<<" = "<<primaryId;

		if (dao.executeCustomConsultativeQuery(query.str())) {
			std::set<int> *aSet = new std::set<int>();

			while(dao.fetch()) {
				aSet->insert(convertToInt(dao.getField(0)));
			}

			(*(*this).nodeCover_)[id] = aSet;
		}

		else {
			throw Exception(__FILE__, __LINE__, dao.getError());
		}
	}

	return this->nodeCover_->at(id);
}

/*double ProblemInstanceFromDataBase::getCompat(int id1, int id2) {
	VectorToAngleSimilarity* similarity = VectorToAngleSimilarity::getInstance();
	double compat = similarity->getAngleBetweenVectors(dao, id1, id2);
	return compat;
}*/

/*double ProblemInstanceFromDataBase::getCompat(int id1, int id2) {
        double compat = -1.0;
        int temp;
        if (id1 > id2) {
                std::swap(id1, id2);
        }
        if (id1 == id2) {
                return 0;
                //throw Exception(__FILE__, __LINE__, "The ids can not be equal");
        }
	std::stringstream query;
	query<<"select "<<this->compatField_<<" from "<<this->tableCompat_<<" where "<<this->itemCompat1_<<" = "<<id1 << " and " << itemCompat2_<< " = "<<id2;
        if (dao.executeCustomConsultativeQuery(query.str())) {
                const char** result = dao.getNextRow();
                compat = (result != NULL) ? atof(result[0]) : 0.00;
        }
        else {
                throw Exception(__FILE__, __LINE__, dao.getError());
        }
        return compat;
}*/

double ProblemInstanceFromDataBase::getCompat(int id1, int id2)
{
	if (id1 > id2) {
		std::swap(id1, id2);
	}

	return ProblemInstance::getCompat(id1, id2);
}


SparseDoubleMatrix2D* ProblemInstanceFromDataBase::getCompat()
{
	throw Exception(__FILE__, __LINE__, "Imposible to retrieve so many registers");
	return 0;
}

void ProblemInstanceFromDataBase::normalizeNodeCompat()
{
	throw Exception(__FILE__, __LINE__, "The compatibility is already normalize");
}

std::string ProblemInstanceFromDataBase::getNode(int id)
{
	return convertToString(this->getPrimaryId(id));
}
