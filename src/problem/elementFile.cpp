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

void ElementFile::completeMapping(std::map<std::string, std::string> &id2str, Dao *dao) const
{
    std::ifstream file;
    file.open(this->fileNodeName_.c_str());
    std::string line;

    while(getline(file, line, '\n')) {
        std::vector<std::string> tokens;
        stringToVectorSplit(line, "\t", tokens);
        std::stringstream name;
        name<<tokens[0]<<"\t"<<tokens[1];
        id2str[tokens[0]] = name.str();
    }

    file.close();
}
