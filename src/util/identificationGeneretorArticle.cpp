#include "identificationGeneretorArticle.h"

void IdentificationGeneretorArticle::fillTheMapping(MapStringString *node2name) {
    if (this->dao_->executeCustomConsultativeQuery(this->query_)) {
        while (this->dao_->fetch()) {
            MapStringString::iterator it = (*(node2name)).find(this->dao_->getField(1));
            if (it == node2name->end()) {
                (*(node2name))[this->dao_->getField(1)] = this->dao_->getField(2) + this->separator_ + this->dao_->getField(3) + this->separator_  + this->dao_->getField(4);
            }
            else {
                it->second.append(", " + this->dao_->getField(4));
            }
        }
    }
}

IdentificationGeneretorArticle::~IdentificationGeneretorArticle() {
}
