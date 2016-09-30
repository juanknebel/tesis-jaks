//
// Created by zero on 11/09/16.
//

#include "elementAuthor.h"
#include "../dao/dao.h"
#include "../dao/factoryDao.h"

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
    return std::__cxx11::string();
}
