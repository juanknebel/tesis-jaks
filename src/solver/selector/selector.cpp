#include "selector.h"

double Selector::scoreSetIntraInter(SnowFlakeVector &selected, SnowFlake candidate, SnowFlakeHelper helper,
                          ProblemInstance problem, double selectedSumIntra, double selectedSumOneMinusInter) {
    double sumIntra = selectedSumIntra + helper.getSumIntraCompat(candidate, problem);
    double sumOneMinusInter = selectedSumOneMinusInter;
    for (auto elem : selected) {
    //for (SnowFlakeVector::iterator it = selected->begin(); it != selected->end(); ++it) {
        sumOneMinusInter += 1.0 - problem.maxPairwiseCompatibility(elem.ids(), candidate.ids());
    }
    double gamma = 1.0 - this->interSimilarityWeight_;
    return (gamma * sumIntra) + ((1.0 - gamma) * sumOneMinusInter);
}

double Selector::scoreSetIntraInterWithSpecificProfile(SnowFlakeVector &selected, SnowFlake candidate, SnowFlakeHelper helper,
                                             ProblemInstance problem, double selectedSumIntra,
                                             double selectedSumOneMinusInter) {
    double sumIntra = selectedSumIntra + helper.getSumIntraCompatWithSpecificProfile(candidate, problem);
    double sumOneMinusInter = selectedSumOneMinusInter;
    for (auto elem : selected) {
        sumOneMinusInter += 1.0 - problem.maxPairwiseCompatibilityWithSpecificProfile(elem.ids(), candidate.ids());
    }
    double gamma = 1.0 - this->interSimilarityWeight_;
    return (gamma * sumIntra) + ((1.0 - gamma) * sumOneMinusInter);
}

double Selector::scoreSetIntraInter(SnowFlakeVector &selected, SnowFlake candidate, SnowFlake candidateTwo,
                          SnowFlakeHelper helper, ProblemInstance problem, double selectedSumIntra,
                          double selectedSumOneMinusInter) {
    double sumIntra = selectedSumIntra + helper.getSumIntraCompatWithSpecificProfile(candidate, problem) +
            helper.getSumIntraCompatWithSpecificProfile(candidateTwo, problem);
    double sumInter = selectedSumOneMinusInter;
    double sumInterTwo = selectedSumOneMinusInter;
    for (auto elem : selected) {
    //for (SnowFlakeVector::iterator it = selected->begin(); it != selected->end(); ++it) {
        sumInter += 1.0 - problem.maxPairwiseCompatibilityWithSpecificProfile(elem.ids(), candidate.ids());
        sumInterTwo += 1.0 - problem.maxPairwiseCompatibilityWithSpecificProfile(elem.ids(), candidateTwo.ids());
    }
    double sumInterCandidates = 1.0 - problem.maxPairwiseCompatibility(candidate.ids(), candidateTwo.ids());
    double sumOneMinusInter = sumInter + sumInterTwo + sumInterCandidates;
    double gamma = 1.0 - this->interSimilarityWeight_;
    return (gamma * sumIntra) + ((1.0 - gamma) * sumOneMinusInter);
}

double Selector::scoreSetIntraInter(SnowFlakeVector &selected, SnowFlake candidate, SnowFlakeHelper helper,
                          ProblemInstance problem, double selectedSumIntra, double selectedSumOneMinusInter,
                          double alpha, double beta) {
    double sumIntra = selectedSumIntra + helper.getSumIntraCompat(candidate, problem);
    double sumOneMinusInter = selectedSumOneMinusInter;
    for (auto elem : selected) {
        sumOneMinusInter += 1.0 - problem.maxPairwiseCompatibility(elem.ids(), candidate.ids());
    }
    double gamma = 1.0 - this->interSimilarityWeight_;
    return (alpha * (gamma * sumIntra)) + (beta * ((1.0 - gamma) * sumOneMinusInter));
}
