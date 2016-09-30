#include <cstdlib>
#include <iostream>
#include <memory>
#include "executeSolver.h"
#include "util/algorithm/localSearch.h"

#include "problem/factoryProblem.h"
#include "solver/factorySolver.h"
#include "problem/factoryElement.h"

using namespace std;

/*
void showSolution(SnowFlakeVector& solution, Configurator& configurator)
{
	if(configurator.getPrintToScreen()) {
		std::cout<<configurator.getTheWrtiter()->showInScreen(solution, configurator.getTheNodeName())<<std::endl;
	}
}

void writeSolution(SnowFlakeVector &solution, Configurator &configurator, std::string fileName,
                   double interSimilarityWeight)
{
	if(configurator.getWriteToFile()) {
		WriterSolution* theWriter = configurator.getTheWrtiter();
		std::cout << "Writing the solution into the file: " << fileName << std::endl;
		theWriter->writeSolution(solution, fileName, configurator.getTheNodeName(), interSimilarityWeight);
		//WriterSolution::writeInterAndIntraValues(solution, fileName);
	}
}
*/

void executeNew(std::string element, std::string algorithm, std::string strategy, double budget, double gamma,
                int numFlakes, int maxIter, int toProduce, bool writeToFile, bool printToScreen)
{
    std::cout << "Algoritmo para la resolución: " << algorithm << std::endl;
    std::cout << "Estrategia de selección: " << strategy << std::endl;
    std::cout << "Elemento usado: " << element << std::endl;
    std::cout << "Cantidad de bundles: " << numFlakes << std::endl;
    std::cout << "Presupuesto: " << budget << std::endl;
    std::cout << "Valor del gamma: " << gamma << std::endl;
    std::cout << "Bundles a producir solo para BOBO: " << toProduce << std::endl;

    std::unique_ptr<Element> theElement = std::move(FactoryElement::getTheElement(element));
    std::unique_ptr<ProblemInstance> theProblem = std::move(FactoryProblem::getTheProblem(theElement.get(), budget));
    std::unique_ptr<Solver> theSolver = std::move(FactorySolver::getTheSolver(theProblem.get(), algorithm, strategy, numFlakes, gamma));

    SnowFlakeVector* solution = 0;
    SnowFlakeVector newSolution;

    try {
        solution = theSolver.get()->solve(toProduce);
        LocalSearch localSearch;
        newSolution = localSearch.execute(maxIter,*solution, *theProblem.get(), gamma);
    }

    catch (Exception& e) {
        std::cerr<<e.what()<<std::endl;
        exit(0);
    }

    int i=0;
    for (auto& bundle : *solution) {
        bundle.setIdentificator(i);
        i++;
    }
    std::cout << Element::convertToJson(*solution, *theElement.get()) << std::endl;
    if (writeToFile) {
        std::stringstream fileName;
        std::stringstream fileNameTabu;
        fileName << algorithm << strategy << "Gamma-" << gamma << ".csv";
        fileNameTabu << algorithm << strategy << "Gamma-" << gamma << "-Tabu.csv";
        std::cout << "Escribiendo la solución original en: " << fileName.str() << std::endl;
        theElement.get()->writeSolution(*solution, fileName.str(), gamma);
        std::cout << "Escribiendo la solución con tabu en: " << fileNameTabu.str() << std::endl;
        theElement.get()->writeSolution(newSolution, fileNameTabu.str(), gamma);
    }

    if (printToScreen) {
        std::cout << Element::showInScreen(theElement.get(), *solution) << std::endl;
        std::cout << Element::showInScreen(theElement.get(), newSolution) << std::endl;

        std::cout<<"Primera solucion: "<<SnowFlake::objetiveFunction(*solution, gamma)<<std::endl;
        std::cout<<"Segunda solucion: "<<SnowFlake::objetiveFunction(newSolution, gamma)<<std::endl;
    }

    delete solution;
}
