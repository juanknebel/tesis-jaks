#include <cstdlib>
#include <iostream>
#include "executeSolver.h"
#include "util/configurator/factoryConfigurator.h"
#include "util/writer/writerSolution.h"

using namespace std;

void showSolution(SnowFlakeVector& solution, Configurator& configurator) {
    if(configurator.getPrintToScreen()) {
        std::cout<<configurator.getTheWrtiter()->showInScreen(solution, configurator.getTheNodeName())<<std::endl;
	}
}

void writeSolution(SnowFlakeVector& solution, Configurator& configurator) {
    if(configurator.getWriteToFile()) {
        WriterSolution* theWriter = configurator.getTheWrtiter();
		std::stringstream fileName;
        fileName << configurator.getDirectoryOfWork() << "Solver-";
        fileName << configurator.getSolverName();
        Double gamma = configurator.getGamma();
        Double interSimilarityWeight = 1.00 - gamma;

        fileName << "_ToProduce-"<<configurator.getNumToProduce()<<"_Gamma-"<<gamma<<".csv";
		std::cout<<"Writing the solution into the file: "<<fileName.str()<<std::endl;
        theWriter->writeSolution(solution, fileName.str(), configurator.getTheNodeName(), interSimilarityWeight);
        WriterSolution::writeInterAndIntraValues(solution, fileName.str());
	}
}

void execute(ConfigurationJaks& configFile) {
    Configurator* theConfigurator = FactoryConfigurator::getTheConfigurator(configFile);
    Solver* theSolver = theConfigurator->getTheSolver();

	SnowFlakeVector* solution = 0;
	try {
        solution = theSolver->solve(theConfigurator->getNumToProduce());
	}
	catch (Exception& e) {
		std::cerr<<e.what()<<std::endl;
		exit(0);
	}
	catch ( ... ) {
		std::cerr<<"Unexpected error"<<std::endl;
		exit(0);
	}
    showSolution(*solution, *theConfigurator);
    writeSolution(*solution, *theConfigurator);
	delete solution;
    delete theConfigurator;
}
