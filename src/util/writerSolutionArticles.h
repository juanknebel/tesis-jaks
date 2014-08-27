#ifndef WRITERSOLUTIONARTICLES_H
#define WRITERSOLUTIONARTICLES_H

#include "writerSolution.h"

class WriterSolutionArticles : public WriterSolution
{
public:
    WriterSolutionArticles(String separator) : WriterSolution(separator) {}

    void writeSolution(const std::vector<SnowFlake>& solution, String fileName, const Id2Str* node2name, Double interSimilarityWeight);

    ~WriterSolutionArticles();
};

#endif // WRITERSOLUTIONARTICLES_H
