//
// Created by zero on 11/09/16.
//

#include "factoryProblem.h"
#include "elementFile.h"
#include "elementAffiliation.h"
#include "elementArticle.h"
#include "elementAuthor.h"
#include "../dao/daoQt.h"
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>

FactoryProblem::FactoryProblem()
{

}

std::unique_ptr<ProblemInstance> FactoryProblem::getTheProblem(const Element *element, double budget)
{
    boost::property_tree::ptree pt;
    boost::property_tree::ini_parser::read_ini("Tesis.ini", pt);

    if (element->getElementType().compare("FILE") == 0) {
        std::string directoryOfWork = pt.get<std::string>("SectionFile.directoryOfWork");
        std::unique_ptr<ProblemInstance> theUniqueProblemFile(new ProblemInstanceFromFiles(directoryOfWork + element->getFileCosts(),
                                                        directoryOfWork + element->getFileCompat(),
                                                        directoryOfWork + element->getFileCover(), budget));
        return std::move(theUniqueProblemFile);
    }
    else {
        std::string database = pt.get<std::string>("SectionDatabase.database");
        std::string user = pt.get<std::string>("SectionDatabase.user");
        std::string password = pt.get<std::string>("SectionDatabase.password");
        std::string server = pt.get<std::string>("SectionDatabase.server");
        Dao* theDao = new DaoQt(database, user, password, server);
        theDao->connect();
        std::unique_ptr<ProblemInstance> theUniqueProblemDb(new ProblemInstanceFromDataBase(theDao, element->getTableCost(), element->getTableCompat(),
                                                                                            element->getTableCover(), element->getTableConvertionElementToItem(),
                                                                                            element->getFieldCost(), element->getFieldCompat(),
                                                                                            element->getFieldCover(), element->getFieldPrimary(),
                                                                                            element->getFieldPrimaryDescription(), element->getFieldItem(),
                                                                                            element->getFieldItemCompat1(), element->getFieldItemCompat2(), budget));
        return std::move(theUniqueProblemDb);
    }
}
