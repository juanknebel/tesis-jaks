#ifndef WRITERSOLUTIONARTICLES_H
#define WRITERSOLUTIONARTICLES_H

#include "writerSolution.h"

class WriterSolutionArticles : public WriterSolution
{
public:
    WriterSolutionArticles(std::string separator, SnowFlakeHelper aSnowFlakeHelper) : WriterSolution(separator, aSnowFlakeHelper) {}

    void writeSolution(const std::vector<SnowFlake> &solution, std::string fileName, const Id2Str *node2name,
                       double interSimilarityWeight, ProblemInstance &problem);

    ~WriterSolutionArticles();
};

#endif // WRITERSOLUTIONARTICLES_H
