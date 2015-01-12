#include "interIntraTuplesSelector.h"
#include "../solver.h"

SnowFlakeVector * InterIntraTuplesSelector::getTopSolution(SnowFlakeVector *produced, int numRequested) {
    if(this->interSimilarityWeight_ < 0.00) {
        throw Exception(__FILE__, __LINE__, "You need to set the value of inter similarity weight");
    }
    SnowFlake::sortByDecresingSumCompat(*produced);
    SnowFlakeVector available(*produced);
    Uint sizeOfBundles = produced->size();
    bool *canUseSnowFlake = new bool[sizeOfBundles];
    for (Uint i = 0; i < sizeOfBundles; ++i) {
        canUseSnowFlake[i] = true;
    }

    SnowFlakeVector *selected = new SnowFlakeVector();
    Double currentSumIntra = 0.0;
    Double currentSumOneMinusInter = 0.0;
    while (selected->size() < numRequested && selected->size() < produced->size()) {
        Double maxScore = -1.0;
        int bestCandidateId = -1;
        int bestCandidateIdTwo = -1;
        if (available.size() == 0) {
            throw Exception(__FILE__, __LINE__, "There are no available condidates");
        }
        for (Uint candidateId = 0; candidateId < sizeOfBundles; ++candidateId) {
            for (Uint candidateIdTwo = candidateId + 1; candidateIdTwo < sizeOfBundles; ++candidateIdTwo) {
                if (canUseSnowFlake[candidateId] && canUseSnowFlake[candidateIdTwo]) {
                    SnowFlake candidate = available[candidateId];
                    SnowFlake candidateTwo = available[candidateIdTwo];
                    Double score = scoreSetIntraInter(selected, candidate, candidateTwo, currentSumIntra, currentSumOneMinusInter);
                    if (score > maxScore) {
                        bestCandidateId = candidateId;
                        bestCandidateIdTwo = candidateIdTwo;
                        maxScore = score;
                    }
                }
            }
        }

        if (bestCandidateId == -1) {
            throw Exception(__FILE__, __LINE__, "There is no best candidate (available.size()==" + convertToString(static_cast<int> (available.size()))
                    + ", maxScore==" + convertToString(maxScore) + ")");
        }

        //Calcula las nuevas puntuaciones
        SnowFlake bestCandidate = available[bestCandidateId];
        SnowFlake bestCandidateTwo = available[bestCandidateIdTwo];
        currentSumIntra += bestCandidate.getSumIntraCompat() + bestCandidateTwo.getSumIntraCompat();
        Double currentSumInter = currentSumOneMinusInter, currentSumInterTwo = currentSumOneMinusInter;
        for (SnowFlakeVector::iterator it = selected->begin(); it != selected->end(); ++it) {
            currentSumInter += 1.0 - theProblem_->maxPairwiseCompatibility((*it).ids(), bestCandidate.ids());
            currentSumInterTwo += 1.0 - theProblem_->maxPairwiseCompatibility((*it).ids(), bestCandidateTwo.ids());
        }
        Double sumInterCandidates = 1.0 - theProblem_->maxPairwiseCompatibility(bestCandidate.ids(), bestCandidateTwo.ids());
        currentSumOneMinusInter = currentSumInter + currentSumInterTwo + sumInterCandidates;
        //Marco como usado los candidatos usados
        canUseSnowFlake[bestCandidateId] = false;
        canUseSnowFlake[bestCandidateIdTwo] = false;
        //Agrego el elemento a la solucion
        selected->push_back(bestCandidate);
        selected->push_back(bestCandidateTwo);
    }
    return selected;
}

InterIntraTuplesSelector::~InterIntraTuplesSelector() {
}
