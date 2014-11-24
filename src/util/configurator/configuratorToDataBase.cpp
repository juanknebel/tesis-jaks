#include "configuratorToDataBase.h"

ConfiguratorToDataBase::~ConfiguratorToDataBase() {
    delete this->theDao_;
}

Dao* ConfiguratorToDataBase::getDao() {
    return this->theDao_;
}
