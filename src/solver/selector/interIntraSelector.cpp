#include "interIntraSelector.h"
#include "../solver.h"

SnowFlakeVector * InterIntraSelector::getTopSolution(SnowFlakeVector *produced, int numRequested) {
    if(this->interSimilarityWeight_ < 0.00) {
        throw Exception(__FILE__, __LINE__, "You need to set the value of inter similarity weight");
    }
    SnowFlake::sortByDecresingSumCompat(*produced);
    SnowFlakeVector available(*produced);
    SnowFlakeVector *selected = new SnowFlakeVector();
    Double currentSumIntra = 0.0;
    Double currentSumOneMinusInter = 0.0;
    while (selected->size() < numRequested && selected->size() < produced->size()) {
        Double maxScore = -1.0;
        int bestCandidateId = -1;
        if (available.size() == 0) {
            throw Exception(__FILE__, __LINE__, "There are no available condidates");
        }
        for (Uint candidateId = 0; candidateId < available.size(); ++candidateId) {
            SnowFlake candidate = available[candidateId];
            //Double score = scoreSetIntraInter(selected, candidate, currentSumIntra, currentSumOneMinusInter);
            Double score = scoreSetIntraInterWithSpecificProfile(selected, candidate, currentSumIntra, currentSumOneMinusInter);
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

InterIntraSelector::~InterIntraSelector() {
}
