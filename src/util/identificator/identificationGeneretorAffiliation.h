#ifndef IDENTIFICATIONGENERETORAFFILIATION_H
#define IDENTIFICATIONGENERETORAFFILIATION_H

#include "identificationGeneretor.h"

class IdentificationGeneretorAffiliation : public IdentificationGeneretor {
public:
    IdentificationGeneretorAffiliation(Dao *dao, std::string separator) : IdentificationGeneretor(dao, separator) {
        this->query_ = "SELECT affiliationId, title, location FROM AFFILIATIONS";
    }

    void fillTheMapping(std::map<std::string, std::string> *node2name);

    ~IdentificationGeneretorAffiliation();
};

#endif // IDENTIFICATIONGENERETORAFFILIATION_H
