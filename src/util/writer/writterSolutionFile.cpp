//
// Created by zero on 05/12/15.
//

#include "writterSolutionFile.h"

void WritterSolutionFile::writeSolution(const std::vector<SnowFlake>& solution, String fileName, const Id2Str* node2name, Double interSimilarityWeight)
{
	FileOutput file(fileName.c_str());
	file << "Bundle" << this->separator_ << "AtractionId" << this->separator_ << "Atraction" << this->endOfLIne_;
	int bundle = 0;

	for (std::vector<SnowFlake>::const_iterator itSF = solution.begin(); itSF != solution.end(); ++itSF) {
		++bundle;

		for (IntSet::const_iterator it = itSF->ids().begin(); it != itSF->ids().end(); ++it) {
			String node = itSF->getProblemNode(*it);
			file << "Bundle " << bundle << this->separator_ << (node2name == NULL ? node : node2name->getNodebyName(node)) << this->separator_ << this->endOfLIne_;
		}
	}

	file << "Objetive function" << this->separator_ << SnowFlake::objetiveFunction(solution, interSimilarityWeight)<<this->endOfLIne_;
	file << "Inter" << this->separator_ << SnowFlake::getInter(solution, interSimilarityWeight)<<this->endOfLIne_;
	file << "Intra" << this->separator_ << SnowFlake::getIntra(solution, interSimilarityWeight);
	file.close();
}

WritterSolutionFile::~WritterSolutionFile()
{
}