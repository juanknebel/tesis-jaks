/*
 * id2Str.cpp
 *
 *  Created on: 30/07/2013
 *      Author: zero
 */

#include "id2Str.h"
#include "stringUtilities.h"

Id2Str::Id2Str() {
	this->node2name_ = 0;
	this->dao_ = 0;
}

Id2Str::Id2Str(String fileName) {
	this->node2name_ = new Object2ObjectOpenHashMap;
	FileInput file;
	file.open(fileName.c_str());
	String line;
	while(getline(file, line, '\n')) {
		StrVector tokens;
		stringToVectorSplit(line, "\t", tokens);
		(*(this->node2name_))[tokens[0]] = tokens[1]; 
	}
	file.close();
}

Id2Str::Id2Str(Dao *dao, String tableName, String node, String fieldToProyect) {
	this->node2name_ = new Object2ObjectOpenHashMap;
	std::stringstream query;
	query<<	"select \
		a.ArticleId as ArticleId \
		,a.title as Title \
		,b.name as VenueName \
		,c.name as Author \
		from ARTICLES a, VENUES b, AUTHORS c, Article_Author d \
		where a.venue_VenueId=b.VenueId and a.ArticleId=d.ARTICLES_ArticleId and \
		d.authors_AuthorId=c.AuthorId";
	if (dao->executeCustomConsultativeQuery(query.str())) {
		const char **result;
		while (result = dao->getNextRow()) {
			Object2ObjectOpenHashMap::iterator it = (*(this->node2name_)).find(result[0]);
			if (it == this->node2name_->end()) {
				(*(this->node2name_))[result[0]] = String(result[1]) + " Venue: " + String(result[2]) + " Authors: "  + String(result[3]);
			}
			else {
				it->second.append(", " + String(result[3]));
			}
		}
	}
}

Id2Str::~Id2Str() {
	delete this->node2name_;
}

String Id2Str::getNodebyName(String node) const {
	return (*(this->node2name_))[node];
}
