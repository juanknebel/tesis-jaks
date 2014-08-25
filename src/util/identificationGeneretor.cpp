#include "identificationGeneretor.h"

IdentificationGeneretor::IdentificationGeneretor(Dao *dao) {
    this->dao = dao;
}

String IdentificationGeneretor::getQuery() const {
    return this->query;
}

IdentificationGeneretor::~IdentificationGeneretor() {

}
