#include "factorySolver.h"

FactorySolver::FactorySolver() {
}

Solver* FactorySolver::instanceTheSolver(int solverId, ProblemInstance* theProblem, int strategyId,
                                         double interSimilarityWeight, double multiplier) {
    ProduceAndChooseSolver::RankingStrategy theStrategy = this->checkAndReturnStrategy(interSimilarityWeight, strategyId);
    Solver* theSolver = 0;
    switch(solverId) {
        case ClusterAndPick:
            theSolver = new ClusterAndPickSolver(theProblem);
            break;
        case SeqScan:
            theSolver = new SequentialScanSolver(theProblem);
            break;
        case RestrictedHAC:
            theSolver = new RestrictedHACSolver(theProblem);
            if (theStrategy != ProduceAndChooseSolver::RANK_BY_INTRA) {
                dynamic_cast<RestrictedHACSolver *> (theSolver)->setRankingStrategy(theStrategy);
                dynamic_cast<RestrictedHACSolver *> (theSolver)->setInterSimilarityWeight(interSimilarityWeight);
                dynamic_cast<RestrictedHACSolver *> (theSolver)->setNumCandidatesMultiplier(multiplier);
            }
            break;
        case RestrictedHACSpecific:
            theSolver = new RestrictedHACSWithSpecificItemSolver(theProblem);
            if (theStrategy != ProduceAndChooseSolver::RANK_BY_INTRA) {
                dynamic_cast<RestrictedHACSWithSpecificItemSolver *> (theSolver)->setRankingStrategy(theStrategy);
                dynamic_cast<RestrictedHACSWithSpecificItemSolver *> (theSolver)->setInterSimilarityWeight(interSimilarityWeight);
                dynamic_cast<RestrictedHACSWithSpecificItemSolver *> (theSolver)->setNumCandidatesMultiplier(multiplier);
            }
            break;
        case RandomBOBO:
            theSolver = new RandomBOBOSolver(theProblem);
            if (theStrategy != ProduceAndChooseSolver::RANK_BY_INTRA) {
                dynamic_cast<RandomBOBOSolver *> (theSolver)->setRankingStrategy(theStrategy);
                dynamic_cast<RandomBOBOSolver *> (theSolver)->setInterSimilarityWeight(interSimilarityWeight);
                dynamic_cast<RandomBOBOSolver *> (theSolver)->setNumCandidatesMultiplier(multiplier);
            }
            break;
        case RandomSOBO:
            theSolver = new RandomSOBOSolver(theProblem);
            if (theStrategy != ProduceAndChooseSolver::RANK_BY_INTRA) {
                dynamic_cast<RandomSOBOSolver *> (theSolver)->setRankingStrategy(theStrategy);
                dynamic_cast<RandomSOBOSolver *> (theSolver)->setInterSimilarityWeight(interSimilarityWeight);
                dynamic_cast<RandomSOBOSolver *> (theSolver)->setNumCandidatesMultiplier(multiplier);
            }
            break;
        case ExAnySimSOBO:
            theSolver = new ExhaustiveGreedyAnySimSOBOSolver(theProblem);
            if (theStrategy != ProduceAndChooseSolver::RANK_BY_INTRA) {
                dynamic_cast<ExhaustiveGreedyAnySimSOBOSolver *> (theSolver)->setRankingStrategy(theStrategy);
                dynamic_cast<ExhaustiveGreedyAnySimSOBOSolver *> (theSolver)->setInterSimilarityWeight(interSimilarityWeight);
                dynamic_cast<ExhaustiveGreedyAnySimSOBOSolver *> (theSolver)->setNumCandidatesMultiplier(multiplier);
            }
            break;
        case ExSumSimSOBO:
            theSolver = new ExhaustiveGreedySumSimSOBOSolver(theProblem);
            if (theStrategy != ProduceAndChooseSolver::RANK_BY_INTRA) {
                dynamic_cast<ExhaustiveGreedySumSimSOBOSolver *> (theSolver)->setRankingStrategy(theStrategy);
                dynamic_cast<ExhaustiveGreedySumSimSOBOSolver *> (theSolver)->setInterSimilarityWeight(interSimilarityWeight);
                dynamic_cast<ExhaustiveGreedySumSimSOBOSolver *> (theSolver)->setNumCandidatesMultiplier(multiplier);
            }
            break;
        case LocalSolver:
        theSolver = new LocalSearchSolver(theProblem);
        if (theStrategy != ProduceAndChooseSolver::RANK_BY_INTRA) {
            dynamic_cast<LocalSearchSolver *> (theSolver)->setInterSimilarityWeight(interSimilarityWeight);
        }
            break;
        default:
            throw Exception(__FILE__, __LINE__, "Algoritmo de busqueda inexistente");
            break;
    }
    return theSolver;
}

ProduceAndChooseSolver::RankingStrategy FactorySolver::checkAndReturnStrategy(double similarity, int strategy) {
    if (similarity != 0.00 && strategy == 0) {
        throw Exception(__FILE__, __LINE__, "If INTER_SIMILARITY_WEIGHT similarity is used, the strategy should be                      #RANK_BY_INTRA_INTER o #RANK_BY_DENSEST_SUBGRAPH)");
    }
    return static_cast<ProduceAndChooseSolver::RankingStrategy> (strategy);
}

Solver* FactorySolver::getTheSolver(int solverId, ProblemInstance* theProblem, int strategyId,
                     double interSimilarityWeight, double multiplier) {
    return this->instanceTheSolver(solverId, theProblem, strategyId, interSimilarityWeight, multiplier);
}

std::string FactorySolver::getTheSolverName(int solverId) {
    switch(solverId) {
        case ClusterAndPick:
            return "ClusterAndPick";
            break;
        case SeqScan:
            return "SeqScan";
            break;
        case RestrictedHAC:
            return "RestrictedHAC";
            break;
        case RestrictedHACSpecific:
            return "RestrictedHACSpecific";
            break;
        case RandomBOBO:
            return "RandomBOBO";
            break;
        case RandomSOBO:
            return "RandomSOBO";
            break;
        case ExAnySimSOBO:
            return "ExAnySimSOBO";
            break;
        case ExSumSimSOBO:
            return "ExSumSimSOBO";
            break;
        case LocalSolver:
            return "LocalSolver";
            break;
    }
}

ProduceAndChooseSolver::RankingStrategy FactorySolver::getTheStrategy(int strategy) {
    return this->checkAndReturnStrategy(0.0, strategy);
}
