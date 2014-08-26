#ifndef WRITERSOLUTION_H
#define WRITERSOLUTION_H

#include "../snowFlake.h"
#include "id2Str.h"
#include "redefinitions.h"

class WriterSolution {
public:
    WriterSolution();

    virtual String showInScreen(std::vector<SnowFlake>& solution,const Id2Str* node2name);

    virtual void writeSolution(const std::vector<SnowFlake>& solution, String fileName, const Id2Str* node2name, Double interSimilarityWeight) = 0;

    virtual ~WriterSolution();
};

#endif // WRITERSOLUTION_H
