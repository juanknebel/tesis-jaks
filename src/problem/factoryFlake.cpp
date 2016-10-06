//
// Created by zero on 03/10/16.
//

#include "factoryFlake.h"

FactoryFlake::FactoryFlake() {

}

Flake FactoryFlake::createNewFlake(int id, ProblemInstance &theProblem) {
    std::set<int> cover = std::set<int>(*theProblem.getCover(id));
    return Flake(id, theProblem.getNode(id), theProblem.getCost(id), cover);
}

std::set<Flake> FactoryFlake::createAllFlakes(ProblemInstance &theProblem) {
    std::set<Flake> allFlakes = std::set<Flake>();
    for (auto id : theProblem.getIds()) {
        allFlakes.insert(FactoryFlake::createNewFlake(id, theProblem));
    }
    return allFlakes;
}
