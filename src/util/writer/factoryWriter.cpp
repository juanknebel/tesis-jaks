#include "factoryWriter.h"

FactoryWriter::FactoryWriter() {
}

std::unique_ptr<WriterSolution> FactoryWriter::getTheWriter(ConfigurationJaks& configFile,
                                                            SnowFlakeHelper aSnowFlakeHelper) {
    WriterSolution* theWritter = nullptr;
    if (configFile["element"] == "ARTICLE") {
        theWritter = new WriterSolutionArticles("\t", aSnowFlakeHelper);
    }
    if (configFile["element"] == "AUTHOR") {
        theWritter = new WriterSolutionAuthors("\t", aSnowFlakeHelper);
    }

    if (configFile["element"] == "AFFILIATION") {
        theWritter = new WriterSolutionAffiliations("\t", aSnowFlakeHelper);
    }
    return std::unique_ptr<WriterSolution> {theWritter};
}
