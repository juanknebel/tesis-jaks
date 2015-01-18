#ifndef WRITERSOLUTION_H
#define WRITERSOLUTION_H

#include <fstream>
#include <iostream>
#include "../../problem/snowFlake.h"
#include "../identificator/id2Str.h"

class WriterSolution {
protected:
    std::string separator_;
    std::string endOfLIne_;
public:
    WriterSolution(std::string separator);

    virtual std::string showInScreen(std::vector<SnowFlake>& solution,const Id2Str* node2name);

    virtual void writeSolution(const std::vector<SnowFlake>& solution, std::string fileName, const Id2Str* node2name, double interSimilarityWeight) = 0;

    static void writeInterAndIntraValues(std::vector<SnowFlake>& solution, std::string fileName);

    static void writeSnowFlakeIds(std::vector<SnowFlake>& snowFlakeAll, std::string fileName);

    virtual ~WriterSolution();
};

#endif // WRITERSOLUTION_H
