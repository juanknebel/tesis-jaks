//
// Created by zero on 19/04/15.
//

#ifndef LOCALSEARCH_H
#define LOCALSEARCH_H

#include "../../problem/snowFlake.h"
#include <memory>

using SnowFlakeVector = std::vector<SnowFlake*>;

class LocalSearch {
private:
    std::shared_ptr<ProblemInstance> theProblem_;
    SnowFlakeVector solution_;
public:
    LocalSearch(SnowFlakeVector solution, std::shared_ptr<ProblemInstance> theProblem);
    SnowFlakeVector execute(int maxIter);
};


#endif //LOCALSEARCH_H
