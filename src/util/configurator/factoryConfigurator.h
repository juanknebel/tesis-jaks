#ifndef FACTORYCONFIGURATOR_H
#define FACTORYCONFIGURATOR_H

#include "configurationJaks.h"
#include "configurator.h"
#include "../../solver/factorySolver.h"
#include "../../problem/factoryProblem.h"

class FactoryConfigurator {
private:    
    Configurator* theConfigurator_;
public:
    FactoryConfigurator(ConfigurationJaks& configFile);
    ~FactoryConfigurator();

    Configurator* getTheConfigurator();
};

#endif // FACTORYCONFIGURATOR_H
