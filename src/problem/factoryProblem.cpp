//
// Created by zero on 11/09/16.
//

#include "factoryProblem.h"
#include "elementFile.h"
#include "elementAffiliation.h"
#include "elementArticle.h"
#include "elementAuthor.h"
#include "../dao/daoMySql.h"
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>

FactoryProblem::FactoryProblem()
{

}

std::unique_ptr<ProblemInstance> FactoryProblem::getTheProblem(std::string element, double budget)
{
    boost::property_tree::ptree pt;
    boost::property_tree::ini_parser::read_ini("Tesis.ini", pt);

    if (element.compare("FILE")) {
        std::string directoryOfWork = pt.get<std::string>("SectionFile.directoryOfWork");
        ElementFile anElement;
        std::unique_ptr<ProblemInstance> theUniqueProblemFile(new ProblemInstanceFromFiles(directoryOfWork + anElement.getFileCosts(),
                                                        directoryOfWork + anElement.getFileCompat(),
                                                        directoryOfWork + anElement.getFileCover(), budget));
        return std::move(theUniqueProblemFile);
    }
    else {
        std::string database = pt.get<std::string>("SectionDatabase.server");
        std::string user = pt.get<std::string>("SectionDatabase.user");
        std::string password = pt.get<std::string>("SectionDatabase.password");
        std::string server = pt.get<std::string>("SectionDatabase.database");
        Dao* theDao = new DaoMySql(database, user, password, server);
        theDao->connect();
        Element * anElementFromDb;

        if (element.compare("AUTHOR")) {
            anElementFromDb = new ElementAuthor();
        }

        if (element.compare("ARTICLE")) {
            anElementFromDb = new ElementArticle();
        }

        if (element.compare("AFFILIATION")) {
            anElementFromDb = new ElementAffiliation();
        }
        std::unique_ptr<ProblemInstance> theUniqueProblemDb(new ProblemInstanceFromDataBase(theDao, anElementFromDb->getTableCost(), anElementFromDb->getTableCompat(),
                                                            anElementFromDb->getTableCover(), anElementFromDb->getTableConvertionElementToItem(),
                                                            anElementFromDb->getFieldCost(), anElementFromDb->getFieldCompat(),
                                                            anElementFromDb->getFieldCover(), anElementFromDb->getFieldPrimary(),
                                                            anElementFromDb->getFieldPrimaryDescription(), anElementFromDb->getFieldItem(),
                                                            anElementFromDb->getFieldItemCompat1(), anElementFromDb->getFieldItemCompat2(), budget));
        delete anElementFromDb;
        return std::move(theUniqueProblemDb);
    }
}
