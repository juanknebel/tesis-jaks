#include "factoryIdentificationGenerator.h"

FactoryIdentificationGenerator::FactoryIdentificationGenerator() {
}

IdentificationGeneretor* FactoryIdentificationGenerator::getTheIdentificator(Dao* dao, ConfigurationJaks& configFile) {
    if (configFile["element"] == "ARTICLE") {
        return new IdentificationGeneretorArticle(dao, "\t");
    }
    if (configFile["element"] == "AUTHOR") {
        return new IdentificationGeneretorAuthor(dao, "\t");
    }

    if (configFile["element"] == "AFFILIATION") {
        return new IdentificationGeneretorAffiliation(dao, "\t");
    }
}
