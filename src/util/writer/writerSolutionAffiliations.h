#ifndef WRITERSOLUTIONAFFILIATIONS_H
#define WRITERSOLUTIONAFFILIATIONS_H

#include "writerSolution.h"

class WriterSolutionAffiliations : public WriterSolution {
public:
    WriterSolutionAffiliations(std::string separator, SnowFlakeHelper aSnowFlakeHelper) : WriterSolution(separator, aSnowFlakeHelper) {}

    void writeSolution(const std::vector<SnowFlake> &solution, std::string fileName, const Id2Str *node2name,
                       double interSimilarityWeight, ProblemInstance &problem);

    ~WriterSolutionAffiliations();
};

#endif // WRITERSOLUTIONAFFILIATIONS_H
