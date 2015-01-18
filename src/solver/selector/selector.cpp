#include "selector.h"

Selector::Selector(double interSimilarityWeight, ProblemInstance* theProblem) {
    this->interSimilarityWeight_ = interSimilarityWeight;
    this->theProblem_ = theProblem;
}

Selector::~Selector() {
}

double Selector::scoreSetIntraInter(SnowFlakeVector* selected, SnowFlake& candidate, double selectedSumIntra, double selectedSumOneMinusInter) {
    double sumIntra = selectedSumIntra + candidate.getSumIntraCompat();
    double sumOneMinusInter = selectedSumOneMinusInter;
    for (SnowFlakeVector::iterator it = selected->begin(); it != selected->end(); ++it) {
        sumOneMinusInter += 1.0 - this->theProblem_->maxPairwiseCompatibility(it->ids(), candidate.ids());
    }
    double gamma = 1.0 - this->interSimilarityWeight_;
    return (gamma * sumIntra) + ((1.0 - gamma) * sumOneMinusInter);
}

double Selector::scoreSetIntraInterWithSpecificProfile(SnowFlakeVector* selected, SnowFlake& candidate, double selectedSumIntra, double selectedSumOneMinusInter) {
    double sumIntra = selectedSumIntra + candidate.getSumIntraCompatWithSpecificProfile();
    double sumOneMinusInter = selectedSumOneMinusInter;
    for (SnowFlakeVector::iterator it = selected->begin(); it != selected->end(); ++it) {
        sumOneMinusInter += 1.0 - this->theProblem_->maxPairwiseCompatibilityWithSpecificProfile(it->ids(), candidate.ids());
    }
    double gamma = 1.0 - this->interSimilarityWeight_;
    return (gamma * sumIntra) + ((1.0 - gamma) * sumOneMinusInter);
}

double Selector::scoreSetIntraInter(SnowFlakeVector* selected, SnowFlake& candidate, SnowFlake& candidateTwo, double selectedSumIntra, double selectedSumOneMinusInter) {
    double sumIntra = selectedSumIntra + candidate.getSumIntraCompat() + candidateTwo.getSumIntraCompat();
    double sumInter = selectedSumOneMinusInter;
    double sumInterTwo = selectedSumOneMinusInter;
    for (SnowFlakeVector::iterator it = selected->begin(); it != selected->end(); ++it) {
        sumInter += 1.0 - this->theProblem_->maxPairwiseCompatibility(it->ids(), candidate.ids());
        sumInterTwo += 1.0 - this->theProblem_->maxPairwiseCompatibility(it->ids(), candidateTwo.ids());
    }
    double sumInterCandidates = 1.0 - this->theProblem_->maxPairwiseCompatibility(candidate.ids(), candidateTwo.ids());
    double sumOneMinusInter = sumInter + sumInterTwo + sumInterCandidates;
    double gamma = 1.0 - this->interSimilarityWeight_;
    return (gamma * sumIntra) + ((1.0 - gamma) * sumOneMinusInter);
}

double Selector::scoreSetIntraInter(SnowFlakeVector* selected, SnowFlake& candidate, double selectedSumIntra, double selectedSumOneMinusInter, double alpha, double beta) {
    double sumIntra = selectedSumIntra + candidate.getSumIntraCompat();
    double sumOneMinusInter = selectedSumOneMinusInter;
    for (SnowFlakeVector::iterator it = selected->begin(); it != selected->end(); ++it) {
        sumOneMinusInter += 1.0 - this->theProblem_->maxPairwiseCompatibility(it->ids(), candidate.ids());
    }
    double gamma = 1.0 - this->interSimilarityWeight_;
    DEBUG(DBG_DEBUG, "Intra real: " << (gamma * sumIntra) << " - Inter real: " << ((1.0 - gamma) * sumOneMinusInter) << " - Intra: " << (alpha * (gamma * sumIntra)) << " - Inter: " << (beta * ((1.0 - gamma) * sumOneMinusInter)));
    return (alpha * (gamma * sumIntra)) + (beta * ((1.0 - gamma) * sumOneMinusInter));
}
