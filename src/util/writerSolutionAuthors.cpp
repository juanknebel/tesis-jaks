#include "writerSolutionAuthors.h"

void WriterSolutionAuthors::writeSolution(const std::vector<SnowFlake>& solution, String fileName, const Id2Str* node2name, Double interSimilarityWeight) {
    FileOutput file(fileName.c_str());
    file << "Bundle" << this->separator_ << "Author" << this->separator_ << "Affiliation" << this->endOfLIne_;
    int bundle = 0;
    for (std::vector<SnowFlake>::const_iterator itSF = solution.begin(); itSF != solution.end(); ++itSF) {
        ++bundle;
        for (IntSet::const_iterator it = itSF->ids().begin(); it != itSF->ids().end(); ++it) {
            String node = itSF->getProblemNode(*it);
            file << "Bundle " << bundle << this->separator_ << (node2name == NULL ? node : node2name->getNodebyName(node)) << this->separator_ << this->endOfLIne_;
        }
    }
    file << "Objetive function" << this->separator_ << SnowFlake::objetiveFunction(solution, interSimilarityWeight);
    file.close();
}

WriterSolutionAuthors::~WriterSolutionAuthors() {
}
