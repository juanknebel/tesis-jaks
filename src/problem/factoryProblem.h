//
// Created by zero on 11/09/16.
//

#ifndef TESIS_JAKS_EXE_FACTORYPROBLEM_H
#define TESIS_JAKS_EXE_FACTORYPROBLEM_H
#include <memory>
#include "problemInstance.h"
#include "problemInstanceFromDataBase.h"
#include "problemInstanceFromFiles.h"

class FactoryProblem {
private:
    FactoryProblem();

public:
    static std::unique_ptr<ProblemInstance> getTheProblem(std::string element, double budget);

};


#endif //TESIS_JAKS_EXE_FACTORYPROBLEM_H
