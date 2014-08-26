#ifndef IDENTIFICATIONGENERETORAFFILIATION_H
#define IDENTIFICATIONGENERETORAFFILIATION_H

#include "identificationGeneretor.h"

class IdentificationGeneretorAffiliation : public IdentificationGeneretor {
public:
    IdentificationGeneretorAffiliation(Dao *dao, String separator) : IdentificationGeneretor(dao, separator) {
        this->query_ = "SELECT affiliationId, title, location FROM AFFILIATIONS";
    }

    void fillTheMapping(MapStringString *node2name);

    ~IdentificationGeneretorAffiliation();
};

#endif // IDENTIFICATIONGENERETORAFFILIATION_H
