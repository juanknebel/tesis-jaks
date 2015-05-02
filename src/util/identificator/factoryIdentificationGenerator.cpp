#include "factoryIdentificationGenerator.h"

FactoryIdentificationGenerator::FactoryIdentificationGenerator() {
}

std::unique_ptr<IdentificationGeneretor> FactoryIdentificationGenerator::getTheIdentificator(Dao* dao, ConfigurationJaks& configFile) {
    IdentificationGeneretor *theIdentification = nullptr;
    if (configFile["element"] == "ARTICLE") {
        theIdentification = new IdentificationGeneretorArticle(dao, "\t");
    }
    if (configFile["element"] == "AUTHOR") {
        theIdentification = new IdentificationGeneretorAuthor(dao, "\t");
    }

    if (configFile["element"] == "AFFILIATION") {
        theIdentification = new IdentificationGeneretorAffiliation(dao, "\t");
    }
    return std::unique_ptr<IdentificationGeneretor> {theIdentification};
}
