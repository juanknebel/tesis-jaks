#include "factoryWriter.h"
FactoryWriter::FactoryWriter() {
}

WriterSolution* FactoryWriter::getTheWriter(ConfigurationJaks& configFile) {
    if (configFile["element"] == "ARTICLE") {
        return new WriterSolutionArticles("\t");
    }
    if (configFile["element"] == "AUTHOR") {
        return new WriterSolutionAuthors("\t");
    }
    if (configFile["element"] == "AFFILIATION") {
        return new WriterSolutionAffiliations("\t");
    }
    if (configFile["use_data_from_db"] == "0") {
        return new WritterSolutionFile("\t");
    }
}
