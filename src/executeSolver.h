#include "util/configurator/configurationJaks.h"

void execute(ConfigurationJaks& configFileName);

void executeNew(std::string element, std::string algorithm, std::string strategy, double budget, double gamma,
                int numFlakes, int maxIter, int toProduce, bool writeToFile, bool printToScreen);
