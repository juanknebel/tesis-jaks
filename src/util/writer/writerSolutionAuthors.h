#ifndef WRITERSOLUTIONAUTHORS_H
#define WRITERSOLUTIONAUTHORS_H

#include "writerSolution.h"

class WriterSolutionAuthors : public WriterSolution
{
public:
    WriterSolutionAuthors(std::string separator) : WriterSolution(separator) {}

    void writeSolution(const std::vector<SnowFlake>& solution, std::string fileName, const Id2Str* node2name, double interSimilarityWeight);

    ~WriterSolutionAuthors();
};

#endif // WRITERSOLUTIONAUTHORS_H
