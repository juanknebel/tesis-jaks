#include "identificationGeneretor.h"

IdentificationGeneretor::IdentificationGeneretor(Dao *dao, String separator) {
    this->dao_ = dao;
    this->separator_ = separator;
}

String IdentificationGeneretor::getQuery() const {
    return this->query_;
}

IdentificationGeneretor::~IdentificationGeneretor() {

}
