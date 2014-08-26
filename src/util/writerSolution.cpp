#include "writerSolution.h"
#include "stringUtilities.h"

WriterSolution::WriterSolution() {
}

String WriterSolution::showInScreen(std::vector<SnowFlake> &solution, const Id2Str *node2name) {
    String result = "\n";
    int avgCost = 0;
    int avgCover = 0;
    int avgSize = 0;
    int avgSumIntraCompat = 0;
    int solutionsSize = solution.size();
    for (std::vector<SnowFlake>::iterator it = solution.begin(); it != solution.end(); ++it) {
        avgCost += it->getCost();
        avgCover += it->getCoverSize();
        avgSize += it->ids().size();
        avgSumIntraCompat += it->getSumIntraCompat();
        result.append(it->toString(node2name));
    }
    result.append("-------------------------------------------------\n");
    result.append("SOLUTION_SIZE = " + convertToString(solutionsSize) + "\n");
    result.append("AVG_COST = " + convertToString(avgCost / (double) solutionsSize) + "\n");
    result.append("AVG_COVER = " + convertToString(avgCover / (double) solutionsSize) + "\n");
    result.append("AVG_SIZE = " + convertToString(avgSize / (double) solutionsSize) + "\n");
    result.append("AVG_SUM_INTRA_COMPAT = " + convertToString(avgSumIntraCompat / (double) solutionsSize) + "\n");

    return result;
}

void WriterSolution:: writeInterAndIntraValues(const std::vector<SnowFlake> &solution, String fileName, Double interSimilarityWeight) {

}

WriterSolution::~WriterSolution() {

}


