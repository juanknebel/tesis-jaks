#ifndef IDENTIFICATIONGENERETOR_H
#define IDENTIFICATIONGENERETOR_H

#include "redefinitions.h"
#include "../dao/daoMySql.h"

class IdentificationGeneretor {
protected:
    Dao *dao;
    String query;
public:
    IdentificationGeneretor(Dao* dao);
    String getQuery() const;
    virtual void fillTheMapping(MapStringString *node2name) = 0;
    virtual ~IdentificationGeneretor();
};

#endif // IDENTIFICATIONGENERETOR_H
