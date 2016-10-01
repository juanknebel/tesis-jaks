//
// Created by zero on 11/09/16.
//

#include "elementAuthor.h"
#include "../dao/factoryDao.h"
#include <boost/property_tree/json_parser.hpp>
namespace pt = boost::property_tree;

ElementAuthor::~ElementAuthor()
{

}

void ElementAuthor::completeMapping() const
{
    std::shared_ptr<FactoryDao> theFactoryDao = FactoryDao::getInstance("RELEASE");
    Dao* dao = theFactoryDao.get()->getDaoInstance();
    std::map<std::string, std::string> *id2str = this->node2name_.get();
    std::string query = "SELECT AuthorId, name, affiliation_title FROM AUTHORS";

    if (dao->executeCustomConsultativeQuery(query)) {
        while (dao->fetch()) {
            std::map<std::string, std::string>::iterator it = id2str->find(dao->getField(0));

            if (it == id2str->end()) {
                (*id2str)[dao->getField(0)] = dao->getField(1) + this->separator_ + dao->getField(2);
            }

            else {
                //error no puede pasar!!!
            }
        }
    }
}

void ElementAuthor::writeSolution(const std::vector<SnowFlake> &solution, std::string fileName, double gamma) const
{
    std::map<std::string, std::string> *node2name = this->node2name_.get();
    std::ofstream file(fileName.c_str());
    file << "Bundle" << this->separator_ << "Author" << this->separator_ << "Affiliation" << "\n";

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

std::string ElementAuthor::convertToJson(const std::vector<SnowFlake> &solution) const {
    std::shared_ptr<FactoryDao> theFactoryDao = FactoryDao::getInstance("RELEASE");
    Dao* dao = theFactoryDao.get()->getDaoInstance();
    pt::ptree root;

    pt::ptree bundlesList;
    for (auto aFlake : solution) {
        pt::ptree authorList;
        for (auto aNode : aFlake.ids()) {
            std::stringstream query;
            std::string id = aFlake.getProblemNode(aNode);
            query << "select aut.name, tpd.distributionAuthor,tpd.distribution_KEY from AUTHORS aut, TopicProfileAuthors tpd where aut.AuthorId = "
                  << id << " and tpd.authors_AuthorId = aut.AuthorId;";
            dao->executeCustomConsultativeQuery(query.str());
            pt::ptree topicsList;
            std::string articleName;
            while(dao->fetch()) {
                pt::ptree topics;
                articleName = dao->getField(0);
                topics.put("topic", dao->getField(2));
                topics.put("dist", dao->getField(1));
                topicsList.push_back(std::make_pair("", topics));
            }
            pt::ptree author;
            author.put("name", articleName);
            author.add_child("topics", topicsList);
            authorList.push_back(std::make_pair("", author));
        }
        pt::ptree bundles;
        bundles.put("bundle", aFlake.getIdentificator());
        bundles.add_child("papers", authorList);
        bundlesList.push_back(std::make_pair("", bundles));
    }
    root.add_child("solution", bundlesList);
    std::stringstream jsonString;
    pt::write_json(jsonString, root);
    return jsonString.str();
}
