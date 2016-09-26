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

void ProblemInstanceFromDataBase::init(Dao *dao, std::string tableCosts, std::string tableCompat, std::string tableCover, std::string tableConvertElementItem, std::string costField, std::string compatField, std::string coverField, std::string primaryField, std::string primaryDescription, std::string item, std::string itemCompat1, std::string itemCompat2)
{
	//TODO: hay que mejorar esta porqueria!!!!!!!!!!!
	this->dao_ = dao;
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

	if (this->dao_->executeCustomConsultativeQuery(query.str())) {
		while(this->dao_->fetch()) {
			this->nodeCompat_->set(convertToInt(this->dao_->getField(0)), convertToInt(this->dao_->getField(1)), convertToDouble(this->dao_->getField(2)));
		}
	}

	this->nodeSpecificCompat_ = new std::map<int, double>;
	query1<<"select * from SIMILARITY_AUX";

	if (this->dao_->executeCustomConsultativeQuery(query1.str())) {
		while(this->dao_->fetch()) {
			(*this->nodeSpecificCompat_)[convertToInt(this->dao_->getField(0))] = convertToDouble(this->dao_->getField(1));
		}
	}
}

int ProblemInstanceFromDataBase::getPrimaryId(int id)
{
	int theId = -1;
	std::stringstream query;
	query<<"select "<<this->primaryField_<<" from "<<this->tableConvertElementItem_<<" where "<<this->item_<<" = "<<id;

	if (this->dao_->executeCustomConsultativeQuery(query.str())) {
		if (this->dao_->fetch()) {
			theId = convertToInt(this->dao_->getField(0));
		}
	}

	else {
		throw Exception(__FILE__, __LINE__, this->dao_->getError());
	}

	return theId;
}

ProblemInstanceFromDataBase::ProblemInstanceFromDataBase() : ProblemInstance()
{
	this->init(NULL, "", "", "", "", "", "", "", "", "", "", "", "");
}

ProblemInstanceFromDataBase::ProblemInstanceFromDataBase(Dao *dao, std::string tableCosts, std::string tableCompat, std::string tableCover, std::string tableConvertElementItem, std::string costField, std::string compatField, std::string coverField, std::string primaryField, std::string primaryDescription, std::string item, std::string itemCompat1, std::string itemCompat2, double budget) : ProblemInstance(budget)
{
	this->init(dao, tableCosts, tableCompat, tableCover, tableConvertElementItem, costField, compatField, coverField, primaryField, primaryDescription, item, itemCompat1, itemCompat2);
}

ProblemInstanceFromDataBase::~ProblemInstanceFromDataBase()
{
	delete this->dao_;
}

std::set<int>& ProblemInstanceFromDataBase::getIds()
{
	if (this->ids_->empty()) {
		std::stringstream query;
		query<<"select "<<this->item_<<" from "<<this->tableConvertElementItem_;

		if (this->dao_->executeCustomConsultativeQuery(query.str())) {
			while(this->dao_->fetch()) {
				this->ids_->insert(convertToInt(this->dao_->getField(0)));
			}
		}

		else {
			throw Exception(__FILE__, __LINE__, this->dao_->getError());
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
	if (this->dao_->executeCustomConsultativeQuery(query.str())) {
		cost = atof(this->dao_->getNextRow()[0]);
	}
	else {
		throw Exception(__FILE__, __LINE__, this->dao_->getError());
	}

	return cost;*/
}

const std::set<int>* ProblemInstanceFromDataBase::getCover(int id)
{
	if (this->nodeCover_->count(id) == 0) {
		int primaryId = this->getPrimaryId(id);
		std::stringstream query;
		query<<"select "<<this->coverField_<<" from "<<this->tableCosts_<<" where "<<this->primaryField_<<" = "<<primaryId;

		if (this->dao_->executeCustomConsultativeQuery(query.str())) {
			std::set<int> *aSet = new std::set<int>();

			while(this->dao_->fetch()) {
				aSet->insert(convertToInt(this->dao_->getField(0)));
			}

			(*(*this).nodeCover_)[id] = aSet;
		}

		else {
			throw Exception(__FILE__, __LINE__, this->dao_->getError());
		}
	}

	return this->nodeCover_->at(id);
}

/*double ProblemInstanceFromDataBase::getCompat(int id1, int id2) {
	VectorToAngleSimilarity* similarity = VectorToAngleSimilarity::getInstance();
	double compat = similarity->getAngleBetweenVectors(this->dao_, id1, id2);
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
        if (this->dao_->executeCustomConsultativeQuery(query.str())) {
                const char** result = this->dao_->getNextRow();
                compat = (result != NULL) ? atof(result[0]) : 0.00;
        }
        else {
                throw Exception(__FILE__, __LINE__, this->dao_->getError());
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
