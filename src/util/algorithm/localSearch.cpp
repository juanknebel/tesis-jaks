#include "localSearch.h"

SnowFlakeVector LocalSearch::execute(int maxIter, SnowFlakeVector& solution, ProblemInstance& theProblem) {
    SnowFlakeVector finalSolution;
    /*
     * Tomo un bundle:
     * tomo un elemento y lo intento cambiar por algun otro de los demas bundles
     * si mejora hago efectivo el cambio y paso al siguiente elemento
     * si no mejora intento con otro elemento
     * esto lo repito tantas veces como el parametro de maximas iteraciones
    */

    int id = 1;
    for (auto snowFlake : solution) {
        snowFlake->setIdentificator(id);
        ++id;
    }

    std::set<int> usedIds;
    for (auto snowFlake : solution) {
        for (auto elem : snowFlake->ids()) {
            usedIds.insert(elem);
        }
    }

    maxIter = 10;
    int iter = 0;
    while (iter < maxIter) {
         for (auto snowFlake : solution) {
            for (auto elem : snowFlake->ids()) {

            }
         }
        ++iter;
    }

    return finalSolution;
}
