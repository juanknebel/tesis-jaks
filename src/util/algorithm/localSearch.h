#ifndef LOCALSEARCH_H
#define LOCALSEARCH_H

#include "../../problem/snowFlake.h"
#include <memory>

typedef std::vector<SnowFlake> SnowFlakeVector;

class LocalSearch {
private:
    std::shared_ptr<ProblemInstance> theProblem_;
    std::shared_ptr<SnowFlakeVector> solution_;
public:
    LocalSearch(std::shared_ptr<SnowFlakeVector> solution, std::shared_ptr<ProblemInstance> theProblem);
    SnowFlakeVector* execute(int maxIter);
};

#endif // LOCALSEARCH_H
