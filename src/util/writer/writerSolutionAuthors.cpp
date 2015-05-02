#include "writerSolutionAuthors.h"

void WriterSolutionAuthors::writeSolution(const std::vector<SnowFlake> &solution, std::string fileName, const Id2Str *node2name,
                   double interSimilarityWeight, ProblemInstance &problem) {
    std::ofstream file(fileName.c_str());
    file << "Bundle" << this->separator_ << "Author" << this->separator_ << "Affiliation" << this->endOfLIne_;
    int bundle = 0;
    for (auto elem : solution) {
        ++bundle;
        for (auto innerElem : elem.ids()) {
            std::string node = this->snowFlakeHelper.getProblemNode(innerElem, problem);
            file << "Bundle " << bundle << this->separator_ << (node2name == nullptr ? node : node2name->getNodebyName(node)) << this->separator_ << this->endOfLIne_;
        }
    }
    file << "Objetive function" << this->separator_ << this->snowFlakeHelper.objetiveFunction(solution, interSimilarityWeight, problem);
    file.close();
}

WriterSolutionAuthors::~WriterSolutionAuthors() {
}
