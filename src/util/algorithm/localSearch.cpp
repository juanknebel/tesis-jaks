#include "localSearch.h"

LocalSearch::LocalSearch(std::shared_ptr<SnowFlakeVector> solution, std::shared_ptr<ProblemInstance> theProblem) {
    this->solution_ = solution;
    this->theProblem_ = theProblem;
}

SnowFlakeVector* LocalSearch::execute(int maxIter) {
    /*
     * Tomo un bundle:
     * tomo un elemento y lo intento cambiar por algun otro de los demas bundles
     * si mejora hago efectivo el cambio y paso al siguiente elemento
     * si no mejora intento con otro elemento
     * esto lo repito tantas veces como el parametro de maximas iteraciones
    */

    auto solution = this->solution_.get();
    int id = 1;
    std::for_each(solution->begin(), solution->end(), [id](SnowFlake item) mutable {
        item.setIdentificator(id);
        ++id;
    });

    maxIter = 10;
    int iter = 0;
    while (iter < maxIter) {
        /*for (auto item: solution) {

        }*/
        std::for_each(solution->cbegin(), solution->cend(),[](SnowFlake item) {

        });
        ++iter;
    }

    return this->solution_.get();
}
