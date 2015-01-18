#include "identificationGeneretorAuthor.h"

void IdentificationGeneretorAuthor::fillTheMapping(std::map<std::string, std::string> *node2name) {
    if (this->dao_->executeCustomConsultativeQuery(this->query_)) {
        while (this->dao_->fetch()) {
            std::map<std::string, std::string>::iterator it = (*(node2name)).find(this->dao_->getField(1));
            if (it == node2name->end()) {
                (*(node2name))[this->dao_->getField(1)] = this->dao_->getField(2) + this->separator_ + this->dao_->getField(3);
            }
            else {
                //error no puede pasar!!!
            }
        }
    }
}

IdentificationGeneretorAuthor::~IdentificationGeneretorAuthor() {
}
