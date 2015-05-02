#ifndef WRITERSOLUTION_H
#define WRITERSOLUTION_H

#include <fstream>
#include <iostream>
#include "../../problem/snowFlake.h"
#include "../identificator/id2Str.h"
#include "../../problem/snowFlakeHelper.h"

class WriterSolution {
protected:
    std::string separator_;
    std::string endOfLIne_;
    SnowFlakeHelper snowFlakeHelper;
public:
    WriterSolution(std::string separator, SnowFlakeHelper aSnowFlakeHelper);

    virtual std::string showInScreen(std::vector<SnowFlake> &solution, const Id2Str *node2name, ProblemInstance &problem);

    virtual void writeSolution(const std::vector<SnowFlake> &solution, std::string fileName, const Id2Str *node2name,
                       double interSimilarityWeight, ProblemInstance &problem) = 0;

    void writeInterAndIntraValues(std::vector<SnowFlake> &solution, std::string fileName,
                                                        ProblemInstance &problem);

    void writeSnowFlakeIds(std::vector<SnowFlake>& snowFlakeAll, std::string fileName);

    virtual ~WriterSolution();
};

#endif // WRITERSOLUTION_H
