#ifndef CONFIGURATORTODATABASE_H
#define CONFIGURATORTODATABASE_H

#include "configurator.h"

class ConfiguratorToDataBase : public Configurator {
private:
    std::unique_ptr<Dao> theDao_;
public:
    ConfiguratorToDataBase(std::unique_ptr<Dao> dao, std::unique_ptr<ProblemInstance> theProblem,
                           std::unique_ptr<Selector> selectorStrategy,
                           std::unique_ptr<Solver> theSolver,
                           std::unique_ptr<WriterSolution> theWriter,
                           std::unique_ptr<Id2Str> theNodeName,
                           std::string solverName, int numToProduce,
                           bool printToScreen, bool writeToFile, std::string directoryOfWork, double gamma) :
        Configurator(std::move(theProblem), std::move(selectorStrategy), std::move(theSolver),
                     std::move(theWriter), std::move(theNodeName), solverName,
                     numToProduce, printToScreen, writeToFile, directoryOfWork, gamma) {
        this->theDao_ = std::move(dao);
    }
    Dao* getDao();
    ~ConfiguratorToDataBase() {}
};

#endif // CONFIGURATORTODATABASE_H
