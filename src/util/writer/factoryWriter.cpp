//
// Created by zero on 25/09/16.
//

#include "factoryWriter.h"

std::unique_ptr<WriterSolution> FactoryWriter::getTheWriter(std::string element) {
    WriterSolution* theWriter;
    if (element.compare("ARTICLE") == 0) {
        theWriter = new WriterSolutionArticles("\t");
    }

    if (element.compare("AUTHOR") == 0) {
        theWriter = new WriterSolutionAuthors("\t");
    }

    if (element.compare("AFFILIATION") == 0) {
        theWriter = new WriterSolutionAffiliations("\t");
    }

    if (element.compare("FILE") == 0) {
        theWriter = new WritterSolutionFile("\t");
    }

    std::unique_ptr<WriterSolution> theUniqueWriter (theWriter);
    return theUniqueWriter;
}
