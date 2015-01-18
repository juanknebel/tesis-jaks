#include "writerSolutionAffiliations.h"

void WriterSolutionAffiliations::writeSolution(const std::vector<SnowFlake> &solution, std::string fileName, const Id2Str *node2name, double interSimilarityWeight) {
    std::ofstream file(fileName.c_str());
    file << "Bundle" << this->separator_ << "Title" << this->separator_ << "Location" << this->endOfLIne_;
    int bundle = 0;
    for (std::vector<SnowFlake>::const_iterator itSF = solution.begin(); itSF != solution.end(); ++itSF) {
        ++bundle;
        for (std::set<int>::const_iterator it = itSF->ids().begin(); it != itSF->ids().end(); ++it) {
            std::string node = itSF->getProblemNode(*it);
            file << "Bundle " << bundle << this->separator_ << (node2name == NULL ? node : node2name->getNodebyName(node)) << this->separator_ << this->endOfLIne_;
        }
    }
    file << "Objetive function" << this->separator_ << SnowFlake::objetiveFunction(solution, interSimilarityWeight);
    file.close();
}

WriterSolutionAffiliations::~WriterSolutionAffiliations(){
}
