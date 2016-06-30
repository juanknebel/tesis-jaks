#include "configurator.h"

Configurator::Configurator(
        Solver* solver, WriterSolution* writer, Id2Str* nodeName,
        ProduceAndChooseSolver::RankingStrategy strategy, std::string solverName, int numToProduce,
        bool printToScreen, bool writeToFile, std::string directoryOfWork, double gamma) {
    this->theSolver_ = solver;
    this->theWriter_ = writer;
    this->theNodeName_ = nodeName;
    this->theStrategy_ = strategy;
    this->solverName_ = solverName;
    this->numToProduce_ = numToProduce;
    this->printToScreen_ = printToScreen;
    this->writeToFile_ = writeToFile;
    this->directoryOfWork_ = directoryOfWork;
    this->gamma_ = gamma;
}

WriterSolution* Configurator::getTheWrtiter() const {
    return this->theWriter_;
}

Solver* Configurator::getTheSolver() const {
    return this->theSolver_;
}

Id2Str* Configurator::getTheNodeName() const {
    return this->theNodeName_;
}

ProduceAndChooseSolver::RankingStrategy Configurator::getTheStrategy() const {
    return this->theStrategy_;
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

string Configurator::getTheStrategyName() const {
    switch(this->theStrategy_) {
      case (RANK_BY_INTRA):
	  return "ByIntra";
	  break;
      case (RANK_BY_INTRA_INTER):
	  return "ByIntraInter";
	  break;
      case (RANK_BY_DENSEST_SUBGRAPH):
	  return "BySubgraph";
	  break;
      case (RANK_BY_INTRA_INTER_TUPLE):
	  return "ByIntraInterTuple";
	  break;
      case (RANK_BY_INTRA_INTER_PROPORTIONAL):
	  return "ByIntraInterProportional";
	  break;
    }
}

