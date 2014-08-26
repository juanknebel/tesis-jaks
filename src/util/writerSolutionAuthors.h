#ifndef WRITERSOLUTIONAUTHORS_H
#define WRITERSOLUTIONAUTHORS_H

#include "writerSolution.h"

class WriterSolutionAuthors : public WriterSolution
{
public:
    WriterSolutionAuthors() : WriterSolution() {}

    void writeSolution(const std::vector<SnowFlake>& solution, String fileName, const Id2Str* node2name, Double interSimilarityWeight);

    ~WriterSolutionAuthors();
};

#endif // WRITERSOLUTIONAUTHORS_H
