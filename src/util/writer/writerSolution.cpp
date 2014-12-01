#include "writerSolution.h"
#include "../system/stringUtilities.h"

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

void WriterSolution:: writeInterAndIntraValues(std::vector<SnowFlake> &solution, String fileName) {
    String separator = "\t";
    String endOfLIne = "\n";
    String fileNameIntra = fileName + "-nodes.csv";
    FileOutput fileIntra(fileNameIntra.c_str());
    fileIntra << "id" << separator << "Label" << separator << "Intra" << endOfLIne;
    Uint id = 1;

    for (std::vector<SnowFlake>::iterator it = solution.begin(); it != solution.end(); ++it) {
        it->setIdentificator(id);
        id++;
        fileIntra << it->getIdentificator() << separator << "Bundle" << it->getIdentificator() << separator << it->getSumIntraCompat() << endOfLIne;
    }
    fileIntra.close();

    String fileNameInter = fileName + "-edges.csv";
    FileOutput fileInter(fileNameInter.c_str());
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

void WriterSolution::writeSnowFlakeIds(std::vector<SnowFlake>& snowFlakeAll, String fileName) {
     FileOutput file(fileName.c_str());
     Uint id = 1;
     for (std::vector<SnowFlake>::iterator it = snowFlakeAll.begin(); it != snowFlakeAll.end(); ++it) {

         IntSet idSet = it->ids();
         for (IntSet::iterator itSF = idSet.begin(); itSF != idSet.end(); ++itSF) {
             file << id << "," << (*itSF) << "\n";
         }
         ++id;
     }
     file.close();
}

