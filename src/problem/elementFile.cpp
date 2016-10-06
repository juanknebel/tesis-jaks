//
// Created by zero on 11/09/16.
//

#include "elementFile.h"
#include "../util/system/stringUtilities.h"
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>

ElementFile::~ElementFile()
{

}

void ElementFile::completeMapping() const
{
    boost::property_tree::ptree pt;
    boost::property_tree::ini_parser::read_ini("Tesis.ini", pt);
    std::string directory = pt.get<std::string>("SectionFile.directoryOfWork");
    std::map<std::string, std::string> *id2str = this->node2name_.get();
    std::ifstream file;
    file.open(directory + this->fileNodeName_.c_str());
    std::string line;

    while(getline(file, line, '\n')) {
        std::vector<std::string> tokens;
        stringToVectorSplit(line, this->separator_, tokens);
        std::stringstream name;
        name<<tokens[0]<<this->separator_<<tokens[1];
        (*id2str)[tokens[0]] = name.str();
    }

    file.close();
}

void ElementFile::writeSolution(const std::vector<SnowFlake> &solution, std::string fileName, double gamma, ProblemInstance &theProblem) const
{
    std::map<std::string, std::string> *node2name = this->node2name_.get();
    std::ofstream file(fileName.c_str());
    file << "Bundle" << this->separator_ << "AtractionId" << this->separator_ << "Atraction" << "\n";

    for (auto aSnowFlake : solution) {
        for (auto aFlake : aSnowFlake.ids()) {
            std::string node = aFlake.getNodeId();
            file << "Bundle " << aSnowFlake.getIdentificator() << this->separator_ << (*node2name)[node] << this->separator_ << "\n";
        }
    }

    file << "Objetive function" << this->separator_ << SnowFlake::objetiveFunction(solution, gamma, theProblem)<<"\n";
    file << "Inter" << this->separator_ << SnowFlake::getInter(solution, theProblem) << "\n";
    file << "Intra" << this->separator_ << SnowFlake::getIntra(solution, theProblem);
    file.close();
}

std::string ElementFile::convertToJson(const std::vector<SnowFlake> &solution) const {
    return std::__cxx11::string();
}
