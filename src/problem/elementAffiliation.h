//
// Created by zero on 11/09/16.
//

#ifndef TESIS_JAKS_EXE_ELEMENTAFFILIATION_H
#define TESIS_JAKS_EXE_ELEMENTAFFILIATION_H
#include "element.h"
#include "../dao/dao.h"
#include "snowFlake.h"

class ElementAffiliation : public Element {
private:
    void completeMapping() const;
public:
    ElementAffiliation() : Element() {
        this->tableCost_ = "AFFILIATIONS";
        this->tableCompat_ = "SIMILARITY_AFFILIATIONS";
        this->tableCover_ = "AFFILIATIONS";
        this->tableConvertionElementToItem_ = "AFFILIATION_ITEM";
        this->fieldCost_ = "Cost";
        this->fieldCover_ = "locationId";
        this->fieldPrimary_ = "affiliationId";
        this->fieldPrimaryDescription_ = "title";
        this->fieldElement_ = "affiliationId";
        this->fieldItem_ = "Item";
        this->fieldItemCompat1_ = "Item";
        this->fieldItemCompat2_ = "Item2";
        this->fieldCompat_ = "Similarity";
        this->elementType_ = "AFFILIATION";
        completeMapping();
    }
    void writeSolution(const std::vector<SnowFlake> &solution, std::string fileName, double gamma) const;
    ~ElementAffiliation();
};


#endif //TESIS_JAKS_EXE_ELEMENTAFFILIATION_H
