//
// Created by zero on 11/09/16.
//

#include "elementArticle.h"
#include "../dao/dao.h"

ElementArticle::~ElementArticle()
{

}

void ElementArticle::completeMapping(std::map<std::string, std::string> &id2str, Dao *dao) const
{
    std::string query = "SELECT \
                a.ArticleId as ArticleId \
                ,a.title as Title \
                ,b.name as VenueName \
                ,c.name as Author \
                FROM ARTICLES a, VENUES b, AUTHORS c, Article_Author d \
                WHERE a.venue_VenueId=b.VenueId and a.ArticleId=d.ARTICLES_ArticleId and \
                d.authors_AuthorId=c.AuthorId";

    if (dao->executeCustomConsultativeQuery(query)) {
        while (dao->fetch()) {
            std::map<std::string, std::string>::iterator it = (id2str).find(dao->getField(1));

            if (it == id2str.end()) {
                (id2str)[dao->getField(0)] = dao->getField(0) + "," + dao->getField(1) + "," + dao->getField(2) + ","  + dao->getField(3);
            }

            else {
                it->second.append(", " + dao->getField(3));
            }
        }
    }
}
