#ifndef WRITERSOLUTION_H
#define WRITERSOLUTION_H

#include "../../problem/snowFlake.h"
#include "../identificator/id2Str.h"
#include "../redefinitions.h"

class WriterSolution {
protected:
    String separator_;
    String endOfLIne_;
public:
    WriterSolution(String separator);

    virtual String showInScreen(std::vector<SnowFlake>& solution,const Id2Str* node2name);

    virtual void writeSolution(const std::vector<SnowFlake>& solution, String fileName, const Id2Str* node2name, Double interSimilarityWeight) = 0;

    static void writeInterAndIntraValues(std::vector<SnowFlake>& solution, String fileName);

    static void writeSnowFlakeIds(std::vector<SnowFlake>& snowFlakeAll, String fileName);

    virtual ~WriterSolution();
};

#endif // WRITERSOLUTION_H
