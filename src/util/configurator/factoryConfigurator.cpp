#include "factoryConfigurator.h"
#include "../../solver/selector/factorySelector.h"

FactoryConfigurator::FactoryConfigurator() {

}

Configurator* FactoryConfigurator::getTheConfigurator(ConfigurationJaks& configFile) {
    /*
     * Dato que indica si los datos seran obtenidos desde una base de datos o desde un archivo
     */
    bool useDataFromDb = configFile["use_data_from_db"] == "1";
    /*
     * Datos comunes a cualquier configurador
     */
    int numberOfSnowFlakes = atoi(configFile["num_flakes"].c_str());
    double interSimilarityWeight = atof(configFile["inter_similarity_weight"].c_str());
    bool printToScreen = configFile["print_to_screen"] == "1";
    bool writeToFile = configFile["write_file"] == "1";
    std::string directoryOfWork = configFile["directory_work"];

    /*
     * Instanciacion del writter
     */
    WriterSolution* theWriter = FactoryWriter::getTheWriter(configFile);

    Configurator* theConfigurator = 0;

    if (useDataFromDb) {
        /*
         * Instanciacion del dao
         */
        std::string database = configFile["db_database"];
        std::string user = configFile["db_user"];
        std::string password = configFile["db_password"];
        std::string server = configFile["db_server"];

        Dao* theDao = new DaoMySql(database, user, password, server);
        theDao->connect();

        /*
         * Instancio el problema y los identificadores de los elementos
         */
        ProblemInstance* theProblem = FactoryProblem::getTheProblemInstance(configFile, theDao);
        IdentificationGeneretor *theIdentificator =
                FactoryIdentificationGenerator::getTheIdentificator(theDao, configFile);
        Id2Str* theNodeName = new Id2Str(theIdentificator);

        /*
         * Instanciacion del solver y la estrategia
         */
        std::string theSolverName = FactorySolver::getTheSolverName(configFile);
        Selector *theStrategySelector = FactorySelector::getSelector(configFile, theProblem);
        Solver *theSolver = FactorySolver::getTheSolver(configFile, theProblem, theStrategySelector);

        /*
         * Instanciacion del configurador
         */
        theConfigurator = new ConfiguratorToDataBase(theDao, theSolver, theWriter, theNodeName,
                                                    theStrategySelector, theSolverName, numberOfSnowFlakes, printToScreen,
                                                    writeToFile, directoryOfWork, 1.00 - interSimilarityWeight);
    }
    else {
        /*
         * Instancio el problema y los identificadores de los elementos
         */
        ProblemInstance* theProblem = FactoryProblem::getTheProblemInstance(configFile);
        std::string nodeName = configFile["file_node_name"];
        Id2Str* theNodeName = new Id2Str(directoryOfWork + nodeName);

        /*
         * Instanciacion del solver y la estrategia
         */
        std::string theSolverName = FactorySolver::getTheSolverName(configFile);
        Selector *theStrategySelector = FactorySelector::getSelector(configFile, theProblem);
        Solver *theSolver = FactorySolver::getTheSolver(configFile, theProblem, theStrategySelector);

        theConfigurator = new Configurator(theSolver, theWriter, theNodeName,
                        theStrategySelector, theSolverName, numberOfSnowFlakes, printToScreen,
                        writeToFile, directoryOfWork, 1.00 - interSimilarityWeight);
    }
    return theConfigurator;
}
