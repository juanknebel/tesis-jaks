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
#include "util/stringUtilities.h"
#include "util/exception.h"

void ProblemInstanceFromDataBase::init(Dao *dao, String tableCosts, String tableCompat, String tableCover, String tableConvertElementItem, String costField, String compatField, String coverField, String primaryField, String primaryDescription, String item, String itemCompat1, String itemCompat2) {
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
}

int ProblemInstanceFromDataBase::getPrimaryId(int id) {
	int theId = -1;
	const char *fields [] =  {this->item_.c_str()};
	const char *values [] = {convertToString(id).c_str()};
	if (this->dao_->executeSelectProjectFromWithAndConditions(this->tableConvertElementItem_, primaryField_, fields, values, 1)) {
		theId = atoi(this->dao_->getNextRow()[0]);
	}
	else {
		throw Exception(__FILE__, __LINE__, this->dao_->getError());
	}
	return theId;
}

ProblemInstanceFromDataBase::ProblemInstanceFromDataBase() : ProblemInstance() {
	this->init(NULL, "", "", "", "", "", "", "", "", "", "", "", "");
}

ProblemInstanceFromDataBase::ProblemInstanceFromDataBase(Dao *dao, String tableCosts, String tableCompat, String tableCover, String tableConvertElementItem, String costField, String compatField, String coverField, String primaryField, String primaryDescription, String item, String itemCompat1, String itemCompat2, Double budget) : ProblemInstance(budget) {
	this->init(dao, tableCosts, tableCompat, tableCover, tableConvertElementItem, costField, compatField, coverField, primaryField, primaryDescription, item, itemCompat1, itemCompat2);
}

ProblemInstanceFromDataBase::~ProblemInstanceFromDataBase() {
}

IntSet& ProblemInstanceFromDataBase::getIds() {
	if (this->ids_->empty()) {
		if (this->dao_->executeSelectAllFromProject(this->tableConvertElementItem_, this->item_)) {
			const char** result;
			while(result = this->dao_->getNextRow()) {
				this->ids_->insert(atoi(result[0]));
			}
		}
		else {
			throw Exception(__FILE__, __LINE__, this->dao_->getError());
		}
	}
	return *(this->ids_);
}

int ProblemInstanceFromDataBase::numNodes() {
	int count = -1;
	if (this->dao_->executeCountAllFrom(this->tableCosts_)) {
		count = atoi(this->dao_->getNextRow()[0]);
	}
	else {
		throw Exception(__FILE__, __LINE__, this->dao_->getError());
	}
	return count;
}

Double ProblemInstanceFromDataBase::getCost(int id) {
	Double cost = -1.0;
	const char *fields [] =  {this->primaryField_.c_str()};
	const char *values [] = {convertToString(this->getPrimaryId(id)).c_str()};
	if (this->dao_->executeSelectProjectFromWithAndConditions(this->tableCosts_, this->costField_,fields, values, 1)) {
		cost = atof(this->dao_->getNextRow()[0]);
	}
	else {
		throw Exception(__FILE__, __LINE__, this->dao_->getError());
	}
	return cost;
}

const IntSet* ProblemInstanceFromDataBase::getCover(int id) {
	IntSet *cover = new IntSet;
	const char *fields [] =  {this->primaryField_.c_str()};
	const char *values [] = {convertToString(this->getPrimaryId(id)).c_str()};
	if (this->dao_->executeSelectProjectFromWithAndConditions(this->tableCosts_, this->coverField_,fields, values, 1)) {
		const char** result;
			while(result = this->dao_->getNextRow()) {
				cover->insert(atoi(result[0]));
			}
	}
	else {
		throw Exception(__FILE__, __LINE__, this->dao_->getError());
	}
	return cover;
}

Double ProblemInstanceFromDataBase::getCompat(int id1, int id2) {
	Double compat = -1.0;
	int temp;
	if (id1 > id2) {
		std::swap(id1, id2);
	}
	if (id1 == id2) {
		throw Exception(__FILE__, __LINE__, "The ids can not be equal");
	}
	const char *fields [] =  {this->itemCompat1_.c_str(), this->itemCompat2_.c_str()};
	String theId1 = convertToString(id1), theId2 = convertToString(id2);
	const char *values [] = {theId1.c_str(), theId2.c_str()};
	if (this->dao_->executeSelectProjectFromWithAndConditions(this->tableCompat_, this->compatField_,fields, values, 2)) {
		compat = atof(this->dao_->getNextRow()[0]);
	}
	else {
		throw Exception(__FILE__, __LINE__, this->dao_->getError());
	}
	return compat;
}

SparseDoubleMatrix2D* ProblemInstanceFromDataBase::getCompat() {
	int count = -1;
	if (this->dao_->executeCountAllFrom(this->tableCompat_)) {
		count = atoi(this->dao_->getNextRow()[0]);
		this->dao_->disconnect();
	}
	else {
		throw Exception(__FILE__, __LINE__, this->dao_->getError());
	}
	throw Exception(__FILE__, __LINE__, "Imposible to retrieve so many registers: " + convertToString(count));
	return 0;
}

void ProblemInstanceFromDataBase::normalizeNodeCompat() {
	throw Exception(__FILE__, __LINE__, "The compatibility is already normalize");
}

String ProblemInstanceFromDataBase::getNode(int id) {
	String node;
	const char *fields [] =  {this->primaryField_.c_str()};
	const char *values [] = {convertToString(this->getPrimaryId(id)).c_str()};
	if (this->dao_->executeSelectProjectFromWithAndConditions(this->tableCosts_, this->primaryDescription_,fields, values, 1)) {
		node = this->dao_->getNextRow()[0];
	}
	else {
		throw Exception(__FILE__, __LINE__, this->dao_->getError());
	}
	return node;
}
