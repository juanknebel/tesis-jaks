#ifndef WRITERSOLUTIONAFFILIATIONS_H
#define WRITERSOLUTIONAFFILIATIONS_H

#include "writerSolution.h"

class WriterSolutionAffiliations : public WriterSolution {
public:
    WriterSolutionAffiliations() : WriterSolution() {}

    void writeSolution(const std::vector<SnowFlake>& solution, String fileName, const Id2Str* node2name, Double interSimilarityWeight);

    ~WriterSolutionAffiliations();
};

#endif // WRITERSOLUTIONAFFILIATIONS_H
