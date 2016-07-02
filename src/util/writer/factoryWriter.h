#ifndef FACTORYWRITER_H
#define FACTORYWRITER_H

#include "writerSolutionAffiliations.h"
#include "writerSolutionArticles.h"
#include "writerSolutionAuthors.h"
#include "writterSolutionFile.h"
#include "../configurator/configurationJaks.h"

class FactoryWriter {
private:
	FactoryWriter();
public:
	static WriterSolution* getTheWriter(ConfigurationJaks& configFile);
};

#endif // FACTORYWRITER_H
