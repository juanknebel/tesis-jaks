#include "configurator.h"

Configurator::Configurator(std::unique_ptr<ProblemInstance> theProblem,
                           std::unique_ptr<Selector> selectorStrategy,
                           std::unique_ptr<Solver> theSolver,
                           std::unique_ptr<WriterSolution> theWriter,
                           std::unique_ptr<Id2Str> theNodeName,
                           std::string solverName, int numToProduce,
                           bool printToScreen, bool writeToFile, std::string directoryOfWork, double gamma) {
    this->theProblem_ = std::move(theProblem);
    this->theSolver_ = std::move(theSolver);
    this->theWriter_ = std::move(theWriter);
    this->theNodeName_ = std::move(theNodeName);
    this->selectorStrategy_ = std::move(selectorStrategy);
    this->solverName_ = solverName;
    this->numToProduce_ = numToProduce;
    this->printToScreen_ = printToScreen;
    this->writeToFile_ = writeToFile;
    this->directoryOfWork_ = directoryOfWork;
    this->gamma_ = gamma;
}

WriterSolution* Configurator::getTheWriter() const {
    return this->theWriter_.get();
}

Solver* Configurator::getTheSolver() const {
    return this->theSolver_.get();
}

Id2Str* Configurator::getTheNodeName() const {
    return this->theNodeName_.get();
}

std::string Configurator::getSolverName() const {
    return this->solverName_;
}

int Configurator::getNumToProduce() const {
    return this->numToProduce_;
}

bool Configurator::getPrintToScreen() const {
    return this->printToScreen_;
}

bool Configurator::getWriteToFile() const {
    return this->writeToFile_;
}

std::string Configurator::getDirectoryOfWork() const {
    return this->directoryOfWork_;
}

double Configurator::getGamma() const {
    return this->gamma_;
}

Selector *Configurator::getTheStrategy() const {
    return this->selectorStrategy_.get();
}

ProblemInstance *Configurator::getTheProblemInstance() const {
    return theProblem_.get();
}
