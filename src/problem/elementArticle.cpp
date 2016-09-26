//
// Created by zero on 11/09/16.
//

#include "elementArticle.h"

ElementArticle::~ElementArticle()
{

}

void ElementArticle::completeMapping(Dao *dao) const
{
    std::map<std::string, std::string> *id2str = this->node2name_.get();
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
            std::map<std::string, std::string>::iterator it = id2str->find(dao->getField(1));

            if (it == id2str->end()) {
                (*id2str)[dao->getField(0)] = dao->getField(0) + "," + dao->getField(1) + "," + dao->getField(2) + ","  + dao->getField(3);
            }

            else {
                it->second.append(", " + dao->getField(3));
            }
        }
    }
}

void
ElementArticle::writeSolution(const std::vector<SnowFlake> &solution, std::string fileName, double gamma) const
{
    std::map<std::string, std::string> *node2name = this->node2name_.get();
    std::ofstream file(fileName.c_str());
    file << "Bundle" << this->separator_ << "ArticleId" << this->separator_ << "Paper" << this->separator_ << "Venue" << this->separator_ << "Author" << "\n";

    for (auto aFlake : solution) {
        for (auto anElement : aFlake.ids()) {
            std::string node = aFlake.getProblemNode(anElement);
            file << "Bundle " << aFlake.getIdentificator() << this->separator_ << (*node2name)[node] << this->separator_ << "\n";
        }
    }

    file << "Objetive function" << this->separator_ << SnowFlake::objetiveFunction(solution, gamma)<<"\n";
    file << "Inter" << this->separator_ << SnowFlake::getInter(solution) << "\n";
    file << "Intra" << this->separator_ << SnowFlake::getIntra(solution);
    file.close();
}
