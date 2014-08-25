#include "identificationGeneretorArticle.h"

void IdentificationGeneretorArticle::fillTheMapping(MapStringString *node2name) {
    if (dao->executeCustomConsultativeQuery(query)) {
        while (dao->fetch()) {
            MapStringString::iterator it = (*(node2name)).find(dao->getField(1));
            if (it == node2name->end()) {
                (*(node2name))[dao->getField(1)] = dao->getField(2) + "\t" + dao->getField(3) + "\t"  + dao->getField(4);
            }
            else {
                it->second.append(", " + dao->getField(4));
            }
        }
    }
}

IdentificationGeneretorArticle::~IdentificationGeneretorArticle() {
}
