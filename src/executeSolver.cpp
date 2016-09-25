#include <cstdlib>
#include <iostream>
#include <memory>
#include "executeSolver.h"
#include "util/algorithm/localSearch.h"

#include "problem/factoryProblem.h"
#include "solver/factorySolver.h"
#include "util/writer/factoryWriter.h"

#include "util/configurator/factoryConfigurator.h"

using namespace std;

void showSolution(SnowFlakeVector& solution, Configurator& configurator)
{
	if(configurator.getPrintToScreen()) {
		std::cout<<configurator.getTheWrtiter()->showInScreen(solution, configurator.getTheNodeName())<<std::endl;
	}
}

void writeSolution(SnowFlakeVector &solution, Configurator &configurator, String fileName,
                   Double interSimilarityWeight)
{
	if(configurator.getWriteToFile()) {
		WriterSolution* theWriter = configurator.getTheWrtiter();
		std::cout << "Writing the solution into the file: " << fileName << std::endl;
		theWriter->writeSolution(solution, fileName, configurator.getTheNodeName(), interSimilarityWeight);
		//WriterSolution::writeInterAndIntraValues(solution, fileName);
	}
}

void execute(ConfigurationJaks& configFile)
{
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
	fileName << "ToProduce-" << theConfigurator->getNumToProduce() << "Gamma-" << gamma << ".csv-Tabu";
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

void executeNew(std::string element, std::string algorithm, std::string strategy, double budget, double gamma,
                int numFlakes, int maxIter, int toProduce, bool writeToFile, bool printToScreen)
{
    std::unique_ptr<ProblemInstance> theProblem = std::move(FactoryProblem::getTheProblem(element, budget));
    std::unique_ptr<Solver> theSolver = std::move(FactorySolver::getTheSolver(theProblem.get(), algorithm, strategy, numFlakes, gamma));
    std::unique_ptr<WriterSolution> thwWriter = std::move(FactoryWriter::getTheWriter(element));

    SnowFlakeVector* solution = 0;
    SnowFlakeVector newSolution;

    try {
        solution = theSolver->solve(toProduce);
        LocalSearch localSearch;
        newSolution = localSearch.execute(maxIter,*solution, *(theSolver->getTheProblem()), gamma);
    }

    catch (Exception& e) {
        std::cerr<<e.what()<<std::endl;
        exit(0);
    }

    //showSolution(newSolution);
    std::stringstream fileName;
    //fileName << theConfigurator->getDirectoryOfWork() << theConfigurator->getSolverName();
    //fileName << theConfigurator->getTheStrategyName();
    //fileName << "ToProduce-" << theConfigurator->getNumToProduce() << "Gamma-" << gamma << ".csv-Tabu";
    //writeSolution(newSolution, *theConfigurator, fileName.str(), interSimilarityWeight);
    std::stringstream fileNameOrg;
    //fileNameOrg << theConfigurator->getDirectoryOfWork() << theConfigurator->getSolverName();
    //fileNameOrg << theConfigurator->getTheStrategyName();
    //fileNameOrg << "ToProduce-" << theConfigurator->getNumToProduce() << "Gamma-" << gamma << ".csv";
    //writeSolution(*solution, *theConfigurator, fileNameOrg.str(), interSimilarityWeight);
    int i=0;

    for (auto& bundle : *solution) {
        bundle.setIdentificator(i);
        i++;
    }

    std::cout<<"Primera solucion: "<<SnowFlake::objetiveFunction(*solution, gamma)<<std::endl;
    std::cout<<"Segunda solucion: "<<SnowFlake::objetiveFunction(newSolution, gamma)<<std::endl;
    delete solution;
}
