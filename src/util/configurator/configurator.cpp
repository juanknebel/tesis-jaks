#include "configurator.h"

Configurator::Configurator(
        Solver* solver, WriterSolution* writer, Id2Str* nodeName,
        Selector* strategy, std::string solverName, int numToProduce,
        bool printToScreen, bool writeToFile, std::string directoryOfWork, double gamma) {
    this->theSolver_ = solver;
    this->theWriter_ = writer;
    this->theNodeName_ = nodeName;
    this->selectorStrategy_ = strategy;
    this->solverName_ = solverName;
    this->numToProduce_ = numToProduce;
    this->printToScreen_ = printToScreen;
    this->writeToFile_ = writeToFile;
    this->directoryOfWork_ = directoryOfWork;
    this->gamma_ = gamma;
}

WriterSolution* Configurator::getTheWriter() const {
    return this->theWriter_;
}

Solver* Configurator::getTheSolver() const {
    return this->theSolver_;
}

Id2Str* Configurator::getTheNodeName() const {
    return this->theNodeName_;
}

String Configurator::getSolverName() const {
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

Configurator::~Configurator() {
    delete this->theSolver_;
    delete this->theWriter_;
    delete this->theNodeName_;
}

Selector *Configurator::getTheStrategy() const {
    return this->selectorStrategy_;
}
