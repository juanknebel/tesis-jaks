//
// Created by zero on 03/10/16.
//

#ifndef TESIS_JAKS_EXE_FACTORYFLAKE_H
#define TESIS_JAKS_EXE_FACTORYFLAKE_H


#include "flake.h"

class FactoryFlake {
private:
    FactoryFlake();

public:
    static Flake createNewFlake(int id, ProblemInstance& theProblem);
    static std::set<Flake> createAllFlakes(ProblemInstance& theProblem);
};


#endif //TESIS_JAKS_EXE_FACTORYFLAKE_H
