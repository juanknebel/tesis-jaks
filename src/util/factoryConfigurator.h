#ifndef FACTORYSOLVER_H
#define FACTORYSOLVER_H

#include "configurationJaks.h"
#include "configurator/configurator.h"

class FactoryConfigurator {
private:
    ProblemInstance* instanceTheProblemForDB(
            std::string tableOfCosts, std::string tableOfCompatibility, std::string tableOfCover,
            std::string tableOfMappingIds, std::string fieldForCost, std::string fieldForCompatibility,
            std::string fieldForCover, std::string fieldPrimary, std::string fieldPrimaryDescription,
            std::string fieldItem, std::string fieldItemCompat1, std::string fieldItemCompat2, double budget);

    ProblemInstance* instanceTheProblemForFiles(
            std::string directoryOfWork, std::string fileOfCosts, std::string fileOfCompatibility,
            std::string fileOfCover, double budget, bool withSpecificItem, int specificItem);

    WriterSolution* instanceTheWriter();

    IdentificationGeneretor* instanceTheIdentificator();

    ProduceAndChooseSolver::RankingStrategy checkAndReturnStrategy(double similarity, int strategy);

    Solver* instanceTheSolver(
            int solverId, ProblemInstance* theProblem, ProduceAndChooseSolver::RankingStrategy strategy,
            double interSimilarityWeight, double multiplier);

    std::string instanceTheSolverName(int solverId);
    void instanceTheDao(std::string database, std::string user, std::string password, std::string server);

    Configurator* theConfigurator_;
    Dao* theDao_;
public:
    enum SolverAlgorithm {
        ClusterAndPick, RestrictedHAC, RestrictedHACSpecific, RandomBOBO,
        RandomSOBO, ExAnySimSOBO, ExSumSimSOBO, SeqScan
    };

    FactoryConfigurator(ConfigurationJaks& configFile);
    ~FactoryConfigurator();

    Configurator* getTheConfigurator();
    Dao* getTheDao();
};

#endif // FACTORYSOLVER_H
