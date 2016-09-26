//
// Created by zero on 11/09/16.
//

#ifndef TESIS_JAKS_EXE_ELEMENTFILE_H
#define TESIS_JAKS_EXE_ELEMENTFILE_H
#include "element.h"
#include "../dao/dao.h"

class ElementFile : public Element {
public:
    ElementFile() : Element() {
        this->fileTypeName_ = "type_name.csv";
        this->fileCompat_ = "node_compatibility.csv";
        this->fileCosts_ = "node_cost.csv";
        this->fileNodeName_ = "node_name.csv";
        this->fileCover_ = "node_cover.csv";
        this->elementType_ = "FILE";
    }
    void completeMapping(std::map<std::string, std::string> &id2str, Dao *dao) const;
    ~ElementFile();
};


#endif //TESIS_JAKS_EXE_ELEMENTFILE_H
