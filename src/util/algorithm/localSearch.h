#ifndef LOCALSEARCH_H
#define LOCALSEARCH_H

#include "../../problem/snowFlake.h"
#include <memory>

using SnowFlakeVector = std::vector<SnowFlake*>;

class LocalSearch {
private:
    struct UsedElements {
        int snowFlakeId;
        int countBetter;
        int countTabu;
    };

public:
    LocalSearch() {}
    SnowFlakeVector execute(int maxIter, SnowFlakeVector& solution, ProblemInstance& theProblem);
};

#endif // LOCALSEARCH_H
