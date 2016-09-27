//
// Created by zero on 26/09/16.
//

#include <iostream>
#include "factoryDao.h"
FactoryDao* FactoryDao::theInstance_;

Dao* FactoryDao::getDaoInstance()
{
    if (!this->theDao_->isConnected()) {
        this->theDao_->connect();
    }
    return this->theDao_;
}

std::shared_ptr<FactoryDao> FactoryDao::getInstance(std::string environment)
{
    if (FactoryDao::theInstance_ == nullptr) {
        FactoryDao::theInstance_ = new FactoryDao(environment);
    }

    static std::shared_ptr<FactoryDao> instance = std::shared_ptr<FactoryDao>(FactoryDao::theInstance_);
    return instance;
}

FactoryDao::FactoryDao(std::string environment)
{
    boost::property_tree::ptree pt;
    boost::property_tree::ini_parser::read_ini("Tesis.ini", pt);
    if (environment.compare("RELEASE") == 0) {
        environment = "SectionDatabase";
    }
    if (environment.compare("DEBUG") == 0) {
        environment = "SectionDatabaseDebug";
    }
    if (environment.compare("TEST") == 0) {
        environment = "SectionDatabaseTest";
    }
    std::string database = pt.get<std::string>(environment + ".database");
    std::string user = pt.get<std::string>(environment + ".user");
    std::string password = pt.get<std::string>(environment + ".password");
    std::string server = pt.get<std::string>(environment + ".server");
    this->theDao_ = new DaoQt(database, user, password, server);
}

FactoryDao::~FactoryDao()
{
    /*if (FactoryDao::theInstance_!= nullptr) {
        if (this->theDao_!= nullptr) {
            delete this->theDao_;
            this->theDao_ = nullptr;
        }
        FactoryDao::theInstance_= nullptr;
    }*/
}