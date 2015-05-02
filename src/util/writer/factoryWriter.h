#ifndef FACTORYWRITER_H
#define FACTORYWRITER_H

#include "writerSolutionAffiliations.h"
#include "writerSolutionArticles.h"
#include "writerSolutionAuthors.h"
#include "../configurator/configurationJaks.h"
#include <memory>

class FactoryWriter {
private:
    FactoryWriter();
public:
    static std::unique_ptr<WriterSolution> getTheWriter(ConfigurationJaks& configFile,
                                                        SnowFlakeHelper aSnowFlakeHelper);
};

#endif // FACTORYWRITER_H
