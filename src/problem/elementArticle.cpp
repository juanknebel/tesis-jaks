//
// Created by zero on 11/09/16.
//

#include "elementArticle.h"
#include "../dao/factoryDao.h"
#include <boost/property_tree/json_parser.hpp>
namespace pt = boost::property_tree;

ElementArticle::~ElementArticle()
{

}

void ElementArticle::completeMapping() const
{
    std::shared_ptr<FactoryDao> theFactoryDao = FactoryDao::getInstance("RELEASE");
    Dao& dao = theFactoryDao.get()->getDaoInstance();
    std::map<std::string, std::string> *id2str = this->node2name_.get();
    std::string query = "SELECT \
                a.ArticleId as ArticleId \
                ,a.title as Title \
                ,b.name as VenueName \
                ,c.name as Author \
                FROM ARTICLES a, VENUES b, AUTHORS c, Article_Author d \
                WHERE a.venue_VenueId=b.VenueId and a.ArticleId=d.ARTICLES_ArticleId and \
                d.authors_AuthorId=c.AuthorId";

    if (dao.executeCustomConsultativeQuery(query)) {
        while (dao.fetch()) {
            std::map<std::string, std::string>::iterator it = id2str->find(dao.getField(0));

            if (it == id2str->end()) {
                (*id2str)[dao.getField(0)] = dao.getField(0) + this->separator_ + dao.getField(1) + this->separator_ + dao.getField(2) + this->separator_  + dao.getField(3);
            }

            else {
                it->second.append("," + dao.getField(3));
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

std::string ElementArticle::convertToJson(const std::vector<SnowFlake> &solution) const {
    std::shared_ptr<FactoryDao> theFactoryDao = FactoryDao::getInstance("RELEASE");
    Dao& dao = theFactoryDao.get()->getDaoInstance();
    pt::ptree root;

    pt::ptree bundlesList;
    for (auto aFlake : solution) {
        pt::ptree paperList;
        for (auto aNode : aFlake.ids()) {
            std::stringstream query;
            std::string id = aFlake.getProblemNode(aNode);
            query << "select art.title, tpd.distribution, tpd.distribution_KEY from ARTICLES art, TopicProfile_distribution tpd where art.ArticleId = "
                    << id << " and art.topicProfile_identifier = tpd.topicProfile_identifier;";
            dao.executeCustomConsultativeQuery(query.str());
            pt::ptree topicsList;
            std::string articleName;
            while(dao.fetch()) {
                pt::ptree topics;
                articleName = dao.getField(0);
                topics.put("topic", dao.getField(2));
                topics.put("dist", dao.getField(1));
                topicsList.push_back(std::make_pair("", topics));
            }
            pt::ptree paper;
            paper.put("name", articleName);
            paper.add_child("topics", topicsList);
            paperList.push_back(std::make_pair("", paper));
        }
        pt::ptree bundles;
        bundles.put("bundle", aFlake.getIdentificator());
        bundles.add_child("papers", paperList);
        bundlesList.push_back(std::make_pair("", bundles));
    }
    root.add_child("solution", bundlesList);
    std::stringstream jsonString;
    pt::write_json(jsonString, root);
    return jsonString.str();
}
