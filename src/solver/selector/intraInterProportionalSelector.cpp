#include "intraInterProportionalSelector.h"
#include "../solver.h"

SnowFlakeVector * IntraInterProportionalSelector::getTopSolution(SnowFlakeVector *produced, int numRequested) {
    if(this->interSimilarityWeight_ < 0.00) {
        throw Exception(__FILE__, __LINE__, "You need to set the value of inter similarity weight");
    }
    SnowFlake::sortByDecresingSumCompat(*produced);
    SnowFlakeVector available(*produced);
    SnowFlakeVector *selected = new SnowFlakeVector();
    double currentSumIntra = 0.0;
    double currentSumOneMinusInter = 0.0;
    while (selected->size() < numRequested && selected->size() < produced->size()) {
        double maxScore = -1.0;
        int bestCandidateId = -1;
        if (available.size() == 0) {
            throw Exception(__FILE__, __LINE__, "There are no available condidates");
        }
        int theSize = selected->size() + 1;
        for (unsigned int candidateId = 0; candidateId < available.size(); ++candidateId) {
            double alpha = (double) numRequested / theSize;
            double beta = 0.0;
            if (theSize == 1) {
                beta = 1.0;
            }
            else {
                beta = alpha * (double) ((numRequested - 1) / (theSize - 1));
            }
            SnowFlake candidate = available[candidateId];
            double score = scoreSetIntraInter(selected, candidate, currentSumIntra, currentSumOneMinusInter, alpha, beta);
            if (score > maxScore) {
                bestCandidateId = candidateId;
                maxScore = score;
            }
        }

        if (bestCandidateId == -1) {
            throw Exception(__FILE__, __LINE__, "There is no best candidate (available.size()==" + convertToString(static_cast<int> (available.size()))
                    + ", maxScore==" + convertToString(maxScore) + ")");
        }

        //Calcula las nuevas puntuaciones
        SnowFlake bestCandidate = available[bestCandidateId];
        currentSumIntra += bestCandidate.getSumIntraCompat();
        for (SnowFlakeVector::iterator it = selected->begin(); it != selected->end(); ++it) {
            currentSumOneMinusInter += 1.0 - theProblem_->maxPairwiseCompatibility((*it).ids(), bestCandidate.ids());
        }

        //Borro el candidato que ya use
        available.erase(available.begin() + bestCandidateId);
        //Agrego el elemento a la solucion
        selected->push_back(bestCandidate);
    }
    return selected;
}

IntraInterProportionalSelector::~IntraInterProportionalSelector(){
}
