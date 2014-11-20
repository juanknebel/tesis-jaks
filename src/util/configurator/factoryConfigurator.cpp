#include "factoryConfigurator.h"

FactoryConfigurator::FactoryConfigurator(ConfigurationJaks& configFile) {
    std::string useDataFromDb = configFile["use_data_from_db"];

    std::string database = configFile["db_database"];
    std::string user = configFile["db_user"];
    std::string password = configFile["db_password"];
    std::string server = configFile["db_server"];

    std::string tableOfCosts = configFile["table_costs"];
    std::string tableOfCompatibility = configFile["table_compat"];
    std::string tableOfCover = configFile["table_cover"];
    std::string tableOfMappingIds = configFile["table_convertion_element_item"];

    std::string fieldForCost = configFile["field_cost"];
    std::string fieldForCompatibility = configFile["field_compat"];
    std::string fieldForCover = configFile["field_cover"];
    std::string fieldPrimary = configFile["field_primary"];
    std::string fieldPrimaryDescription = configFile["field_primary_description"];
    std::string fieldItem = configFile["field_item"];
    std::string fieldItemCompat1 = configFile["field_item_compat1"];
    std::string fieldItemCompat2 = configFile["field_item_compat2"];

    std::string directoryOfWork = configFile["directory_work"];
    std::string fileOfCosts = configFile["file_costs"];
    std::string fileOfCompatibility = configFile["file_compat"];
    std::string fileOfCover = configFile["file_cover"];
    std::string nodeName = configFile["file_node_name"];

    bool withSpecificItem = ((configFile["with_specific_item"] == "1") ? true : false);
    int specificItem = atoi(configFile["specific_item"].c_str());
    int solverId = atoi(configFile["solver"].c_str());
    double budget = atof(configFile["budget"].c_str());
    int numberOfSnowFlakes = atoi(configFile["num_flakes"].c_str());
    double interSimilarityWeight = atof(configFile["inter_similarity_weight"].c_str());
    double multiplier = atof(configFile["to_produce"].c_str());
    double similarity = atof(configFile["inter_similarity_weight"].c_str());
    int strategy = atoi(configFile["ranking_strategy"].c_str());

    bool printToScreen = ((configFile["print_to_screen"] == "1") ? true : false);
    bool writeToFile = ((configFile["write_file"] == "1") ? true : false);

    ProblemInstance* theProblem = 0;
    IdentificationGeneretor *theIdentificator = 0;
    Id2Str* theNodeName = 0;
    WriterSolution* theWriter = this->instanceTheWriter();

    this->instanceTheDao(database, user, password, server);

    if (useDataFromDb == "1") {
        theProblem = this->instanceTheProblemForDB(
                    tableOfCosts, tableOfCompatibility, tableOfCover,
                    tableOfMappingIds, fieldForCost, fieldForCompatibility, fieldForCover, fieldPrimary,
                    fieldPrimaryDescription, fieldItem, fieldItemCompat1, fieldItemCompat2, budget);
        theIdentificator = this->instanceTheIdentificator();
        theNodeName = new Id2Str(theIdentificator);
    }
    else {
        theProblem = this->instanceTheProblemForFiles(
                    directoryOfWork, fileOfCosts, fileOfCompatibility,
                    fileOfCover, budget, withSpecificItem, specificItem);
        theNodeName = new Id2Str(directoryOfWork + nodeName);
    }

    FactorySolver factorySolver;
    Solver *theSolver = factorySolver.getTheSolver(solverId, theProblem, strategy, similarity, multiplier);
    std::string theSolverName = factorySolver.getTheSolverName(solverId);
    ProduceAndChooseSolver::RankingStrategy theStrategy = factorySolver.getTheStrategy(strategy);

    this->theConfigurator_ = new Configurator(
                theSolver, theWriter, theIdentificator, theNodeName,
                theStrategy, theSolverName, numberOfSnowFlakes, printToScreen,
                writeToFile, directoryOfWork, 1.00 - interSimilarityWeight);
}

FactoryConfigurator::~FactoryConfigurator() {
}

ProblemInstance* FactoryConfigurator::instanceTheProblemForDB(
            std::string tableOfCosts, std::string tableOfCompatibility, std::string tableOfCover,
            std::string tableOfMappingIds, std::string fieldForCost, std::string fieldForCompatibility,
            std::string fieldForCover, std::string fieldPrimary, std::string fieldPrimaryDescription,
            std::string fieldItem, std::string fieldItemCompat1, std::string fieldItemCompat2, double budget) {

    ProblemInstance *theProblem = new ProblemInstanceFromDataBase(
                this->theDao_, tableOfCosts, tableOfCompatibility, tableOfCover, tableOfMappingIds,
                fieldForCost, fieldForCompatibility, fieldForCover, fieldPrimary,
                fieldPrimaryDescription, fieldItem, fieldItemCompat1, fieldItemCompat2, budget);
    return theProblem;
}

ProblemInstance* FactoryConfigurator::instanceTheProblemForFiles(
            std::string directoryOfWork, std::string fileOfCosts, std::string fileOfCompatibility,
            std::string fileOfCover, double budget, bool withSpecificItem, int specificItem) {

    ProblemInstance* theProblem = new ProblemInstanceFromFiles(
                directoryOfWork+fileOfCosts, directoryOfWork+fileOfCompatibility,
                directoryOfWork+fileOfCover, budget);

    if (withSpecificItem) {
        theProblem->setSpecificItem(specificItem);
    }
    return theProblem;
}

WriterSolution* FactoryConfigurator::instanceTheWriter() {
    //return new WriterSolutionAuthors("\t");
    return new WriterSolutionArticles("\t");
    //return new WriterSolutionAffiliations("\t");
}

IdentificationGeneretor* FactoryConfigurator::instanceTheIdentificator() {
    //return new IdentificationGeneretorAuthor(dao, "\t");
    return new IdentificationGeneretorArticle(this->theDao_, "\t");
    //return new IdentificationGeneretorAffiliation(dao, "\t");
}

void FactoryConfigurator::instanceTheDao(
        std::string database, std::string user, std::string password, std::string server) {
    this->theDao_ = new DaoMySql(database, user, password, server);
    theDao_->connect();
}

Configurator* FactoryConfigurator::getTheConfigurator() {
    return this->theConfigurator_;
}

Dao* FactoryConfigurator::getTheDao() {
    return this->theDao_;
}
