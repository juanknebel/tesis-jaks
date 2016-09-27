//
// Created by zero on 11/09/16.
//

#ifndef TESIS_JAKS_EXE_ELEMENT_H
#define TESIS_JAKS_EXE_ELEMENT_H

#include <string>
#include <map>
#include <fstream>
#include "../dao/dao.h"
#include "snowFlake.h"

class Element {
protected:
    std::string tableCost_;
    std::string tableCompat_;
    std::string tableCover_;
    std::string tableConvertionElementToItem_;
    std::string fieldCost_;
    std::string fieldCover_;
    std::string fieldPrimary_;
    std::string fieldPrimaryDescription_;
    std::string fieldElement_;
    std::string fieldItem_;
    std::string fieldItemCompat1_;
    std::string fieldItemCompat2_;
    std::string fieldCompat_;

    std::string fileTypeName_;
    std::string fileCompat_;
    std::string fileCosts_;
    std::string fileNodeName_;
    std::string fileCover_;

    std::string elementType_;
    std::string separator_;

    std::unique_ptr<std::map<std::string, std::string>> node2name_;
protected:
    virtual void completeMapping() const = 0;
public:
    Element();
    const std::string &getTableCost() const;
    const std::string &getTableCompat() const;
    const std::string &getTableCover() const;
    const std::string &getTableConvertionElementToItem() const;
    const std::string &getFieldCost() const;
    const std::string &getFieldCover() const;
    const std::string &getFieldPrimary() const;
    const std::string &getFieldPrimaryDescription() const;
    const std::string &getFieldElement() const;
    const std::string &getFieldItem() const;
    const std::string &getFieldItemCompat1() const;
    const std::string &getFieldItemCompat2() const;
    const std::string &getFieldCompat() const;
    const std::string &getFileTypeName() const;
    const std::string &getFileCompat() const;
    const std::string &getFileCosts() const;
    const std::string &getFileNodeName() const;
    const std::string &getFileCover() const;
    const std::string &getElementType() const;
    virtual void writeSolution(const std::vector<SnowFlake> &solution, std::string fileName, double gamma) const = 0;

    static std::string showInScreen(const Element* element, std::vector<SnowFlake> &solution);
    static std::string showInScreen(const Element* element, const SnowFlake& snowFlake);
    virtual ~Element();
};


#endif //TESIS_JAKS_EXE_ELEMENT_H
