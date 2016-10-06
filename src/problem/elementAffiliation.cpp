//
// Created by zero on 11/09/16.
//

#include "elementAffiliation.h"
#include "../dao/factoryDao.h"
#include "../util/system/exception.h"
#include <boost/property_tree/json_parser.hpp>
namespace pt = boost::property_tree;

ElementAffiliation::~ElementAffiliation()
{

}

void ElementAffiliation::completeMapping() const
{
    std::shared_ptr<FactoryDao> theFactoryDao = FactoryDao::getInstance("RELEASE");
    Dao& dao = theFactoryDao.get()->getDaoInstance();
    std::map<std::string, std::string> *id2str = this->node2name_.get();
    std::string query = "SELECT affiliationId, title, location FROM AFFILIATIONS";
    if (dao.executeCustomConsultativeQuery(query)) {
        while (dao.fetch()) {
            std::map<std::string, std::string>::iterator it = id2str->find(dao.getField(0));

            if (it == id2str->end()) {
                (*id2str)[dao.getField(0)] = dao.getField(1) + this->separator_ + dao.getField(2);
            }

            else {
                throw Exception(__FILE__, __LINE__, "Error executing query to complete mapping");
            }
        }
    }
}

void
ElementAffiliation::writeSolution(const std::vector<SnowFlake> &solution, std::string fileName, double gamma, ProblemInstance &theProblem) const
{
    std::map<std::string, std::string> *node2name = this->node2name_.get();
    std::ofstream file(fileName.c_str());
    file << "Bundle" << this->separator_ << "Title" << this->separator_ << "Location" << "\n";

    for (auto aSnowFlake : solution) {
        for (auto aFlake : aSnowFlake.ids()) {
            std::string node = aFlake.getNodeId();
            file << "Bundle " << aSnowFlake.getIdentificator() << this->separator_ << (*node2name)[node] << this->separator_ << "\n";
        }
    }

    file << "Objetive function" << this->separator_ << SnowFlake::objetiveFunction(solution, gamma, theProblem)<<"\n";
    file << "Inter" << this->separator_ << SnowFlake::getInter(solution, theProblem) << "\n";
    file << "Intra" << this->separator_ << SnowFlake::getIntra(solution, theProblem);
    file.close();
}

std::string ElementAffiliation::convertToJson(const std::vector<SnowFlake> &solution) const {
    std::shared_ptr<FactoryDao> theFactoryDao = FactoryDao::getInstance("RELEASE");
    Dao& dao = theFactoryDao.get()->getDaoInstance();
    pt::ptree root;

    pt::ptree bundlesList;
    for (auto aSnowFlake : solution) {
        pt::ptree affiliationList;
        for (auto aFlake : aSnowFlake.ids()) {
            std::stringstream query;
            std::string id = aFlake.getNodeId();
            query << "select aff.title, tpd.distributionAffiliation,tpd.distribution_KEY from AFFILIATIONS aff, TopicProfileAffiliations tpd where aff.affiliationId = "
                  << id << " and tpd.AFFILIATION_affiliationId = aff.affiliationId;";
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
            pt::ptree affiliation;
            affiliation.put("name", articleName);
            affiliation.add_child("topics", topicsList);
            affiliationList.push_back(std::make_pair("", affiliation));
        }
        pt::ptree bundles;
        bundles.put("bundle", aSnowFlake.getIdentificator());
        bundles.add_child("papers", affiliationList);
        bundlesList.push_back(std::make_pair("", bundles));
    }
    root.add_child("solution", bundlesList);
    std::stringstream jsonString;
    pt::write_json(jsonString, root);
    return jsonString.str();
}
