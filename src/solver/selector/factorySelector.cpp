#include "factorySelector.h"

FactorySelector::FactorySelector() {
}

std::unique_ptr<Selector> FactorySelector::getSelector(ConfigurationJaks& configFile, ProblemInstance* theProblem) {
    int strategyId = atoi(configFile["ranking_strategy"].c_str());
    double interSimilarityWeight = atof(configFile["inter_similarity_weight"].c_str());
    Selector* selector = 0;
    switch(strategyId) {
        case(RANK_BY_INTRA):
            selector = new IntraSelector(interSimilarityWeight, theProblem);
            break;
        case(RANK_BY_INTRA_INTER):
            selector = new InterIntraSelector(interSimilarityWeight, theProblem);
            break;
        case(RANK_BY_DENSEST_SUBGRAPH):
            selector = new DensestSubgraphSelector(interSimilarityWeight, theProblem);
            break;
        case(RANK_BY_INTRA_INTER_TUPLE):
            selector = new InterIntraTuplesSelector(interSimilarityWeight, theProblem);
            break;
        case(RANK_BY_INTRA_INTER_PROPORTIONAL):
            selector = new IntraInterProportionalSelector(interSimilarityWeight, theProblem);
            break;
    }
    return std::unique_ptr<Selector> {selector};
}
