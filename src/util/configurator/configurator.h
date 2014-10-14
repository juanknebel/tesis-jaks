#ifndef CONFIGURATOR_H
#define CONFIGURATOR_H

#include "../../solver/clusterAndPickSolver.h"
#include "../../solver/restrictedHACSolver.h"
#include "../../solver/randomSOBOSolver.h"
#include "../../solver/randomBOBOSolver.h"
#include "../../solver/exhaustiveGreedyAnySimSOBOSolver.h"
#include "../../solver/exhaustiveGreedySumSimSOBOSolver.h"
#include "../../solver/sequentialScanSolver.h"
#include "../../solver/restrictedHACWithSpecificItemSolver.h"
#include "../identificator/identificationGeneretorArticle.h"
#include "../identificator/identificationGeneretorAuthor.h"
#include "../identificator/identificationGeneretorAffiliation.h"
#include "../writer/writerSolutionAffiliations.h"
#include "../writer/writerSolutionAuthors.h"
#include "../writer/writerSolutionArticles.h"
#include "../system/Logger.h"
#include "../identificator/id2Str.h"
#include "../system/exception.h"
#include "../../problem/problemInstanceFromDataBase.h"
#include "../../problem/problemInstanceFromFiles.h"


class Configurator {
private:
    WriterSolution *theWriter_;
    Solver* theSolver_;
    IdentificationGeneretor* theIdentificator_;
    Id2Str* theNodeName_;
    ProduceAndChooseSolver::RankingStrategy theStrategy_;
    std::string solverName_;
    int numToProduce_;
    bool printToScreen_;
    bool writeToFile_;
    std::string directoryOfWork_;
    double gamma_;
public:
    Configurator(Solver* solver, WriterSolution* writer, IdentificationGeneretor* identificator, Id2Str* nodeName,
                 ProduceAndChooseSolver::RankingStrategy strategy, std::string solverName, int numToProduce,
                 bool printToScreen, bool writeToFile, std::string directoryOfWork, double gamma);

    ~Configurator();
    WriterSolution* getTheWrtiter() const;
    Solver* getTheSolver() const;
    IdentificationGeneretor* getTheIdentificator() const;
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
