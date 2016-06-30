#include <cstdlib>
#include <iostream>
#include "executeSolver.h"
#include "util/configurator/factoryConfigurator.h"
#include "util/algorithm/localSearch.h"

using namespace std;

void showSolution(SnowFlakeVector& solution, Configurator& configurator) {
    if(configurator.getPrintToScreen()) {
        std::cout<<configurator.getTheWrtiter()->showInScreen(solution, configurator.getTheNodeName())<<std::endl;
	}
}

void writeSolution(SnowFlakeVector &solution, Configurator &configurator, String fileName,
                   Double interSimilarityWeight) {
    if(configurator.getWriteToFile()) {
        WriterSolution* theWriter = configurator.getTheWrtiter();
        std::cout << "Writing the solution into the file: " << fileName << std::endl;
        theWriter->writeSolution(solution, fileName, configurator.getTheNodeName(), interSimilarityWeight);
        //WriterSolution::writeInterAndIntraValues(solution, fileName);
	}
}

void execute(ConfigurationJaks& configFile) {
    Configurator* theConfigurator = FactoryConfigurator::getTheConfigurator(configFile);
    Solver* theSolver = theConfigurator->getTheSolver();
    Double gamma = theConfigurator->getGamma();
    Double interSimilarityWeight = 1.00 - gamma;
    SnowFlakeVector* solution = 0;
    SnowFlakeVector newSolution;
	try {
        solution = theSolver->solve(theConfigurator->getNumToProduce());
        LocalSearch localSearch;
        newSolution = localSearch.execute(20,*solution, *(theSolver->getTheProblem()), interSimilarityWeight);
	}
	catch (Exception& e) {
		std::cerr<<e.what()<<std::endl;
		exit(0);
	}
	/*catch ( ... ) {
		std::cerr<<"Unexpected error"<<std::endl;
		exit(0);
	}*/

    showSolution(newSolution, *theConfigurator);
    std::stringstream fileName;
    fileName << theConfigurator->getDirectoryOfWork() << theConfigurator->getSolverName();
    fileName << theConfigurator->getTheStrategyName();
    fileName << "TabuToProduce-" << theConfigurator->getNumToProduce() << "Gamma-" << gamma << ".csv";
    writeSolution(newSolution, *theConfigurator, fileName.str(), interSimilarityWeight);
    std::stringstream fileNameOrg;
    fileNameOrg << theConfigurator->getDirectoryOfWork() << theConfigurator->getSolverName();
    fileNameOrg << theConfigurator->getTheStrategyName();
    fileNameOrg << "ToProduce-" << theConfigurator->getNumToProduce() << "Gamma-" << gamma << ".csv";
    writeSolution(*solution, *theConfigurator, fileNameOrg.str(), interSimilarityWeight);
    int i=0;
    for (auto& bundle : *solution) {
        bundle.setIdentificator(i);
        i++;
    }
    std::cout<<"Primera solucion: "<<SnowFlake::objetiveFunction(*solution, interSimilarityWeight)<<std::endl;
    std::cout<<"Segunda solucion: "<<SnowFlake::objetiveFunction(newSolution, interSimilarityWeight)<<std::endl;
    delete solution;
    delete theConfigurator;
}
