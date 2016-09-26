//
// Created by zero on 11/09/16.
//

#include "elementAuthor.h"
#include "../dao/dao.h"

ElementAuthor::~ElementAuthor()
{

}

void ElementAuthor::completeMapping(std::map<std::string, std::string> &id2str, Dao *dao) const
{
    std::string query = "SELECT AuthorId, name, affiliation_title FROM AUTHORS";

    if (dao->executeCustomConsultativeQuery(query)) {
        while (dao->fetch()) {
            std::map<std::string, std::string>::iterator it = (id2str).find(dao->getField(0));

            if (it == id2str.end()) {
                (id2str)[dao->getField(0)] = dao->getField(1) + "," + dao->getField(2);
            }

            else {
                //error no puede pasar!!!
            }
        }
    }
}
