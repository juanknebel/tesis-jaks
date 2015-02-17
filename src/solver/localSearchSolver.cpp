#include "localSearchSolver.h"

SnowFlakeVector* LocalSearchSolver::produceManySnowflakes(int numSnowFlakes) {
    IntSet emptyIdSet;
    SnowFlake emptySnowFlake(emptyIdSet, this->problem_);
    SnowFlakeVector *solution = new SnowFlakeVector();
    for (int i = 0; i < numSnowFlakes; ++i) {
        solution->push_back(emptySnowFlake);
    }
    IntSet theIds(this->problem_->getIds());

    int idBestBundle = -1;
    int theBestId = -1;
    Double bestFnObjective = -1.0;

    int idBestWorstBundle = -1;
    int theBestWorstId = -1;
    Double bestWorstFnObjetive = -1.0;


    bool hasBetterFlake = false;
    bool hasBetterWorstFlake = false;
    bool isNotComplete = true;
    int kk = 0;

    while(isNotComplete) {
        Double objective = SnowFlake::objetiveFunction(*solution, this->interSimilarityWeight_);
        bestFnObjective = objective;
        bestWorstFnObjetive = -1.0;
        for(IntSet::iterator it = theIds.begin(); it != theIds.end(); ++it) {
            for (int i = 0; i < numSnowFlakes; ++i) {
                SnowFlake theSnowAtiPosition = (*solution)[i];
                if (this->checkBudgetAndCoverageConstraint(theSnowAtiPosition.ids(), *it)) {
                    IntSet tempIds(theSnowAtiPosition.ids());
                    tempIds.insert(*it);
                    SnowFlake theSnow(tempIds, this->problem_);
                    (*solution)[i] = theSnow;
                    Double newFnObjective = SnowFlake::objetiveFunction(*solution, this->interSimilarityWeight_);
                    if (newFnObjective >= bestFnObjective) {
                        bestFnObjective = newFnObjective;
                        idBestBundle = i;
                        hasBetterFlake = true;
                        theBestId = *it;
                    }
                    else {
                        if (newFnObjective >= bestWorstFnObjetive) {
                            bestWorstFnObjetive = newFnObjective;
                            idBestWorstBundle = i;
                            hasBetterWorstFlake = true;
                            theBestWorstId = *it;
                        }
                    }
                    (*solution)[i] = theSnowAtiPosition;
                }
            }
        }
        if (hasBetterFlake == true) {
            IntSet theNewIdsForBundle((*solution)[idBestBundle].ids());
            theNewIdsForBundle.insert(theBestId);
            SnowFlake theNewBestSnowFlake(theNewIdsForBundle, this->problem_);
            (*solution)[idBestBundle] = theNewBestSnowFlake;
            theIds.erase(theBestId);
        }
        else {
            if (hasBetterWorstFlake == true) {
                IntSet theNewIdsForBundle((*solution)[idBestWorstBundle].ids());
                theNewIdsForBundle.insert(theBestWorstId);
                SnowFlake theNewBestWorstSnowFlake(theNewIdsForBundle, this->problem_);
                (*solution)[idBestWorstBundle] = theNewBestWorstSnowFlake;
                theIds.erase(theBestWorstId);
            }
        }
        isNotComplete = hasBetterFlake || hasBetterWorstFlake;
        hasBetterFlake = false;
        hasBetterWorstFlake = false;
    }
    return solution;
}

int LocalSearchSolver::numToProduce(int numRequested) {
    return numRequested;
}
