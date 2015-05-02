#include "configuratorToDataBase.h"

Dao* ConfiguratorToDataBase::getDao() {
    return this->theDao_.get();
}
