#include "factorySolverOLD.h"

FactorySolverOLD::FactorySolverOLD()
{
}

Solver* FactorySolverOLD::getTheSolver(ConfigurationJaks& configFile, ProblemInstance* theProblem)
{
	int solverId = atoi(configFile["solver"].c_str());
	double multiplier = atof(configFile["to_produce"].c_str());
	double interSimilarityWeight = atof(configFile["inter_similarity_weight"].c_str());

	ProduceAndChooseSolver::RankingStrategy theStrategy = FactorySolverOLD::getTheStrategy(configFile);
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

	case AllGreedySolver:
		theSolver = new GreedySolver(theProblem);

		if (theStrategy != ProduceAndChooseSolver::RANK_BY_INTRA) {
			dynamic_cast<GreedySolver *> (theSolver)->setRankingStrategy(theStrategy);
			dynamic_cast<GreedySolver *> (theSolver)->setInterSimilarityWeight(interSimilarityWeight);
		}

		break;

	case EfficientHAC:
		theSolver = new RestrictedEfficientHACSolver(theProblem);

		if (theStrategy != ProduceAndChooseSolver::RANK_BY_INTRA) {
			dynamic_cast<RestrictedEfficientHACSolver *> (theSolver)->setRankingStrategy(theStrategy);
			dynamic_cast<RestrictedEfficientHACSolver *> (theSolver)->setInterSimilarityWeight(interSimilarityWeight);
			dynamic_cast<RestrictedEfficientHACSolver *> (theSolver)->setNumCandidatesMultiplier(multiplier);
		}

		break;

	default:
		throw Exception(__FILE__, __LINE__, "Algoritmo de busqueda inexistente");
		break;
	}

	return theSolver;
}

std::string FactorySolverOLD::getTheSolverName(ConfigurationJaks& configFile)
{
	int solverId = atoi(configFile["solver"].c_str());

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

	case AllGreedySolver:
		return "GreedySolver";
		break;

	case EfficientHAC:
		return "RestrictedEfficientHAC";
		break;

	default:
		return "ERROR";
		break;
	}
}

ProduceAndChooseSolver::RankingStrategy FactorySolverOLD::getTheStrategy(ConfigurationJaks& configFile)
{
	int strategy = atoi(configFile["ranking_strategy"].c_str());
	return static_cast<ProduceAndChooseSolver::RankingStrategy> (strategy);
}