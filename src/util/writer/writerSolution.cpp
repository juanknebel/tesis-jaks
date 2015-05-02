#include "writerSolution.h"
#include "../system/stringUtilities.h"

WriterSolution::WriterSolution(std::string separator, SnowFlakeHelper aSnowFlakeHelper) {
    this->separator_ = separator;
    this->endOfLIne_ = "\n";
    this->snowFlakeHelper = aSnowFlakeHelper;
}

std::string WriterSolution::showInScreen(std::vector<SnowFlake> &solution, const Id2Str *node2name, ProblemInstance &problem) {
    std::string result = this->endOfLIne_;
    int avgCost = 0;
    int avgCover = 0;
    int avgSize = 0;
    int avgSumIntraCompat = 0;
    int solutionsSize = solution.size();
    for (auto elem : solution) {
        avgCost += this->snowFlakeHelper.getCost(elem, problem);
        avgCover += this->snowFlakeHelper.getCoverSize(elem, problem);
        avgSize += elem.ids().size();
        avgSumIntraCompat += this->snowFlakeHelper.getSumIntraCompat(elem, problem);
        result.append(this->snowFlakeHelper.toString(elem, problem, node2name));
    }
    result.append("-------------------------------------------------" + this->endOfLIne_);
    result.append("SOLUTION_SIZE = " + convertToString(solutionsSize) + "\n");
    result.append("AVG_COST = " + convertToString(avgCost / (double) solutionsSize) + this->endOfLIne_);
    result.append("AVG_COVER = " + convertToString(avgCover / (double) solutionsSize) + this->endOfLIne_);
    result.append("AVG_SIZE = " + convertToString(avgSize / (double) solutionsSize) + this->endOfLIne_);
    result.append("AVG_SUM_INTRA_COMPAT = " + convertToString(avgSumIntraCompat / (double) solutionsSize) + this->endOfLIne_);

    return result;
}

void WriterSolution::writeInterAndIntraValues(std::vector<SnowFlake> &solution, std::string fileName,
                                                    ProblemInstance &problem) {
    std::string separator = "\t";
    std::string endOfLIne = "\n";
    std::string fileNameIntra = fileName + "-nodes.csv";
    std::ofstream fileIntra(fileNameIntra.c_str());
    fileIntra << "id" << separator << "Label" << separator << "Intra" << endOfLIne;
    unsigned int id = 1;

    for (auto elem : solution) {
        elem.setIdentificator(id);
        id++;
        fileIntra << elem.getIdentificator() << separator << "Bundle" << elem.getIdentificator() << separator << this->snowFlakeHelper.getSumIntraCompat(elem, problem) << endOfLIne;
    }
    fileIntra.close();

    std::string fileNameInter = fileName + "-edges.csv";
    std::ofstream fileInter(fileNameInter.c_str());
    fileInter << "Source" << separator << "Target" << separator << "Type" << separator << "id" << separator << "Weight" << endOfLIne;
    id = 1;
    for (auto elem : solution) {
        for (auto otherElem : solution) {
            if (elem.getIdentificator() == otherElem.getIdentificator()) {
                 continue;
            }
            fileInter << elem.getIdentificator() << separator << otherElem.getIdentificator() <<
                    separator << "Undirected" << separator << id++ << separator <<
                    this->snowFlakeHelper.maxPairwiseCompatibility(elem, otherElem, problem) << endOfLIne;
        }
    }
}

WriterSolution::~WriterSolution() {

}

void WriterSolution::writeSnowFlakeIds(std::vector<SnowFlake>& snowFlakeAll, std::string fileName) {
    std::ofstream file(fileName.c_str());
    unsigned int id = 1;
    for (auto aSnowFlake : snowFlakeAll) {
        for (auto theId : aSnowFlake.ids()) {
            file << id << "," << theId << "\n";
        }
        ++id;
    }
    file.close();
}
