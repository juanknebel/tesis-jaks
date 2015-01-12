#include "selector.h"

Selector::Selector(Double interSimilarityWeight, ProblemInstance* theProblem) {
    this->interSimilarityWeight_ = interSimilarityWeight;
    this->theProblem_ = theProblem;
}

Selector::~Selector() {
}

Double Selector::scoreSetIntraInter(SnowFlakeVector* selected, SnowFlake& candidate, Double selectedSumIntra, Double selectedSumOneMinusInter) {
    Double sumIntra = selectedSumIntra + candidate.getSumIntraCompat();
    Double sumOneMinusInter = selectedSumOneMinusInter;
    for (SnowFlakeVector::iterator it = selected->begin(); it != selected->end(); ++it) {
        sumOneMinusInter += 1.0 - this->theProblem_->maxPairwiseCompatibility(it->ids(), candidate.ids());
    }
    Double gamma = 1.0 - this->interSimilarityWeight_;
    return (gamma * sumIntra) + ((1.0 - gamma) * sumOneMinusInter);
}

Double Selector::scoreSetIntraInterWithSpecificProfile(SnowFlakeVector* selected, SnowFlake& candidate, Double selectedSumIntra, Double selectedSumOneMinusInter) {
    Double sumIntra = selectedSumIntra + candidate.getSumIntraCompatWithSpecificProfile();
    Double sumOneMinusInter = selectedSumOneMinusInter;
    for (SnowFlakeVector::iterator it = selected->begin(); it != selected->end(); ++it) {
        sumOneMinusInter += 1.0 - this->theProblem_->maxPairwiseCompatibilityWithSpecificProfile(it->ids(), candidate.ids());
    }
    Double gamma = 1.0 - this->interSimilarityWeight_;
    return (gamma * sumIntra) + ((1.0 - gamma) * sumOneMinusInter);
}

Double Selector::scoreSetIntraInter(SnowFlakeVector* selected, SnowFlake& candidate, SnowFlake& candidateTwo, Double selectedSumIntra, Double selectedSumOneMinusInter) {
    Double sumIntra = selectedSumIntra + candidate.getSumIntraCompat() + candidateTwo.getSumIntraCompat();
    Double sumInter = selectedSumOneMinusInter;
    Double sumInterTwo = selectedSumOneMinusInter;
    for (SnowFlakeVector::iterator it = selected->begin(); it != selected->end(); ++it) {
        sumInter += 1.0 - this->theProblem_->maxPairwiseCompatibility(it->ids(), candidate.ids());
        sumInterTwo += 1.0 - this->theProblem_->maxPairwiseCompatibility(it->ids(), candidateTwo.ids());
    }
    Double sumInterCandidates = 1.0 - this->theProblem_->maxPairwiseCompatibility(candidate.ids(), candidateTwo.ids());
    Double sumOneMinusInter = sumInter + sumInterTwo + sumInterCandidates;
    Double gamma = 1.0 - this->interSimilarityWeight_;
    return (gamma * sumIntra) + ((1.0 - gamma) * sumOneMinusInter);
}

Double Selector::scoreSetIntraInter(SnowFlakeVector* selected, SnowFlake& candidate, Double selectedSumIntra, Double selectedSumOneMinusInter, Double alpha, Double beta) {
    Double sumIntra = selectedSumIntra + candidate.getSumIntraCompat();
    Double sumOneMinusInter = selectedSumOneMinusInter;
    for (SnowFlakeVector::iterator it = selected->begin(); it != selected->end(); ++it) {
        sumOneMinusInter += 1.0 - this->theProblem_->maxPairwiseCompatibility(it->ids(), candidate.ids());
    }
    Double gamma = 1.0 - this->interSimilarityWeight_;
    DEBUG(DBG_DEBUG, "Intra real: " << (gamma * sumIntra) << " - Inter real: " << ((1.0 - gamma) * sumOneMinusInter) << " - Intra: " << (alpha * (gamma * sumIntra)) << " - Inter: " << (beta * ((1.0 - gamma) * sumOneMinusInter)));
    return (alpha * (gamma * sumIntra)) + (beta * ((1.0 - gamma) * sumOneMinusInter));
}
