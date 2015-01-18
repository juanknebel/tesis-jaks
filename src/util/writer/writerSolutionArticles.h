#ifndef WRITERSOLUTIONARTICLES_H
#define WRITERSOLUTIONARTICLES_H

#include "writerSolution.h"

class WriterSolutionArticles : public WriterSolution
{
public:
    WriterSolutionArticles(std::string separator) : WriterSolution(separator) {}

    void writeSolution(const std::vector<SnowFlake>& solution, std::string fileName, const Id2Str* node2name, double interSimilarityWeight);

    ~WriterSolutionArticles();
};

#endif // WRITERSOLUTIONARTICLES_H
