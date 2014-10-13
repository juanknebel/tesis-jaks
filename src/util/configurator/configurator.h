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
#include "../system/Logger.h"
#include "../identificator/id2Str.h"
#include "../system/exception.h"
#include "../identificator/identificationGeneretorArticle.h"
#include "../identificator/identificationGeneretorAuthor.h"
#include "../identificator/identificationGeneretorAffiliation.h"
#include "../writer/writerSolutionAffiliations.h"
#include "../writer/writerSolutionAuthors.h"
#include "../writer/writerSolutionArticles.h"

class Configurator {
private:
    WriterSolution *theWriter_;
    Solver* theSolver_;
    String solverName_;
public:
    Configurator(Solver* solver, WriterSolution* writer, IdentificationGeneretor* identificator);

    ~Configurator();
    WriterSolution* getTheWrtiter() const;
    Solver* getTheSolver() const;
    String getSolverName() const;
};

#endif // CONFIGURATOR_H
