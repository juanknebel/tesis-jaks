//
// Created by zero on 11/09/16.
//

#include "elementFile.h"
#include "../util/system/stringUtilities.h"
#include "../dao/dao.h"
#include <sstream>

ElementFile::~ElementFile()
{

}

void ElementFile::completeMapping(Dao *dao) const
{
    std::map<std::string, std::string> *id2str = this->node2name_.get();
    std::ifstream file;
    file.open(this->fileNodeName_.c_str());
    std::string line;

    while(getline(file, line, '\n')) {
        std::vector<std::string> tokens;
        stringToVectorSplit(line, "\t", tokens);
        std::stringstream name;
        name<<tokens[0]<<"\t"<<tokens[1];
        (*id2str)[tokens[0]] = name.str();
    }

    file.close();
}

void ElementFile::writeSolution(const std::vector<SnowFlake> &solution, std::string fileName, double gamma) const
{
    std::map<std::string, std::string> *node2name = this->node2name_.get();
    std::ofstream file(fileName.c_str());
    file << "Bundle" << this->separator_ << "AtractionId" << this->separator_ << "Atraction" << "\n";

    for (auto aFlake : solution) {
        for (auto anElement : aFlake.ids()) {
            std::string node = aFlake.getProblemNode(anElement);
            file << "Bundle " << aFlake.getIdentificator() << this->separator_ << (*node2name)[node] << this->separator_ << "\n";
        }
    }

    file << "Objetive function" << this->separator_ << SnowFlake::objetiveFunction(solution, gamma)<<"\n";
    file << "Inter" << this->separator_ << SnowFlake::getInter(solution) << "\n";
    file << "Intra" << this->separator_ << SnowFlake::getIntra(solution);
    file.close();
}
