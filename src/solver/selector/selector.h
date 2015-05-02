#ifndef SELECTOR_H
#define SELECTOR_H

#include "../../problem/snowFlake.h"
#include "../../util/system/exception.h"
#include "../../problem/snowFlakeHelper.h"

typedef std::vector<SnowFlake> SnowFlakeVector;

class Selector {
protected:
    std::string selectorName;
    double interSimilarityWeight_;

    double scoreSetIntraInter(SnowFlakeVector &selected, SnowFlake candidate, SnowFlakeHelper helper,
                              ProblemInstance problem, double selectedSumIntra, double selectedSumOneMinusInter);

    double scoreSetIntraInterWithSpecificProfile(SnowFlakeVector &selected, SnowFlake candidate, SnowFlakeHelper helper,
                                                 ProblemInstance problem, double selectedSumIntra,
                                                 double selectedSumOneMinusInter);

    double scoreSetIntraInter(SnowFlakeVector &selected, SnowFlake candidate, SnowFlake candidateTwo,
                              SnowFlakeHelper helper, ProblemInstance problem, double selectedSumIntra,
                              double selectedSumOneMinusInter);

    double scoreSetIntraInter(SnowFlakeVector &selected, SnowFlake candidate, SnowFlakeHelper helper,
                              ProblemInstance problem, double selectedSumIntra, double selectedSumOneMinusInter,
                              double alpha, double beta);
public:
    Selector() {
        this->interSimilarityWeight_ = -1;
    }

    virtual SnowFlakeVector getTopSolution(SnowFlakeVector &produced, ProblemInstance &theProblem,
                                           SnowFlakeHelper helper, double interSimilarityWeight, int numRequested) = 0;
    virtual ~Selector() {}
};

#endif // SELECTOR_H
