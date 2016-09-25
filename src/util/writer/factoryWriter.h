//
// Created by zero on 25/09/16.
//

#ifndef TESIS_JAKS_EXE_FACTORYWRITER_H
#define TESIS_JAKS_EXE_FACTORYWRITER_H

#include "writerSolutionAffiliations.h"
#include "writerSolutionArticles.h"
#include "writerSolutionAuthors.h"
#include "writterSolutionFile.h"
#include <memory>

class FactoryWriter {
private:
    FactoryWriter();
public:
    static std::unique_ptr<WriterSolution> getTheWriter(std::string element);
};


#endif //TESIS_JAKS_EXE_FACTORYWRITER_H
