#ifndef IDENTIFICATIONGENERETOR_H
#define IDENTIFICATIONGENERETOR_H

#include "../redefinitions.h"
#include "../../dao/daoMySql.h"

class IdentificationGeneretor {
protected:
    Dao *dao_;
    String query_;
    String separator_;
public:
    IdentificationGeneretor(Dao* dao, String separator);
    String getQuery() const;
    virtual void fillTheMapping(MapStringString *node2name) = 0;
    virtual ~IdentificationGeneretor();
};

#endif // IDENTIFICATIONGENERETOR_H
