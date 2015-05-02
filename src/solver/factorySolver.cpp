#include "factorySolver.h"

FactorySolver::FactorySolver() {
}

std::unique_ptr<Solver> FactorySolver::getTheSolver(ConfigurationJaks& configFile, ProblemInstance* theProblem, Selector *theStrategySelector) {
    int solverId = atoi(configFile["solver"].c_str());
    double multiplier = atof(configFile["to_produce"].c_str());
    double interSimilarityWeight = atof(configFile["inter_similarity_weight"].c_str());

    Solver* theSolver = 0;
    switch(solverId) {
        case ClusterAndPick:
            theSolver = new ClusterAndPickSolver(theProblem, theStrategySelector);
            break;
        case SeqScan:
            theSolver = new SequentialScanSolver(theProblem, theStrategySelector);
            break;
        case RestrictedHAC:
            theSolver = new RestrictedHACSolver(theProblem, theStrategySelector);
            dynamic_cast<RestrictedHACSolver *> (theSolver)->setInterSimilarityWeight(interSimilarityWeight);
            dynamic_cast<RestrictedHACSolver *> (theSolver)->setNumCandidatesMultiplier(multiplier);
            break;
        case RestrictedHACSpecific:
            theSolver = new RestrictedHACSWithSpecificItemSolver(theProblem, theStrategySelector);
            dynamic_cast<RestrictedHACSWithSpecificItemSolver *> (theSolver)->setInterSimilarityWeight(interSimilarityWeight);
            dynamic_cast<RestrictedHACSWithSpecificItemSolver *> (theSolver)->setNumCandidatesMultiplier(multiplier);
            break;
        case RandomBOBO:
            theSolver = new RandomBOBOSolver(theProblem, theStrategySelector);
            dynamic_cast<RandomBOBOSolver *> (theSolver)->setInterSimilarityWeight(interSimilarityWeight);
            dynamic_cast<RandomBOBOSolver *> (theSolver)->setNumCandidatesMultiplier(multiplier);
            break;
        case RandomSOBO:
            theSolver = new RandomSOBOSolver(theProblem, theStrategySelector);
            dynamic_cast<RandomSOBOSolver *> (theSolver)->setInterSimilarityWeight(interSimilarityWeight);
            dynamic_cast<RandomSOBOSolver *> (theSolver)->setNumCandidatesMultiplier(multiplier);
            break;
        case ExAnySimSOBO:
            theSolver = new ExhaustiveGreedyAnySimSOBOSolver(theProblem, theStrategySelector);
            dynamic_cast<ExhaustiveGreedyAnySimSOBOSolver *> (theSolver)->setInterSimilarityWeight(interSimilarityWeight);
            dynamic_cast<ExhaustiveGreedyAnySimSOBOSolver *> (theSolver)->setNumCandidatesMultiplier(multiplier);
            break;
        case ExSumSimSOBO:
            theSolver = new ExhaustiveGreedySumSimSOBOSolver(theProblem, theStrategySelector);
            dynamic_cast<ExhaustiveGreedySumSimSOBOSolver *> (theSolver)->setInterSimilarityWeight(interSimilarityWeight);
            dynamic_cast<ExhaustiveGreedySumSimSOBOSolver *> (theSolver)->setNumCandidatesMultiplier(multiplier);
            break;
        case LocalSolver:
            theSolver = new GreedySolver(theProblem, theStrategySelector);
            dynamic_cast<GreedySolver *> (theSolver)->setInterSimilarityWeight(interSimilarityWeight);
            break;
        default:
            throw Exception(__FILE__, __LINE__, "Algoritmo de busqueda inexistente");
    }
    return std::unique_ptr<Solver> {theSolver};
};

std::string FactorySolver::getTheSolverName(ConfigurationJaks& configFile) {
    int solverId = atoi(configFile["solver"].c_str());
    switch(solverId) {
        case FactorySolver::ClusterAndPick:
            return "ClusterAndPick";
            break;
        case FactorySolver::SeqScan:
            return "SeqScan";
            break;
        case FactorySolver::RestrictedHAC:
            return "RestrictedHAC";
            break;
        case FactorySolver::RestrictedHACSpecific:
            return "RestrictedHACSpecific";
            break;
        case FactorySolver::RandomBOBO:
            return "RandomBOBO";
            break;
        case FactorySolver::RandomSOBO:
            return "RandomSOBO";
            break;
        case FactorySolver::ExAnySimSOBO:
            return "ExAnySimSOBO";
            break;
        case FactorySolver::ExSumSimSOBO:
            return "ExSumSimSOBO";
            break;
        case FactorySolver::LocalSolver:
            return "LocalSolver";
            break;
        default:
            return "NN";
            break;
    }
}
