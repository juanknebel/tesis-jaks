#include <float.h>
#include "densestSubGraphSelector.h"
#include "../solver.h"

SnowFlakeVector * DensestSubgraphSelector::getTopSolution(SnowFlakeVector *produced, int numRequested) {
    int numProduced = produced->size();
    Double gamma = 1.0 - this->interSimilarityWeight_;
    DEBUG(DBG_DEBUG,"Valor del gamma: "<<gamma);
    MatrixWrapper* w;
    w= new MatrixConcrete(numProduced, numProduced);

    for (int ui = 0; ui < numProduced; ++ui) {
        SnowFlake& u = (*produced)[ui];
        for (int vi = 0; vi < numProduced; ++vi) {
            SnowFlake& v = (*produced)[vi];
            Double val = ((gamma / (2.0 * ((Double) numRequested - 1.0))) * (u.getSumIntraCompat() + v.getSumIntraCompat()))
                    + (1.0 - gamma) * (1.0 - theProblem_->maxPairwiseCompatibility(u.ids(), v.ids()));
            w->set(ui,vi,val);
        }
    }

    IntSet selected = IntSet();
    for (int ui = 0; ui < numProduced; ui++) {
            selected.insert(ui);
    }

    while(selected.size() > numRequested){
        Double minWeightedDegree = FLT_MAX;
        int minElement = -1;
        for (IntSet::iterator ui = selected.begin(); ui != selected.end(); ++ui) {
            Double weightedDegree = 0.0;
            for (IntSet::iterator vi = selected.begin(); vi != selected.end(); ++vi) {
                weightedDegree += w->get(*ui,*vi);
                if (weightedDegree > minWeightedDegree) {
                    break;
                }
            }
            if (weightedDegree < minWeightedDegree) {
                minWeightedDegree = weightedDegree;
                minElement = *ui;
            }
        }
        if (selected.count(minElement) == 0) {
            throw Exception(__FILE__, __LINE__, "Tried to remove element " + convertToString(minElement) + " that does not belong to " + "selected");
        }
        selected.erase(minElement);
    }
    SnowFlakeVector* solution = new SnowFlakeVector();
    for (IntSet::iterator ui = selected.begin(); ui != selected.end(); ++ui) {
        solution->push_back(produced->at(*ui));
    }
    return solution;
}

DensestSubgraphSelector::~DensestSubgraphSelector() {
}
