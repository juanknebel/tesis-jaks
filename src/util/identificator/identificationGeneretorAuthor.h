#ifndef IDENTIFICATIONGENERETORAUTHOR_H
#define IDENTIFICATIONGENERETORAUTHOR_H

#include "identificationGeneretor.h"

class IdentificationGeneretorAuthor : public IdentificationGeneretor {
public:
    IdentificationGeneretorAuthor(Dao* dao, std::string separator) : IdentificationGeneretor(dao, separator) {
        this->query_ = "SELECT AuthorId, name, affiliation_title FROM AUTHORS";
    }

    void fillTheMapping(std::map<std::string, std::string> *node2name);

    ~IdentificationGeneretorAuthor();
};

#endif // IDENTIFICATIONGENERETORAUTHOR_H
