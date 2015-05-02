#include "intraSelector.h"

SnowFlakeVector IntraSelector::getTopSolution(SnowFlakeVector &produced, ProblemInstance &theProblem,
                                              SnowFlakeHelper helper, double interSimilarityWeight, int numRequested) {
    this->interSimilarityWeight_ = interSimilarityWeight;
    SnowFlake::sortByDecresingSumCompat(produced, theProblem);
    int minValue = (int) ((numRequested < produced.size()) ? numRequested : produced.size());
    SnowFlakeVector selected;
    for (int i = 0; i < minValue; ++i) {
        SnowFlake selectedSnowFlake(produced.at(i));
        selected.push_back(selectedSnowFlake);
    }
    return selected;
}
