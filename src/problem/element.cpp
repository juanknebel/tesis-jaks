//
// Created by zero on 11/09/16.
//

#include "element.h"

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
