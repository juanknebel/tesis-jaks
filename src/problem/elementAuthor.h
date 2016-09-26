//
// Created by zero on 11/09/16.
//

#ifndef TESIS_JAKS_EXE_ELEMENTAUTHOR_H
#define TESIS_JAKS_EXE_ELEMENTAUTHOR_H
#include "element.h"
#include "../dao/dao.h"

class ElementAuthor  : public Element {
public:
    ElementAuthor() : Element() {
        this->tableCost_ = "AUTHORS";
        this->tableCompat_ = "SIMILARITY_AUTHOR";
        this->tableCover_ = "ARTICLES";
        this->tableConvertionElementToItem_ = "AUTHOR_ITEM";
        this->fieldCost_ = "Cost";
        this->fieldCover_ = "Affiliation_affiliationId";
        this->fieldPrimary_ = "AuthorId";
        this->fieldPrimaryDescription_ = "name";
        this->fieldElement_ = "AuthorId";
        this->fieldItem_ = "Item";
        this->fieldItemCompat1_ = "Item";
        this->fieldItemCompat2_ = "Item2";
        this->fieldCompat_ = "Similarity";
        this->elementType_ = "AUTHOR";
    }
    void completeMapping(std::map<std::string, std::string> &id2str, Dao *dao) const;
    ~ElementAuthor();
};

#endif //TESIS_JAKS_EXE_ELEMENTAUTHOR_H
