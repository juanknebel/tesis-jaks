#ifndef FACTORYCONFIGURATOR_H
#define FACTORYCONFIGURATOR_H

#include "configurationJaks.h"
#include "configurator.h"
#include "configuratorToDataBase.h"
#include "../../solver/factorySolver.h"
#include "../../problem/factoryProblem.h"
#include "../writer/factoryWriter.h"
#include "../identificator/factoryIdentificationGenerator.h"

class FactoryConfigurator {
private:    
    FactoryConfigurator();
public:
    static Configurator* getTheConfigurator(ConfigurationJaks& configFile);
};

#endif // FACTORYCONFIGURATOR_H
