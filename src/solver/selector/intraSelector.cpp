#include "intraSelector.h"

SnowFlakeVector* IntraSelector::getTopSolution(SnowFlakeVector* produced, int numRequested) {
    SnowFlake::sortByDecresingSumCompat(*produced);
    int minValue = ((numRequested < produced->size()) ? numRequested : produced->size());
    SnowFlakeVector* selected = new SnowFlakeVector();
    for (int i = 0; i < minValue; ++i) {
        SnowFlake selectedSnowFlake(produced->at(i));
        selected->push_back(selectedSnowFlake);
    }
    return selected;
}

IntraSelector::~IntraSelector() {
}
