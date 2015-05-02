#ifndef FACTORYPROBLEM_H
#define FACTORYPROBLEM_H

#include "problemInstanceFromDataBase.h"
#include "problemInstanceFromFiles.h"
#include "../util/configurator/configurationJaks.h"
#include "../dao/dao.h"
#include <memory>

class FactoryProblem {
private:
    FactoryProblem();
public:
    static std::unique_ptr<ProblemInstance> getTheProblemInstance(ConfigurationJaks &configFile);
    static std::unique_ptr<ProblemInstance> getTheProblemInstance(ConfigurationJaks &configFile, Dao* dao);
};

#endif // FACTORYPROBLEM_H
