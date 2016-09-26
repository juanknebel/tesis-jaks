//
// Created by zero on 26/09/16.
//

#ifndef TESIS_JAKS_EXE_FACTORYELEMENT_H
#define TESIS_JAKS_EXE_FACTORYELEMENT_H

#include <memory>
#include "elementFile.h"
#include "elementAffiliation.h"
#include "elementAuthor.h"
#include "elementArticle.h"

class FactoryElement {
private:
    FactoryElement();
public:
    static std::unique_ptr<Element> getTheElement(std::string element);
};


#endif //TESIS_JAKS_EXE_FACTORYELEMENT_H
