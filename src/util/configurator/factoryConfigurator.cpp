#include "factoryConfigurator.h"

FactoryConfigurator::FactoryConfigurator(ConfigurationJaks& configFile) {
    IdentificationGeneretor *theIdentificator = 0;
    Id2Str* theNodeName = 0;

    /*
     *  Instanciacion del writter
     */
    //WriterSolution* theWriter = new WriterSolutionAuthors("\t");
    WriterSolution* theWriter = new WriterSolutionArticles("\t");
    //WriterSolution* theWriter = new WriterSolutionAffiliations("\t");

    /*
     *  Instanciacion del problema
     */
    bool useDataFromDb = ((configFile["use_data_from_db"] == "1") ? true : false);
    std::string directoryOfWork = configFile["directory_work"];
    ProblemInstance* theProblem = 0;

    if (useDataFromDb == true) {
        /*
         *  Instanciacion del dao
         */
        std::string database = configFile["db_database"];
        std::string user = configFile["db_user"];
        std::string password = configFile["db_password"];
        std::string server = configFile["db_server"];

        Dao* theDao = new DaoMySql(database, user, password, server);
        theDao->connect();
        theProblem = FactoryProblem::getTheProblemInstance(configFile, theDao);
        //theIdentificator =  new IdentificationGeneretorAuthor(dao, "\t");
        theIdentificator =  new IdentificationGeneretorArticle(theDao, "\t");
        //theIdentificator =  new IdentificationGeneretorAffiliation(dao, "\t");
        theNodeName = new Id2Str(theIdentificator);
    }
    else {
        theProblem = FactoryProblem::getTheProblemInstance(configFile);
        std::string nodeName = configFile["file_node_name"];
        theNodeName = new Id2Str(directoryOfWork + nodeName);
    }

    /*
     *  Instanciacion del solver
     */
    Solver *theSolver = FactorySolver::getTheSolver(configFile, theProblem);
    std::string theSolverName = FactorySolver::getTheSolverName(configFile);
    ProduceAndChooseSolver::RankingStrategy theStrategy = FactorySolver::getTheStrategy(configFile);

    /*
     *  Instanciacion del configurador
     */
    int numberOfSnowFlakes = atoi(configFile["num_flakes"].c_str());
    double interSimilarityWeight = atof(configFile["inter_similarity_weight"].c_str());
    bool printToScreen = ((configFile["print_to_screen"] == "1") ? true : false);
    bool writeToFile = ((configFile["write_file"] == "1") ? true : false);
    this->theConfigurator_ = new Configurator(
                theSolver, theWriter, theNodeName,
                theStrategy, theSolverName, numberOfSnowFlakes, printToScreen,
                writeToFile, directoryOfWork, 1.00 - interSimilarityWeight);
}

FactoryConfigurator::~FactoryConfigurator() {
}

Configurator* FactoryConfigurator::getTheConfigurator() {
    return this->theConfigurator_;
}
