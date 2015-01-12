#ifndef FACTORYSELECTOR_H
#define FACTORYSELECTOR_H

#include "../../util/configurator/configurationJaks.h"
#include "intraSelector.h"
#include "interIntraSelector.h"
#include "interIntraTuplesSelector.h"
#include "intraInterProportionalSelector.h"
#include "densestSubGraphSelector.h"

class FactorySelector {
private:
    enum RankingStrategy {
        /**
        * Sort in decreasing order by intra similarity, then pick the top elements.
        */
        RANK_BY_INTRA = 0,
        /**
        * Apply a greedy heuristic to add the element that increases the most ( gamma * intra + ( 1
        * - gamma ) * inter )
        */
        RANK_BY_INTRA_INTER,
        /**
        * Apply a densest-subgraph heuristic.
        */
        RANK_BY_DENSEST_SUBGRAPH,
        /**
        * Hace lo mismo que el INTRA_INTER pero genera tuplas para la seleccion
        */
        RANK_BY_INTRA_INTER_TUPLE,
        /**
         * Aplica una seleccion similiar al RANK_BY_INTRA_INTER pero compensa la primer parte
         */
        RANK_BY_INTRA_INTER_PROPORTIONAL
    };
    FactorySelector();
public :
    static Selector* getSelector(ConfigurationJaks& configFile, ProblemInstance* theProblem);
};

#endif // FACTORYSELECTOR_H
