#include "identificationGeneretorAffiliation.h"

void IdentificationGeneretorAffiliation::fillTheMapping(MapStringString *node2name) {
    if (dao->executeCustomConsultativeQuery(query)) {
        while (dao->fetch()) {
            MapStringString::iterator it = (*(node2name)).find(dao->getField(1));
            if (it == node2name->end()) {
                (*(node2name))[dao->getField(1)] = dao->getField(2) + "\t" + dao->getField(3);
            }
            else {
                //error no puede pasar!!!
            }
        }
    }
}

IdentificationGeneretorAffiliation::~IdentificationGeneretorAffiliation() {
}
