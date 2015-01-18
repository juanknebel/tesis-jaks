#ifndef IDENTIFICATIONGENERETOR_H
#define IDENTIFICATIONGENERETOR_H

#include "../../dao/daoMySql.h"

class IdentificationGeneretor {
protected:
    Dao *dao_;
    std::string query_;
    std::string separator_;
public:
    IdentificationGeneretor(Dao* dao, std::string separator);
    std::string getQuery() const;
    virtual void fillTheMapping(std::map<std::string, std::string> *node2name) = 0;
    virtual ~IdentificationGeneretor();
};

#endif // IDENTIFICATIONGENERETOR_H
