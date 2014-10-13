#include "configurator.h"

Configurator::Configurator(Solver* solver, WriterSolution* writer, IdentificationGeneretor* identificator) {
}

WriterSolution* Configurator::getTheWrtiter() const {
    return this->theWriter_;
}

Solver* Configurator::getTheSolver() const {
    return this->theSolver_;
}

String Configurator::getSolverName() const {
    return this->solverName_;
}

Configurator::~Configurator() {
    delete this->theSolver_;
    delete this->theWriter_;
}
