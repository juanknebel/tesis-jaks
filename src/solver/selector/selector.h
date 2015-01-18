#ifndef SELECTOR_H
#define SELECTOR_H

#include "../../problem/snowFlake.h"
#include "../../util/system/exception.h"

typedef std::vector<SnowFlake> SnowFlakeVector;

class Selector {
protected:
    std::string selectorName;
    ProblemInstance* theProblem_;
    double interSimilarityWeight_;

    double scoreSetIntraInter(SnowFlakeVector* selected, SnowFlake& candidate, double selectedSumIntra, double selectedSumOneMinusInter);

    double scoreSetIntraInterWithSpecificProfile(SnowFlakeVector* selected, SnowFlake& candidate, double selectedSumIntra, double selectedSumOneMinusInter);

    double scoreSetIntraInter(SnowFlakeVector* selected, SnowFlake& candidate, SnowFlake& candidateTwo, double selectedSumIntra, double selectedSumOneMinusInter);

    double scoreSetIntraInter(SnowFlakeVector* selected, SnowFlake& candidate, double selectedSumIntra, double selectedSumOneMinusInter, double alpha, double beta);
public:
    Selector(double interSimilarityWeight, ProblemInstance* theProblem);
    virtual SnowFlakeVector* getTopSolution(SnowFlakeVector* produced, int numRequested) = 0;
    virtual ~Selector();
};

#endif // SELECTOR_H
