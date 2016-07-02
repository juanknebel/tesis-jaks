#ifndef FACTORYPROBLEM_H
#define FACTORYPROBLEM_H

#include "problemInstanceFromDataBase.h"
#include "problemInstanceFromFiles.h"
#include "../util/configurator/configurationJaks.h"
#include "../dao/dao.h"

class FactoryProblem {
private:
	FactoryProblem();
public:
	static ProblemInstance* getTheProblemInstance(ConfigurationJaks &configFile);
	static ProblemInstance* getTheProblemInstance(ConfigurationJaks &configFile, Dao* dao);
};

#endif // FACTORYPROBLEM_H
