//
// Created by zero on 11/09/16.
//

#ifndef TESIS_JAKS_EXE_ELEMENTFILE_H
#define TESIS_JAKS_EXE_ELEMENTFILE_H
#include "element.h"
#include "snowFlake.h"

class ElementFile : public Element {
private:
    void completeMapping() const;
    std::string convertToJson(const std::vector<SnowFlake>& solution) const;
    void writeSolution(const std::vector<SnowFlake> &solution, std::string fileName, double gamma) const;
public:
    ElementFile() : Element() {
        this->fileTypeName_ = "type_name.csv";
        this->fileCompat_ = "node_compatibility.csv";
        this->fileCosts_ = "node_cost.csv";
        this->fileNodeName_ = "node_name.csv";
        this->fileCover_ = "node_cover.csv";
        this->elementType_ = "FILE";
        completeMapping();
    }
    ~ElementFile();
};


#endif //TESIS_JAKS_EXE_ELEMENTFILE_H
