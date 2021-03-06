//
// Created by zero on 26/09/16.
//

#include <iostream>
#include "factoryDao.h"
FactoryDao* FactoryDao::theInstance_;

Dao & FactoryDao::getDaoInstance()
{
    if (!this->theDao_->isConnected()) {
        this->theDao_->connect();
    }
    return *this->theDao_;
}

std::shared_ptr<FactoryDao> FactoryDao::getInstance(std::string environment)
{
    if (FactoryDao::theInstance_ == nullptr) {
        FactoryDao::theInstance_ = new FactoryDao();
    }

    static std::shared_ptr<FactoryDao> instance = std::shared_ptr<FactoryDao>(FactoryDao::theInstance_);
    return instance;
}

FactoryDao::FactoryDao()
{
    boost::property_tree::ptree pt;
    boost::property_tree::ini_parser::read_ini("Tesis.ini", pt);
    std::string environment = pt.get<std::string>("SectionEnvironment.environment");
    std::string connection;
    if (environment.compare("release") == 0) {
        connection = "SectionDatabase";
    }
    if (environment.compare("debug") == 0) {
        connection = "SectionDatabaseDebug";
    }
    if (environment.compare("test") == 0) {
        connection = "SectionDatabaseTest";
    }
    std::string database = pt.get<std::string>(connection + ".database");
    std::string user = pt.get<std::string>(connection + ".user");
    std::string password = pt.get<std::string>(connection + ".password");
    std::string server = pt.get<std::string>(connection + ".server");
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