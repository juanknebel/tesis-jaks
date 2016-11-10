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

std::string ElementFile::convertToJson(const std::vector<SnowFlake> &solution) const {
    return std::__cxx11::string();
}

void ElementFile::completeDataForQtModel(const std::vector<SnowFlake> &solution, QStandardItemModel *model) const
{
    std::map<std::string, std::string> *node2name = this->node2name_.get();
    int row = 0;
    for (auto aFlake : solution) {
        for (auto anElement : aFlake.ids()) {
            std::string node = aFlake.getProblemNode(anElement);
            std::stringstream bundleId;
            bundleId << "Bundle " << aFlake.getIdentificator();
            QString bundleIdent = QString::fromUtf8(bundleId.str().data(), bundleId.str().size());
            QStandardItem *item = new QStandardItem(bundleIdent);
            model->setItem(row, 0, item);
            QString name = QString::fromUtf8(((*node2name)[node]).data(), ((*node2name)[node]).size());
            item = new QStandardItem(name);
            model->setItem(row, 1, item);
            row++;
        }
    }
    QStringList labelList = {"Bundle", "Identificación"};
    model->setHorizontalHeaderLabels(labelList);
}
