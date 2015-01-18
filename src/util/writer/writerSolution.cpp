#include "writerSolution.h"
#include "../system/stringUtilities.h"

WriterSolution::WriterSolution(std::string separator) {
    this->separator_ = separator;
    this->endOfLIne_ = "\n";
}

std::string WriterSolution::showInScreen(std::vector<SnowFlake> &solution, const Id2Str *node2name) {
    std::string result = this->endOfLIne_;
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

void WriterSolution:: writeInterAndIntraValues(std::vector<SnowFlake> &solution, std::string fileName) {
    std::string separator = "\t";
    std::string endOfLIne = "\n";
    std::string fileNameIntra = fileName + "-nodes.csv";
    std::ofstream fileIntra(fileNameIntra.c_str());
    fileIntra << "id" << separator << "Label" << separator << "Intra" << endOfLIne;
    unsigned int id = 1;

    for (std::vector<SnowFlake>::iterator it = solution.begin(); it != solution.end(); ++it) {
        it->setIdentificator(id);
        id++;
        fileIntra << it->getIdentificator() << separator << "Bundle" << it->getIdentificator() << separator << it->getSumIntraCompat() << endOfLIne;
    }
    fileIntra.close();

    std::string fileNameInter = fileName + "-edges.csv";
    std::ofstream fileInter(fileNameInter.c_str());
    fileInter << "Source" << separator << "Target" << separator << "Type" << separator << "id" << separator << "Weight" << endOfLIne;
    id = 1;

     for (std::vector<SnowFlake>::iterator it = solution.begin(); it != solution.end(); ++it) {
         for (std::vector<SnowFlake>::iterator it2 = it; it2 != solution.end(); ++it2) {
             if (it->getIdentificator() == it2->getIdentificator()) {
                 continue;
             }
             fileInter << it->getIdentificator() << separator << it2->getIdentificator() << separator << "Undirected" << separator << id++ << separator << SnowFlake::maxPairwiseCompatibility(*it, *it2) << endOfLIne;
         }
     }
}

WriterSolution::~WriterSolution() {

}

void WriterSolution::writeSnowFlakeIds(std::vector<SnowFlake>& snowFlakeAll, std::string fileName) {
     std::ofstream file(fileName.c_str());
     unsigned int id = 1;
     for (std::vector<SnowFlake>::iterator it = snowFlakeAll.begin(); it != snowFlakeAll.end(); ++it) {

         std::set<int> idSet = it->ids();
         for (std::set<int>::iterator itSF = idSet.begin(); itSF != idSet.end(); ++itSF) {
             file << id << "," << (*itSF) << "\n";
         }
         ++id;
     }
     file.close();
}

