#include "writerSolutionAuthors.h"

void WriterSolutionAuthors::writeSolution(const std::vector<SnowFlake>& solution, String fileName, const Id2Str* node2name, Double interSimilarityWeight) {
    FileOutput file(fileName.c_str());
    file << "Bundle\tAuthor\tAffiliation\n";
    int bundle = 0;
    for (std::vector<SnowFlake>::const_iterator itSF = solution.begin(); itSF != solution.end(); ++itSF) {
        ++bundle;
        for (IntSet::const_iterator it = itSF->ids().begin(); it != itSF->ids().end(); ++it) {
            String node = itSF->getProblemNode(*it);
            file << "Bundle " << bundle << "\t" << (node2name == NULL ? node : node2name->getNodebyName(node)) << "\t\n";
        }
    }
    file << "Objetive function \t" << SnowFlake::objetiveFunction(solution, interSimilarityWeight);
    file.close();
}

WriterSolutionAuthors::~WriterSolutionAuthors() {
}
