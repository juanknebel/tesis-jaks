//
// Created by zero on 11/09/16.
//

#include "elementAffiliation.h"
#include "../dao/dao.h"

ElementAffiliation::~ElementAffiliation()
{

}

void ElementAffiliation::completeMapping(std::map<std::string, std::string> &id2str, Dao *dao) const
{
    std::string query = "SELECT affiliationId, title, location FROM AFFILIATIONS";
    if (dao->executeCustomConsultativeQuery(query)) {
        while (dao->fetch()) {
            std::map<std::string, std::string>::iterator it = (id2str).find(dao->getField(1));

            if (it == id2str.end()) {
                id2str[dao->getField(0)] = dao->getField(1) + "," + dao->getField(2);
            }

            else {
                //error no puede pasar!!!
            }
        }
    }
}
