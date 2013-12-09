#include <cstdlib>
#include "util/Logger.h"
#include "util/id2Str.h"
#include "util/exception.h"
#include "util/dbConnection.h"
#include "dao/daoMySql.h"
#include "executeSolver.h"
#include "problemInstanceFromFiles.h"
#include "problemInstanceFromDataBase.h"
#include "solver/clusterAndPickSolver.h"
#include "solver/restrictedHACSolver.h"
#include "solver/randomBOBOSolver.h"
#include "solver/randomSOBOSolver.h"
#include "solver/exhaustiveGreedyAnySimSOBOSolver.h"
#include "solver/exhaustiveGreedySumSimSOBOSolver.h"
#include "solver/sequentialScanSolver.h"
#include "solver/restrictedHACWithSpecificItemSolver.h"

#include <iostream>
using namespace std;

ProblemInstance* instanceTheProblemForDB(ConfigurationJaks& configFile) {
	Dao *dao = new DaoMySql(db_database, db_user, db_password, db_server);
	dao->connect();
	ProblemInstance *theProblem = new ProblemInstanceFromDataBase(dao, configFile["table_costs"], configFile["table_compat"], configFile["table_cover"], configFile["table_convertion_element_item"], configFile["field_cost"], configFile["field_compat"], configFile["field_cover"], configFile["field_primary"], configFile["field_primary_description"], configFile["field_item"], configFile["field_item_compat1"], configFile["field_item_compat2"], atof(configFile["budget"].c_str()));
	return theProblem;
}

ProblemInstance* instanceTheProblemForFiles(ConfigurationJaks& configFile) {
	std::string directory = configFile["directory_work"];
	ProblemInstance* theProblem = new ProblemInstanceFromFiles(directory+configFile["file_costs"], directory+configFile["file_compat"], directory+configFile["file_cover"], atof(configFile["budget"].c_str()));
	bool withSpecificItem = ((configFile["with_specific_item"] == "1") ? true : false);
	int specificItem = atoi(configFile["specific_item"].c_str());
	if (withSpecificItem) {
		theProblem->setSpecificItem(specificItem);
	}
	return theProblem;
}

ProblemInstance* instanceTheProblem(ConfigurationJaks& configFile) {
	ProblemInstance* theProblem = 0;
	if (configFile["use_data_from_db"] == "1") {
		theProblem = instanceTheProblemForDB(configFile);
	}
	else {
		theProblem = instanceTheProblemForFiles(configFile);
	}
	return theProblem;
}

Id2Str* instanceTheNodeName(ConfigurationJaks& configFile) {
	std::string directory = configFile["directory_work"];
	Id2Str* theNodeName = new Id2Str(configFile["directory_work"] + configFile["file_node_name"]);
	return theNodeName;
}

void showSolution(SnowFlakeVector& solution, ConfigurationJaks& configFile, const Id2Str* theNodeName) {
	if(atoi(configFile["print_to_screen"].c_str())) {
		cout<<SnowFlake::showSolution(solution,theNodeName)<<endl;
	}
}

void writeSolution(const SnowFlakeVector& solution, ConfigurationJaks& configFile) {
	if(atoi(configFile["write_file"].c_str())) {
		String outputFileName = configFile["directory_work"] + configFile["name_output"];
		std::cout<<"Writing the solution into the file: "<<outputFileName<<std::endl;
		SnowFlake::writeSolution(solution, outputFileName);
	}
}

ProduceAndChooseSolver::RankingStrategy checkAndReturnStrategy(ConfigurationJaks& configFile) {
	Double similarity = atof(configFile["inter_similarity_weight"].c_str());
	int strategy = atoi(configFile["ranking_strategy"].c_str());
	if (similarity == 1.00 && strategy == 0) {
		throw Exception(__FILE__, __LINE__, "If INTER_SIMILARITY_WEIGHT similarity is used, the strategy should be #RANK_BY_INTRA_INTER o #RANK_BY_DENSEST_SUBGRAPH)");
	}
	return static_cast<ProduceAndChooseSolver::RankingStrategy> (strategy);
}

void execute(ConfigurationJaks& configFile) {
	int solverId = atoi(configFile["solver"].c_str());
	ProblemInstance* theProblem = instanceTheProblem(configFile);
	Id2Str* theNodeName;
	//theNodeName = instanceTheNodeName(configFile);
	ProduceAndChooseSolver::RankingStrategy strategy = checkAndReturnStrategy(configFile);
	int numberOfSnowFlakes = atoi(configFile["num_flakes"].c_str());
	Solver* theSolver = 0;
	Double interSimilarityWeight = atof(configFile["inter_similarity_weight"].c_str());
	
	switch(solverId) {
		case ClusterAndPick:
			std::cout<<"Running ClusterAndPickSolver ..."<<std::endl;
			theSolver = new ClusterAndPickSolver(theProblem);
			break;
		case SeqScan:
			std::cout<<"Running SequentialScanSolver ..."<<std::endl;
			theSolver = new SequentialScanSolver(theProblem);
			break;
		case RestrictedHAC:
			std::cout<<"Running RestrictedHACSolver ..."<<std::endl;
			theSolver = new RestrictedHACSolver(theProblem);
			dynamic_cast<RestrictedHACSolver *> (theSolver)->setRankingStrategy(strategy);
			dynamic_cast<RestrictedHACSolver *> (theSolver)->setInterSimilarityWeight(interSimilarityWeight);
			break;
		case RestrictedHACSpecific:
			std::cout<<"Running RestrictedHACSpecificSolver ..."<<std::endl;
			theSolver = new RestrictedHACSWithSpecificItemSolver(theProblem);
			dynamic_cast<RestrictedHACSWithSpecificItemSolver *> (theSolver)->setRankingStrategy(strategy);
			dynamic_cast<RestrictedHACSWithSpecificItemSolver *> (theSolver)->setInterSimilarityWeight(interSimilarityWeight);
			break;
		case RandomBOBO:
			std::cout<<"Running RandomBOBOSolver ..."<<std::endl;
			theSolver = new RandomBOBOSolver(theProblem);
			dynamic_cast<RandomBOBOSolver *> (theSolver)->setRankingStrategy(strategy);
			dynamic_cast<RandomBOBOSolver *> (theSolver)->setInterSimilarityWeight(interSimilarityWeight);
			break;
		case RandomSOBO:
			std::cout<<"Running RandomSOBOSolver ..."<<std::endl;
			theSolver = new RandomSOBOSolver(theProblem);
			dynamic_cast<RandomSOBOSolver *> (theSolver)->setRankingStrategy(strategy);
			dynamic_cast<RandomSOBOSolver *> (theSolver)->setInterSimilarityWeight(interSimilarityWeight);
			break;
		case ExAnySimSOBO:
			std::cout<<"Running ExhaustiveGreedyAnySimSolver ..."<<std::endl;
			theSolver = new ExhaustiveGreedyAnySimSOBOSolver(theProblem);
			dynamic_cast<ExhaustiveGreedyAnySimSOBOSolver *> (theSolver)->setRankingStrategy(strategy);
			dynamic_cast<ExhaustiveGreedyAnySimSOBOSolver *> (theSolver)->setInterSimilarityWeight(interSimilarityWeight);
			break;
		case ExSumSimSOBO:
			std::cout<<"Running ExhaustiveGreedySumSimSolver ..."<<std::endl;
			theSolver = new ExhaustiveGreedySumSimSOBOSolver(theProblem);
			dynamic_cast<ExhaustiveGreedySumSimSOBOSolver *> (theSolver)->setRankingStrategy(strategy);
			dynamic_cast<ExhaustiveGreedySumSimSOBOSolver *> (theSolver)->setInterSimilarityWeight(interSimilarityWeight);
			break;
		default:
			std::cerr<<"The method chosen for the resolution does not exist"<<std::endl;
			exit(0);
			break;
	}
	SnowFlakeVector* solution = 0;
	try {
		solution = theSolver->solve(numberOfSnowFlakes);
	}
	catch (Exception& e) {
		std::cerr<<e.what()<<std::endl;
	}
	catch ( ... ) {
		std::cerr<<"Unexpected error"<<std::endl;
	}
	showSolution(*solution, configFile, theNodeName);
	writeSolution(*solution, configFile);
	delete solution;
	delete theProblem;
	delete theSolver;
}
