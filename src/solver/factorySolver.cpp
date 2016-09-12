//
// Created by zero on 11/09/16.
//

#include "factorySolver.h"

FactorySolver::FactorySolver()
{

}

std::unique_ptr<Solver> FactorySolver::getTheSolver(ProblemInstance* theProblem, std::string algorithm, std::string strategy, int multiplier, double gamma)
{
    int theStrategyId;
    int solverId;
    ProduceAndChooseSolver::RankingStrategy theStrategy = static_cast<ProduceAndChooseSolver::RankingStrategy> (theStrategyId);
    Solver *theSolver;

    switch(solverId) {
        case FactorySolver::ClusterAndPick:
            theSolver = new ClusterAndPickSolver(theProblem);
            break;

        case FactorySolver::SeqScan:
            theSolver = new SequentialScanSolver(theProblem);
            break;

        case FactorySolver::RestrictedHAC:
            theSolver = new RestrictedHACSolver(theProblem);

            if (theStrategy != ProduceAndChooseSolver::RANK_BY_INTRA) {
                dynamic_cast<RestrictedHACSolver *> (theSolver)->setRankingStrategy(theStrategy);
                dynamic_cast<RestrictedHACSolver *> (theSolver)->setInterSimilarityWeight(gamma);
                dynamic_cast<RestrictedHACSolver *> (theSolver)->setNumCandidatesMultiplier(multiplier);
            }

            break;

        case FactorySolver::RestrictedHACSpecific:
            theSolver = new RestrictedHACSWithSpecificItemSolver(theProblem);

            if (theStrategy != ProduceAndChooseSolver::RANK_BY_INTRA) {
                dynamic_cast<RestrictedHACSWithSpecificItemSolver *> (theSolver)->setRankingStrategy(theStrategy);
                dynamic_cast<RestrictedHACSWithSpecificItemSolver *> (theSolver)->setInterSimilarityWeight(gamma);
                dynamic_cast<RestrictedHACSWithSpecificItemSolver *> (theSolver)->setNumCandidatesMultiplier(multiplier);
            }

            break;

        case FactorySolver::RandomBOBO:
            theSolver = new RandomBOBOSolver(theProblem);

            if (theStrategy != ProduceAndChooseSolver::RANK_BY_INTRA) {
                dynamic_cast<RandomBOBOSolver *> (theSolver)->setRankingStrategy(theStrategy);
                dynamic_cast<RandomBOBOSolver *> (theSolver)->setInterSimilarityWeight(gamma);
                dynamic_cast<RandomBOBOSolver *> (theSolver)->setNumCandidatesMultiplier(multiplier);
            }

            break;

        case FactorySolver::RandomSOBO:
            theSolver = new RandomSOBOSolver(theProblem);

            if (theStrategy != ProduceAndChooseSolver::RANK_BY_INTRA) {
                dynamic_cast<RandomSOBOSolver *> (theSolver)->setRankingStrategy(theStrategy);
                dynamic_cast<RandomSOBOSolver *> (theSolver)->setInterSimilarityWeight(gamma);
                dynamic_cast<RandomSOBOSolver *> (theSolver)->setNumCandidatesMultiplier(multiplier);
            }

            break;

        case FactorySolver::ExAnySimSOBO:
            theSolver = new ExhaustiveGreedyAnySimSOBOSolver(theProblem);

            if (theStrategy != ProduceAndChooseSolver::RANK_BY_INTRA) {
                dynamic_cast<ExhaustiveGreedyAnySimSOBOSolver *> (theSolver)->setRankingStrategy(theStrategy);
                dynamic_cast<ExhaustiveGreedyAnySimSOBOSolver *> (theSolver)->setInterSimilarityWeight(gamma);
                dynamic_cast<ExhaustiveGreedyAnySimSOBOSolver *> (theSolver)->setNumCandidatesMultiplier(multiplier);
            }

            break;

        case FactorySolver::ExSumSimSOBO:
            theSolver = new ExhaustiveGreedySumSimSOBOSolver(theProblem);

            if (theStrategy != ProduceAndChooseSolver::RANK_BY_INTRA) {
                dynamic_cast<ExhaustiveGreedySumSimSOBOSolver *> (theSolver)->setRankingStrategy(theStrategy);
                dynamic_cast<ExhaustiveGreedySumSimSOBOSolver *> (theSolver)->setInterSimilarityWeight(gamma);
                dynamic_cast<ExhaustiveGreedySumSimSOBOSolver *> (theSolver)->setNumCandidatesMultiplier(multiplier);
            }

            break;

        case FactorySolver::AllGreedySolver:
            theSolver = new GreedySolver(theProblem);

            if (theStrategy != ProduceAndChooseSolver::RANK_BY_INTRA) {
                dynamic_cast<GreedySolver *> (theSolver)->setRankingStrategy(theStrategy);
                dynamic_cast<GreedySolver *> (theSolver)->setInterSimilarityWeight(gamma);
            }

            break;

        case FactorySolver::EfficientHAC:
            theSolver = new RestrictedEfficientHACSolver(theProblem);

            if (theStrategy != ProduceAndChooseSolver::RANK_BY_INTRA) {
                dynamic_cast<RestrictedEfficientHACSolver *> (theSolver)->setRankingStrategy(theStrategy);
                dynamic_cast<RestrictedEfficientHACSolver *> (theSolver)->setInterSimilarityWeight(gamma);
                dynamic_cast<RestrictedEfficientHACSolver *> (theSolver)->setNumCandidatesMultiplier(multiplier);
            }

            break;

        default:
            throw Exception(__FILE__, __LINE__, "Algoritmo de busqueda inexistente");
    }
    std::unique_ptr<Solver> theUniqueSolver (theSolver);
    return  theUniqueSolver;
}
