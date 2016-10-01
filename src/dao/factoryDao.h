//
// Created by zero on 26/09/16.
//

#ifndef TESIS_JAKS_EXE_FACTORYDAO_H
#define TESIS_JAKS_EXE_FACTORYDAO_H

#include "daoQt.h"
#include <memory>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>

class FactoryDao {
private:
    Dao* theDao_;
    static FactoryDao* theInstance_;
    FactoryDao();

public:
    static std::shared_ptr<FactoryDao> getInstance(std::string environment);
    Dao *getDaoInstance();
    virtual ~FactoryDao();
};


#endif //TESIS_JAKS_EXE_FACTORYDAO_H