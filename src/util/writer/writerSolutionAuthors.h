#ifndef WRITERSOLUTIONAUTHORS_H
#define WRITERSOLUTIONAUTHORS_H

#include "writerSolution.h"

class WriterSolutionAuthors : public WriterSolution
{
public:
    WriterSolutionAuthors(std::string separator, SnowFlakeHelper aSnowFlakeHelper) : WriterSolution(separator, aSnowFlakeHelper) {}

    void writeSolution(const std::vector<SnowFlake> &solution, std::string fileName, const Id2Str *node2name,
                       double interSimilarityWeight, ProblemInstance &problem);

    ~WriterSolutionAuthors();
};

#endif // WRITERSOLUTIONAUTHORS_H
