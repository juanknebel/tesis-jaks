//
// Created by zero on 11/09/16.
//

#include "element.h"
#include "../util/system/stringUtilities.h"

Element::Element()
{
    this->tableCost_ = "";
    this->tableCompat_ = "";
    this->tableCover_ = "";
    this->tableConvertionElementToItem_ = "";
    this->fieldCost_ = "";
    this->fieldCover_ = "";
    this->fieldPrimary_ = "";
    this->fieldPrimaryDescription_ = "";
    this->fieldElement_ = "";
    this->fieldItem_ = "";
    this->fieldItemCompat1_ = "";
    this->fieldItemCompat2_ = "";
    this->fieldCompat_ = "";

    this->fileTypeName_ = "";
    this->fileCompat_ = "";
    this->fileCosts_ = "";
    this->fileNodeName_ = "";
    this->fileCover_ = "";

    this->elementType_ = "ERROR";
    this->separator_ = "\t";

    this->node2name_ = std::unique_ptr<std::map<std::string, std::string>> (new std::map<std::string, std::string>);
}

Element::~Element()
{

}

const std::string &Element::getTableCost() const {
    return tableCost_;
}

const std::string &Element::getTableCompat() const {
    return tableCompat_;
}

const std::string &Element::getTableCover() const {
    return tableCover_;
}

const std::string &Element::getTableConvertionElementToItem() const {
    return tableConvertionElementToItem_;
}

const std::string &Element::getFieldCost() const {
    return fieldCost_;
}

const std::string &Element::getFieldCover() const {
    return fieldCover_;
}

const std::string &Element::getFieldPrimary() const {
    return fieldPrimary_;
}

const std::string &Element::getFieldPrimaryDescription() const {
    return fieldPrimaryDescription_;
}

const std::string &Element::getFieldElement() const {
    return fieldElement_;
}

const std::string &Element::getFieldItem() const {
    return fieldItem_;
}

const std::string &Element::getFieldItemCompat1() const {
    return fieldItemCompat1_;
}

const std::string &Element::getFieldItemCompat2() const {
    return fieldItemCompat2_;
}

const std::string &Element::getFieldCompat() const {
    return fieldCompat_;
}

const std::string &Element::getFileTypeName() const {
    return fileTypeName_;
}

const std::string &Element::getFileCompat() const {
    return fileCompat_;
}

const std::string &Element::getFileCosts() const {
    return fileCosts_;
}

const std::string &Element::getFileNodeName() const {
    return fileNodeName_;
}

const std::string &Element::getFileCover() const {
    return fileCover_;
}

const std::string &Element::getElementType() const {
    return elementType_;
}

std::string Element::showInScreen(const Element* element, std::vector<SnowFlake> &solution)
{
    std::string result = "\n";
    int avgCost = 0;
    int avgCover = 0;
    int avgSize = 0;
    int avgSumIntraCompat = 0;
    int solutionsSize = solution.size();

    for (auto aFlake : solution) {
        avgCost += aFlake.getCost();
        avgCover += aFlake.getCoverSize();
        avgSize += aFlake.ids().size();
        avgSumIntraCompat += aFlake.getSumIntraCompat();
        result.append(Element::showInScreen(element, aFlake));
    }

    result.append("-------------------------------------------------\n");
    result.append("SOLUTION_SIZE = " + convertToString(solutionsSize) + "\n");
    result.append("AVG_COST = " + convertToString(avgCost / (double) solutionsSize) + "\n");
    result.append("AVG_COVER = " + convertToString(avgCover / (double) solutionsSize) + "\n");
    result.append("AVG_SIZE = " + convertToString(avgSize / (double) solutionsSize) + "\n");
    result.append("AVG_SUM_INTRA_COMPAT = " + convertToString(avgSumIntraCompat / (double) solutionsSize) + "\n");

    return result;
}

std::string Element::showInScreen(const Element* element, const SnowFlake &snowFlake) {
    std::map<std::string, std::string> *node2name = element->node2name_.get();
    std::string result = "";
    for (auto anElement : snowFlake.ids()) {
        std::string node = snowFlake.getProblemNode(anElement);;
        double cost = snowFlake.getCostNode(anElement);
        result.append(" * ");
        result.append(node + " " + (*node2name)[node]);
        result.append(" (cost=" + convertToString(cost) + ")\n");
    }

    result.append("SIZE             = " + convertToString((int)snowFlake.ids().size()) + "\n");
    result.append("COVERAGE         = " + convertToString(snowFlake.getCoverSize()) + "\n");
    result.append("COST             = " + convertToString(snowFlake.getCost()) + "\n");
    result.append("MIN_INTRA_COMPAT = " + convertToString(snowFlake.getMinCompat()) + "\n");
    result.append("SUM_INTRA_COMPAT = " + convertToString(snowFlake.getSumIntraCompat()) + "\n\n");
    return result;
}

std::string Element::convertToJson(const std::vector<SnowFlake> &solution, const Element &element) {
    return element.convertToJson(solution);
}

/*
 * void WriterSolution:: writeInterAndIntraValues(std::vector<SnowFlake> &solution, std::string fileName)
{
	std::string separator = "\t";
	std::string endOfLIne = "\n";
	std::string fileNameIntra = fileName + "-nodes.csv";
	FileOutput fileIntra(fileNameIntra.c_str());
	fileIntra << "id" << separator << "Label" << separator << "Intra" << endOfLIne;
	int id = 1;

	for (std::vector<SnowFlake>::iterator it = solution.begin(); it != solution.end(); ++it) {
		it->setIdentificator(id);
		id++;
		fileIntra << it->getIdentificator() << separator << "Bundle" << it->getIdentificator() << separator << it->getSumIntraCompat() << endOfLIne;
	}

	fileIntra.close();

	std::string fileNameInter = fileName + "-edges.csv";
	FileOutput fileInter(fileNameInter.c_str());
	fileInter << "Source" << separator << "Target" << separator << "Type" << separator << "id" << separator << "Weight" << endOfLIne;
	id = 1;

	for (std::vector<SnowFlake>::iterator it = solution.begin(); it != solution.end(); ++it) {
		for (std::vector<SnowFlake>::iterator it2 = it; it2 != solution.end(); ++it2) {
			if (it->getIdentificator() == it2->getIdentificator()) {
				continue;
			}

			fileInter << it->getIdentificator() << separator << it2->getIdentificator() << separator << "Undirected" << separator << id++ << separator << SnowFlake::maxPairwiseCompatibility(*it, *it2) << endOfLIne;
		}
	}
}


 void WriterSolution::writeSnowFlakeIds(std::vector<SnowFlake>& snowFlakeAll, std::string fileName)
{
	FileOutput file(fileName.c_str());
	int id = 1;

	for (std::vector<SnowFlake>::iterator it = snowFlakeAll.begin(); it != snowFlakeAll.end(); ++it) {

		std::set<int> idSet = it->ids();

		for (std::set<int>::iterator itSF = idSet.begin(); itSF != idSet.end(); ++itSF) {
			file << id << "," << (*itSF) << "\n";
		}

		++id;
	}

	file.close();
}
 */