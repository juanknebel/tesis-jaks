#ifndef FACTORYIDENTIFICATIONGENERATOR_H
#define FACTORYIDENTIFICATIONGENERATOR_H

#include "identificationGeneretorAffiliation.h"
#include "identificationGeneretorArticle.h"
#include "identificationGeneretorAuthor.h"
#include "../configurator/configurationJaks.h"
#include "../../dao/dao.h"
#include <memory>

class FactoryIdentificationGenerator {
private:
    FactoryIdentificationGenerator();
public:
    static std::unique_ptr<IdentificationGeneretor> getTheIdentificator(Dao* dao, ConfigurationJaks& configFile);
};

#endif // FACTORYIDENTIFICATIONGENERATOR_H
