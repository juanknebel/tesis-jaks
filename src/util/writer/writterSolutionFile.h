//
// Created by zero on 05/12/15.
//

#ifndef TESIS_JAKS_EXE_WRITTERSOLUTIONFILE_H
#define TESIS_JAKS_EXE_WRITTERSOLUTIONFILE_H

#include "writerSolution.h"


class WritterSolutionFile : public WriterSolution{
public:
    WritterSolutionFile(String separator) : WriterSolution(separator) {}

    void writeSolution(const std::vector<SnowFlake>& solution, String fileName, const Id2Str* node2name, Double interSimilarityWeight);

    ~WritterSolutionFile();
};


#endif //TESIS_JAKS_EXE_WRITTERSOLUTIONFILE_H
