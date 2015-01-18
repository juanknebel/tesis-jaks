#include "identificationGeneretor.h"

IdentificationGeneretor::IdentificationGeneretor(Dao *dao, std::string separator) {
    this->dao_ = dao;
    this->separator_ = separator;
}

std::string IdentificationGeneretor::getQuery() const {
    return this->query_;
}

IdentificationGeneretor::~IdentificationGeneretor() {

}
