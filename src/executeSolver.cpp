#include <cstdlib>
#include "util/Logger.h"
#include "util/id2Str.h"
#include "util/exception.h"
#include "util/identificationGeneretorArticle.h"
#include "util/identificationGeneretorAuthor.h"
#include "util/identificationGeneretorAffiliation.h"
#include "util/writerSolutionAffiliations.h"
#include "util/writerSolutionAuthors.h"
#include "util/writerSolutionArticles.h"
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

Id2Str* theNodeName;
std::string useDataFromDb;
std::string database;
std::string user;
std::string password;
std::string server;
std::string tableOfCosts;
std::string tableOfCompatibility;
std::string tableOfCover;
std::string tableOfMappingIds;
std::string fieldForCost;
std::string fieldForCompatibility;
std::string fieldForCover;
std::string fieldPrimary;
std::string fieldPrimaryDescription;
std::string fieldItem;
std::string fieldItemCompat1;
std::string fieldItemCompat2;
std::string directoryOfWork;
std::string fileOfCosts;
std::string fileOfCompatibility;
std::string fileOfCover;
std::string nodeName;
bool withSpecificItem;
int specificItem;
int solverId;
double budget;
int numberOfSnowFlakes;
double interSimilarityWeight;
double multiplier;
int toProduce;
double similarity;
int strategy;
bool printToScreen;
bool writeToFile;
WriterSolution *theWriter;

void settingGlobalVariables(ConfigurationJaks& configFile) {
	useDataFromDb = configFile["use_data_from_db"];
	
	database = configFile["db_database"];
	user = configFile["db_user"];
	password = configFile["db_password"];
	server = configFile["db_server"];
	
	tableOfCosts = configFile["table_costs"];
	tableOfCompatibility = configFile["table_compat"];
	tableOfCover = configFile["table_cover"];
	tableOfMappingIds = configFile["table_convertion_element_item"];
	
	fieldForCost = configFile["field_cost"];
	fieldForCompatibility = configFile["field_compat"];
	fieldForCover = configFile["field_cover"];
	fieldPrimary = configFile["field_primary"];
	fieldPrimaryDescription = configFile["field_primary_description"];
	fieldItem = configFile["field_item"];
	fieldItemCompat1 = configFile["field_item_compat1"];
	fieldItemCompat2 = configFile["field_item_compat2"];
	
	directoryOfWork = configFile["directory_work"];
	fileOfCosts = configFile["file_costs"];
	fileOfCompatibility = configFile["file_compat"];
	fileOfCover = configFile["file_cover"];
	nodeName = configFile["file_node_name"];
	
	withSpecificItem = ((configFile["with_specific_item"] == "1") ? true : false);
	specificItem = atoi(configFile["specific_item"].c_str());
	solverId = atoi(configFile["solver"].c_str());
	budget = atof(configFile["budget"].c_str());
	numberOfSnowFlakes = atoi(configFile["num_flakes"].c_str());
	interSimilarityWeight = atof(configFile["inter_similarity_weight"].c_str());
	multiplier = atof(configFile["to_produce"].c_str());
	toProduce = multiplier * numberOfSnowFlakes;
	similarity = atof(configFile["inter_similarity_weight"].c_str());
	strategy = atoi(configFile["ranking_strategy"].c_str());
	
	printToScreen = ((configFile["print_to_screen"] == "1") ? true : false);
	writeToFile = ((configFile["write_file"] == "1") ? true : false);
    theWriter = new WriterSolutionAuthors("\t");
    theWriter = new WriterSolutionArticles("\t");
}

ProblemInstance* instanceTheProblemForDB() {
	Dao *dao = new DaoMySql(database, user, password, server);
	dao->connect();
	std::cout<<dao->showConnection()<<std::endl;
	ProblemInstance *theProblem = new ProblemInstanceFromDataBase(dao, tableOfCosts, tableOfCompatibility, tableOfCover, tableOfMappingIds, fieldForCost, fieldForCompatibility, fieldForCover, fieldPrimary, fieldPrimaryDescription, fieldItem, fieldItemCompat1, fieldItemCompat2, budget);
    IdentificationGeneretor *theIdentificator = new IdentificationGeneretorArticle(dao, "\t");
    //IdentificationGeneretor *theIdentificator = new IdentificationGeneretorAuthor(dao, "\t");
    //IdentificationGeneretor *theIdentificator = new IdentificationGeneretorAffiliation(dao, "\t");
    theNodeName = new Id2Str(theIdentificator);
	return theProblem;
}

ProblemInstance* instanceTheProblemForFiles() {
	ProblemInstance* theProblem = new ProblemInstanceFromFiles(directoryOfWork+fileOfCosts, directoryOfWork+fileOfCompatibility, directoryOfWork+fileOfCover, budget);
	if (withSpecificItem) {
		theProblem->setSpecificItem(specificItem);
	}
	theNodeName = new Id2Str(directoryOfWork + nodeName);
	return theProblem;
}

ProblemInstance* instanceTheProblem() {
	ProblemInstance* theProblem = 0;
	if (useDataFromDb == "1") {
		theProblem = instanceTheProblemForDB();
	}
	else {
		theProblem = instanceTheProblemForFiles();
	}
	return theProblem;
}

void showSolution(SnowFlakeVector& solution) {
	if(printToScreen) {
        std::cout<<theWriter->showInScreen(solution, theNodeName)<<std::endl;
	}
}

void writeSolution(SnowFlakeVector& solution) {
	if(writeToFile) {
		std::stringstream fileName;
		fileName << directoryOfWork<<"Solver-";
		Double gamma = 1.00 - interSimilarityWeight;
		switch(solverId) {
			case ClusterAndPick:
				fileName<<"ClusterAndPick";
				break;
			case SeqScan:
				fileName<<"SeqScan";
				break;
			case RestrictedHAC:
				fileName<<"RestrictedHAC";
				break;
			case RestrictedHACSpecific:
				fileName<<"RestrictedHACSpecific";
				break;
			case RandomBOBO:
				fileName<<"RandomBOBO";
				break;
			case RandomSOBO:
				fileName<<"RandomSOBO";
				break;
			case ExAnySimSOBO:
				fileName<<"ExAnySimSOBO";
				break;
			case ExSumSimSOBO:
				fileName<<"ExSumSimSOBO";
				break;
		}
		fileName << "_ToProduce-"<<toProduce<<"_Gamma-"<<gamma<<".csv";
		std::cout<<"Writing the solution into the file: "<<fileName.str()<<std::endl;
        theWriter->writeSolution(solution, fileName.str(), theNodeName, interSimilarityWeight);
        theWriter->writeInterAndIntraValues(solution, fileName.str(), interSimilarityWeight);
	}
}

ProduceAndChooseSolver::RankingStrategy checkAndReturnStrategy() {
	if (similarity != 0.00 && strategy == 0) {
		throw Exception(__FILE__, __LINE__, "If INTER_SIMILARITY_WEIGHT similarity is used, the strategy should be #RANK_BY_INTRA_INTER o #RANK_BY_DENSEST_SUBGRAPH)");
	}
	return static_cast<ProduceAndChooseSolver::RankingStrategy> (strategy);
}

void execute(ConfigurationJaks& configFile) {
	settingGlobalVariables(configFile);
	ProblemInstance* theProblem = instanceTheProblem();
	ProduceAndChooseSolver::RankingStrategy strategy = checkAndReturnStrategy();
	Solver* theSolver = 0;
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
			if (strategy != ProduceAndChooseSolver::RANK_BY_INTRA) {
				dynamic_cast<RestrictedHACSolver *> (theSolver)->setRankingStrategy(strategy);
				dynamic_cast<RestrictedHACSolver *> (theSolver)->setInterSimilarityWeight(interSimilarityWeight);
				dynamic_cast<RestrictedHACSolver *> (theSolver)->setNumCandidatesMultiplier(multiplier);
			}
			break;
		case RestrictedHACSpecific:
			std::cout<<"Running RestrictedHACSpecificSolver ..."<<std::endl;
			theSolver = new RestrictedHACSWithSpecificItemSolver(theProblem);
			if (strategy != ProduceAndChooseSolver::RANK_BY_INTRA) {
				dynamic_cast<RestrictedHACSWithSpecificItemSolver *> (theSolver)->setRankingStrategy(strategy);
				dynamic_cast<RestrictedHACSWithSpecificItemSolver *> (theSolver)->setInterSimilarityWeight(interSimilarityWeight);
				dynamic_cast<RestrictedHACSWithSpecificItemSolver *> (theSolver)->setNumCandidatesMultiplier(multiplier);
			}
			break;
		case RandomBOBO:
			std::cout<<"Running RandomBOBOSolver ..."<<std::endl;
			theSolver = new RandomBOBOSolver(theProblem);
			if (strategy != ProduceAndChooseSolver::RANK_BY_INTRA) {
				dynamic_cast<RandomBOBOSolver *> (theSolver)->setRankingStrategy(strategy);
				dynamic_cast<RandomBOBOSolver *> (theSolver)->setInterSimilarityWeight(interSimilarityWeight);
				dynamic_cast<RandomBOBOSolver *> (theSolver)->setNumCandidatesMultiplier(multiplier);
			}
			break;
		case RandomSOBO:
			std::cout<<"Running RandomSOBOSolver ..."<<std::endl;
			theSolver = new RandomSOBOSolver(theProblem);
			if (strategy != ProduceAndChooseSolver::RANK_BY_INTRA) {
				dynamic_cast<RandomSOBOSolver *> (theSolver)->setRankingStrategy(strategy);
				dynamic_cast<RandomSOBOSolver *> (theSolver)->setInterSimilarityWeight(interSimilarityWeight);
				dynamic_cast<RandomSOBOSolver *> (theSolver)->setNumCandidatesMultiplier(multiplier);
			}
			break;
		case ExAnySimSOBO:
			std::cout<<"Running ExhaustiveGreedyAnySimSolver ..."<<std::endl;
			theSolver = new ExhaustiveGreedyAnySimSOBOSolver(theProblem);
			if (strategy != ProduceAndChooseSolver::RANK_BY_INTRA) {
				dynamic_cast<ExhaustiveGreedyAnySimSOBOSolver *> (theSolver)->setRankingStrategy(strategy);
				dynamic_cast<ExhaustiveGreedyAnySimSOBOSolver *> (theSolver)->setInterSimilarityWeight(interSimilarityWeight);
				dynamic_cast<ExhaustiveGreedyAnySimSOBOSolver *> (theSolver)->setNumCandidatesMultiplier(multiplier);
			}
			break;
		case ExSumSimSOBO:
			std::cout<<"Running ExhaustiveGreedySumSimSolver ..."<<std::endl;
			theSolver = new ExhaustiveGreedySumSimSOBOSolver(theProblem);
			if (strategy != ProduceAndChooseSolver::RANK_BY_INTRA) {
				dynamic_cast<ExhaustiveGreedySumSimSOBOSolver *> (theSolver)->setRankingStrategy(strategy);
				dynamic_cast<ExhaustiveGreedySumSimSOBOSolver *> (theSolver)->setInterSimilarityWeight(interSimilarityWeight);
				dynamic_cast<ExhaustiveGreedySumSimSOBOSolver *> (theSolver)->setNumCandidatesMultiplier(multiplier);
			}
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
		exit(0);
	}
	catch ( ... ) {
		std::cerr<<"Unexpected error"<<std::endl;
		exit(0);
	}
	showSolution(*solution);
	writeSolution(*solution);
	delete solution;
	delete theProblem;
	delete theSolver;
	delete theNodeName;
}
