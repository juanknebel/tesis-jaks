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

void executeNew(std::string element, std::string algorithm, std::string strategy, std::string directory, double budget, double gamma,
                int numFlakes, int maxIter, int toProduce, bool writeToFile, bool printToScreen, bool json)
{
    std::cout << "Algoritmo para la resolución: " << algorithm << std::endl;
    std::cout << "Estrategia de selección: " << strategy << std::endl;
    std::cout << "Elemento usado: " << element << std::endl;
    std::cout << "Cantidad de bundles: " << numFlakes << std::endl;
    std::cout << "Presupuesto: " << budget << std::endl;
    std::cout << "Valor del gamma: " << gamma << std::endl;
    std::cout << "Bundles a producir solo para BOBO: " << toProduce << std::endl;
    std::cout << "Guardar soluciones: " << ((writeToFile) ? "Si" : "No") << std::endl;
    std::cout << "Guardar json: " << ((json) ? "Si" : "No") << std::endl;
    std::cout << "Mostrar solución en pantalla: " << ((printToScreen) ? "Si" : "No") << std::endl;
    std::cout << "Directorio donde se destino de los archivos: " << directory << std::endl;

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

    std::stringstream fileName;
    std::stringstream fileNameTabu;
    fileName << directory << algorithm << strategy << "Gamma-" << gamma;
    fileNameTabu << directory << algorithm << strategy << "Gamma-" << gamma;

    if (json) {
        Element::saveJson(*solution, *theElement.get(), fileName.str() + ".json");
        Element::saveJson(newSolution, *theElement.get(), fileNameTabu.str() + "-Tabu.json");
    }

    if (writeToFile) {
        Element::saveSolution(*solution, fileName.str() + ".csv", gamma, *theElement.get());
        Element::saveSolution(newSolution, fileNameTabu.str() + "-Tabu.csv", gamma, *theElement.get());
    }

    if (printToScreen) {
        std::cout << Element::showInScreen(theElement.get(), *solution) << std::endl;
        std::cout << Element::showInScreen(theElement.get(), newSolution) << std::endl;
        std::cout<<"Primera solucion: "<<SnowFlake::objetiveFunction(*solution, gamma)<<std::endl;
        std::cout<<"Segunda solucion: "<<SnowFlake::objetiveFunction(newSolution, gamma)<<std::endl;
    }

    delete solution;
}
