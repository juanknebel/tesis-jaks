#ifndef CONFIGURATORTODATABASE_H
#define CONFIGURATORTODATABASE_H

#include "configurator.h"

class ConfiguratorToDataBase : public Configurator {
private:
    Dao* theDao_;
public:
    ConfiguratorToDataBase(Dao* dao, Solver* solver, WriterSolution* writer,
                           Id2Str* nodeName, ProduceAndChooseSolver::RankingStrategy strategy, std::string solverName,
                           int numToProduce, bool printToScreen, bool writeToFile, std::string directoryOfWork,
                           double gamma) :
        Configurator(solver, writer, nodeName, strategy, solverName, numToProduce, printToScreen,
                     writeToFile, directoryOfWork, gamma) {
        this->theDao_ = dao;
    }
    Dao* getDao();
    ~ConfiguratorToDataBase();
};

#endif // CONFIGURATORTODATABASE_H
