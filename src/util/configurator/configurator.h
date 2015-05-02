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
#include "../identificator/id2Str.h"
#include "../system/exception.h"
#include "../../problem/problemInstanceFromDataBase.h"
#include "../../problem/problemInstanceFromFiles.h"
#include <memory>


class Configurator {
protected:
    std::unique_ptr<ProblemInstance> theProblem_;
    std::unique_ptr<Selector> selectorStrategy_;
    std::unique_ptr<Solver> theSolver_;
    std::unique_ptr<WriterSolution> theWriter_;
    std::unique_ptr<Id2Str> theNodeName_;
    std::string solverName_;
    int numToProduce_;
    bool printToScreen_;
    bool writeToFile_;
    std::string directoryOfWork_;
    double gamma_;
public:
    Configurator(std::unique_ptr<ProblemInstance> theProblem,
                 std::unique_ptr<Selector> selectorStrategy,
                 std::unique_ptr<Solver> theSolver,
                 std::unique_ptr<WriterSolution> theWriter,
                 std::unique_ptr<Id2Str> theNodeName,
                 std::string solverName, int numToProduce,
                 bool printToScreen, bool writeToFile, std::string directoryOfWork, double gamma);

    virtual ~Configurator() {};
    ProblemInstance* getTheProblemInstance() const;
    Selector* getTheStrategy() const;
    Solver* getTheSolver() const;
    WriterSolution* getTheWriter() const;
    Id2Str* getTheNodeName() const;
    std::string getSolverName() const;
    int getNumToProduce() const;
    bool getPrintToScreen() const;
    bool getWriteToFile() const;
    std::string getDirectoryOfWork() const;
    double getGamma() const;
};

#endif // CONFIGURATOR_H
