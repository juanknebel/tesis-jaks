#ifndef SELECTOR_H
#define SELECTOR_H

#include "../../problem/snowFlake.h"
#include "../../util/redefinitions.h"
#include "../../util/system/exception.h"

typedef std::vector<SnowFlake> SnowFlakeVector;

class Selector {
protected:
    std::string selectorName;
    ProblemInstance* theProblem_;
    Double interSimilarityWeight_;

    Double scoreSetIntraInter(SnowFlakeVector* selected, SnowFlake& candidate, Double selectedSumIntra, Double selectedSumOneMinusInter);

    Double scoreSetIntraInterWithSpecificProfile(SnowFlakeVector* selected, SnowFlake& candidate, Double selectedSumIntra, Double selectedSumOneMinusInter);

    Double scoreSetIntraInter(SnowFlakeVector* selected, SnowFlake& candidate, SnowFlake& candidateTwo, Double selectedSumIntra, Double selectedSumOneMinusInter);

    Double scoreSetIntraInter(SnowFlakeVector* selected, SnowFlake& candidate, Double selectedSumIntra, Double selectedSumOneMinusInter, Double alpha, Double beta);
public:
    Selector(Double interSimilarityWeight, ProblemInstance* theProblem);
    virtual SnowFlakeVector* getTopSolution(SnowFlakeVector* produced, int numRequested) = 0;
    virtual ~Selector();
};

#endif // SELECTOR_H
