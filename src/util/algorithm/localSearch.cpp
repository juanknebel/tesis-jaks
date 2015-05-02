//
// Created by zero on 19/04/15.
//

#include "localSearch.h"

LocalSearch::LocalSearch(SnowFlakeVector solution, std::shared_ptr<ProblemInstance> theProblem) {
    this->solution_ = solution;
    this->theProblem_ = theProblem;
}

/*
 * Tomo un bundle:
 * tomo un elemento y lo intento cambiar por algun otro de los demas bundles
 * si mejora hago efectivo el cambio y paso al siguiente elemento
 * si no mejora intento con otro elemento
 * esto lo repito tantas veces como el parametro de maximas iteraciones
*/
SnowFlakeVector LocalSearch::execute(int maxIter) {
    int id = 1;
    for (auto item : this->solution_) {
        item->setIdentificator(id);
        ++id;
    }

    maxIter = 10;
    int iter = 0;
    while (iter < maxIter) {
        for (auto item : this->solution_) {

        }
    }
    return std::vector<SnowFlake *>();
}
