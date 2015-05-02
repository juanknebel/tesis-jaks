#include "interIntraTuplesSelector.h"


SnowFlakeVector InterIntraTuplesSelector::getTopSolution(SnowFlakeVector &produced, ProblemInstance &theProblem,
                                                         SnowFlakeHelper helper, double interSimilarityWeight,
                                                         int numRequested) {
    this->interSimilarityWeight_ = interSimilarityWeight;
    if(this->interSimilarityWeight_ < 0.00) {
        throw Exception(__FILE__, __LINE__, "You need to set the value of inter similarity weight");
    }
    SnowFlake::sortByDecresingSumCompat(produced, theProblem);
    SnowFlakeVector available(produced);
    int sizeOfBundles = produced.size();
    bool *canUseSnowFlake = new bool[sizeOfBundles];
    for (unsigned int i = 0; i < sizeOfBundles; ++i) {
        canUseSnowFlake[i] = true;
    }

    SnowFlakeVector selected;
    double currentSumIntra = 0.0;
    double currentSumOneMinusInter = 0.0;
    while (selected.size() < numRequested && selected.size() < produced.size()) {
        double maxScore = -1.0;
        int bestCandidateId = -1;
        int bestCandidateIdTwo = -1;
        if (available.size() == 0) {
            throw Exception(__FILE__, __LINE__, "There are no available condidates");
        }
        for (unsigned int candidateId = 0; candidateId < sizeOfBundles; ++candidateId) {
            for (unsigned int candidateIdTwo = candidateId + 1; candidateIdTwo < sizeOfBundles; ++candidateIdTwo) {
                if (canUseSnowFlake[candidateId] && canUseSnowFlake[candidateIdTwo]) {
                    SnowFlake candidate = available[candidateId];
                    SnowFlake candidateTwo = available[candidateIdTwo];
                    double score = scoreSetIntraInter(selected, candidate, candidateTwo, helper, theProblem,
                                                      currentSumIntra, currentSumOneMinusInter);
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
        currentSumIntra += helper.getSumIntraCompat(bestCandidate, theProblem) +
                helper.getSumIntraCompat(bestCandidateTwo, theProblem);
        double currentSumInter = currentSumOneMinusInter, currentSumInterTwo = currentSumOneMinusInter;
        for (auto elem : selected) {
            currentSumInter += 1.0 - theProblem.maxPairwiseCompatibility(elem.ids(), bestCandidate.ids());
            currentSumInterTwo += 1.0 - theProblem.maxPairwiseCompatibility(elem.ids(), bestCandidateTwo.ids());
        }
        double sumInterCandidates = 1.0 - theProblem.maxPairwiseCompatibility(bestCandidate.ids(), bestCandidateTwo.ids());
        currentSumOneMinusInter = currentSumInter + currentSumInterTwo + sumInterCandidates;
        //Marco como usado los candidatos usados
        canUseSnowFlake[bestCandidateId] = false;
        canUseSnowFlake[bestCandidateIdTwo] = false;
        //Agrego el elemento a la solucion
        selected.push_back(bestCandidate);
        selected.push_back(bestCandidateTwo);
    }
    return selected;
}
