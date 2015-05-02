#include "factoryConfigurator.h"
#include "../../solver/selector/factorySelector.h"

FactoryConfigurator::FactoryConfigurator() {

}

std::unique_ptr<Configurator> FactoryConfigurator::getTheConfigurator(ConfigurationJaks& configFile) {
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
     * Instanciacion del helper
     */
    SnowFlakeHelper aSnowFlakeHelper;

    /*
     * Instanciacion del writter
     */
    std::unique_ptr<WriterSolution> theWriter = std::move(FactoryWriter::getTheWriter(configFile, aSnowFlakeHelper));

    Configurator* theConfigurator = nullptr;

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

        std::unique_ptr<Dao> daoConnection {theDao};

        /*
         * Instancio el problema
         */
        std::unique_ptr<ProblemInstance> theProblem = std::move(FactoryProblem::getTheProblemInstance(configFile, theDao));

        /*
         * Instanciacion la estrategia
         */
        std::unique_ptr<Selector> theStrategySelector = std::move(FactorySelector::getSelector(configFile, theProblem.get()));

        /*
         * Instanciacion del solver y el nombre
         */
        std::unique_ptr<Solver> theSolver = std::move(FactorySolver::getTheSolver(configFile, theProblem.get(), theStrategySelector.get()));
        std::string theSolverName = FactorySolver::getTheSolverName(configFile);

        /*
         * Instancio los identificadores de los elementos
         */
        std::unique_ptr<IdentificationGeneretor> theIdentificator =
        std::move(FactoryIdentificationGenerator::getTheIdentificator(theDao, configFile));
        std::unique_ptr<Id2Str> theNodeName {new Id2Str(theIdentificator.get())};

        /*
         * Instanciacion del configurador
         */
        theConfigurator = new ConfiguratorToDataBase(std::move(daoConnection), std::move(theProblem),
                                                     std::move(theStrategySelector), std::move(theSolver),
                                                     std::move(theWriter), std::move(theNodeName),
                                                     theSolverName, numberOfSnowFlakes, printToScreen,
                                                     writeToFile, directoryOfWork, 1.00 - interSimilarityWeight);
    }
    else {
        /*
         * Instancio el problema y los identificadores de los elementos
         */
        std::unique_ptr<ProblemInstance> theProblem = std::move(FactoryProblem::getTheProblemInstance(configFile));

        /*
         * Instanciacion la estrategia
         */
        std::unique_ptr<Selector> theStrategySelector = std::move(FactorySelector::getSelector(configFile, theProblem.get()));

        /*
         * Instanciacion del solver y el nombre
         */
        std::unique_ptr<Solver> theSolver = std::move(FactorySolver::getTheSolver(configFile, theProblem.get(), theStrategySelector.get()));
        std::string theSolverName = FactorySolver::getTheSolverName(configFile);

        /*
         * Instancio los identificadores de los elementos
         */
        std::string nodeName = configFile["file_node_name"];
        std::unique_ptr<Id2Str> theNodeName {new Id2Str(directoryOfWork + nodeName)};


        /*
         * Instanciacion del configurador
         */
        theConfigurator = new Configurator(std::move(theProblem), std::move(theStrategySelector),
                                           std::move(theSolver), std::move(theWriter),
                                           std::move(theNodeName), theSolverName, numberOfSnowFlakes,
                                           printToScreen, writeToFile, directoryOfWork,
                                           1.00 - interSimilarityWeight);
    }
    return std::unique_ptr<Configurator> {theConfigurator};
};
