//
// Created by zero on 11/09/16.
//

#ifndef TESIS_JAKS_EXE_ELEMENTARTICLE_H
#define TESIS_JAKS_EXE_ELEMENTARTICLE_H

#include "element.h"
#include "../dao/dao.h"

class ElementArticle : public Element {
public:
    ElementArticle() : Element() {
        this->tableCost_ = "ARTICLES";
        this->tableCompat_ = "SIMILARITY";
        this->tableCover_ = "ARTICLES";
        this->tableConvertionElementToItem_ = "ARTICLE_ITEM";
        this->fieldCost_ = "Cost";
        this->fieldCover_ = "venue_VenueId";
        this->fieldPrimary_ = "ArticleId";
        this->fieldPrimaryDescription_ = "title";
        this->fieldElement_ = "ArticleId";
        this->fieldItem_ = "Item";
        this->fieldItemCompat1_ = "Item";
        this->fieldItemCompat2_ = "Item2";
        this->fieldCompat_ = "Similarity";
        this->elementType_ = "ARTICLE";
    }
    void completeMapping(std::map<std::string, std::string> &id2str, Dao *dao) const;
    ~ElementArticle();
};


#endif //TESIS_JAKS_EXE_ELEMENTARTICLE_H
