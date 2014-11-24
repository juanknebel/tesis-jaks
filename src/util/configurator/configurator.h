#ifndef CONFIGURATOR_H
#define CONFIGURATOR_H

#include "../identificator/identificationGeneretorArticle.h"
#include "../identificator/identificationGeneretorAuthor.h"
#include "../identificator/identificationGeneretorAffiliation.h"
#include "../writer/writerSolutionAffiliations.h"
#include "../writer/writerSolutionAuthors.h"
#include "../writer/writerSolutionArticles.h"
#include "../../solver/solver.h"
#include "../../solver/produceAndChooseSolver.h"
#include "../system/Logger.h"
#include "../identificator/id2Str.h"
#include "../system/exception.h"
#include "../../problem/problemInstanceFromDataBase.h"
#include "../../problem/problemInstanceFromFiles.h"


class Configurator {
protected:
    WriterSolution *theWriter_;
    Solver* theSolver_;
    Id2Str* theNodeName_;
    ProduceAndChooseSolver::RankingStrategy theStrategy_;
    std::string solverName_;
    int numToProduce_;
    bool printToScreen_;
    bool writeToFile_;
    std::string directoryOfWork_;
    double gamma_;
public:
    Configurator(Solver* solver, WriterSolution* writer, Id2Str* nodeName,
                 ProduceAndChooseSolver::RankingStrategy strategy, std::string solverName, int numToProduce,
                 bool printToScreen, bool writeToFile, std::string directoryOfWork, double gamma);

    virtual ~Configurator();
    WriterSolution* getTheWrtiter() const;
    Solver* getTheSolver() const;
    Id2Str* getTheNodeName() const;
    ProduceAndChooseSolver::RankingStrategy getTheStrategy() const;
    std::string getSolverName() const;
    int getNumToProduce() const;
    bool getPrintToScreen() const;
    bool getWriteToFile() const;
    std::string getDirectoryOfWork() const;
    double getGamma() const;
};

#endif // CONFIGURATOR_H
