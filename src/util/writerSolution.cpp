#include "writerSolution.h"
#include "stringUtilities.h"

WriterSolution::WriterSolution(String separator) {
    this->separator_ = separator;
    this->endOfLIne_ = "\n";
}

String WriterSolution::showInScreen(std::vector<SnowFlake> &solution, const Id2Str *node2name) {
    String result = this->endOfLIne_;
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
    result.append("-------------------------------------------------" + this->endOfLIne_);
    result.append("SOLUTION_SIZE = " + convertToString(solutionsSize) + "\n");
    result.append("AVG_COST = " + convertToString(avgCost / (double) solutionsSize) + this->endOfLIne_);
    result.append("AVG_COVER = " + convertToString(avgCover / (double) solutionsSize) + this->endOfLIne_);
    result.append("AVG_SIZE = " + convertToString(avgSize / (double) solutionsSize) + this->endOfLIne_);
    result.append("AVG_SUM_INTRA_COMPAT = " + convertToString(avgSumIntraCompat / (double) solutionsSize) + this->endOfLIne_);

    return result;
}

void WriterSolution:: writeInterAndIntraValues(std::vector<SnowFlake> &solution, String fileName, Double interSimilarityWeight) {
    String fileNameIntra = fileName + "-nodes.csv";
    FileOutput fileIntra(fileNameIntra.c_str());
    fileIntra << "id" << this->separator_ << "Label" << this->separator_ << "Intra" << this->endOfLIne_;
    Uint id = 1;

    for (std::vector<SnowFlake>::iterator it = solution.begin(); it != solution.end(); ++it) {
        it->setIdentificator(id);
        id++;
        fileIntra << it->getIdentificator() << this->separator_ << "Bundle" << it->getIdentificator() << this->separator_ << it->getSumIntraCompat() << this->endOfLIne_;
    }
    fileIntra.close();

    String fileNameInter = fileName + "-edges.csv";
    FileOutput fileInter(fileNameInter.c_str());
    fileInter << "Source" << this->separator_ << "Target" << this->separator_ << "Type" << this->separator_ << "id" << this->separator_ << "Weight" << this->endOfLIne_;
    id = 1;

     for (std::vector<SnowFlake>::iterator it = solution.begin(); it != solution.end(); ++it) {
         for (std::vector<SnowFlake>::iterator it2 = it; it2 != solution.end(); ++it2) {
             if (it->getIdentificator() == it2->getIdentificator()) {
                 continue;
             }
             fileInter << it->getIdentificator() << this->separator_ << it2->getIdentificator() << this->separator_ << "Undirected" << this->separator_ << id++ << this->separator_ << SnowFlake::maxPairwiseCompatibility(*it, *it2) << this->endOfLIne_;
         }
     }
}

WriterSolution::~WriterSolution() {

}


