#include "factoryProblem.h"

FactoryProblem::FactoryProblem()
{
}

ProblemInstance* FactoryProblem::getTheProblemInstance(ConfigurationJaks& configFile)
{
	std::string directoryOfWork = configFile["directory_work"];
	std::string fileOfCosts = configFile["file_costs"];
	std::string fileOfCompatibility = configFile["file_compat"];
	std::string fileOfCover = configFile["file_cover"];
	double budget = atof(configFile["budget"].c_str());

	bool withSpecificItem = configFile["with_specific_item"] == "1";
	int specificItem = atoi(configFile["specific_item"].c_str());

	ProblemInstanceFromFiles* theProblem = new ProblemInstanceFromFiles(
	    directoryOfWork+fileOfCosts, directoryOfWork+fileOfCompatibility,
	    directoryOfWork+fileOfCover, budget);

	if (withSpecificItem) {
		theProblem->setSpecificItem(specificItem);
	}

	return theProblem;
}

ProblemInstance* FactoryProblem::getTheProblemInstance(ConfigurationJaks &configFile, Dao* dao)
{
	std::string tableOfCosts = configFile["table_costs"];
	std::string tableOfCompatibility = configFile["table_compat"];
	std::string tableOfCover = configFile["table_cover"];
	std::string tableOfMappingIds = configFile["table_convertion_element_item"];
	std::string fieldForCost = configFile["field_cost"];
	std::string fieldForCompatibility = configFile["field_compat"];
	std::string fieldForCover = configFile["field_cover"];
	std::string fieldPrimary = configFile["field_primary"];
	std::string fieldPrimaryDescription = configFile["field_primary_description"];
	std::string fieldItem = configFile["field_item"];
	std::string fieldItemCompat1 = configFile["field_item_compat1"];
	std::string fieldItemCompat2 = configFile["field_item_compat2"];
	double budget = atof(configFile["budget"].c_str());

	ProblemInstanceFromDataBase *theProblem = new ProblemInstanceFromDataBase(
	    dao, tableOfCosts, tableOfCompatibility, tableOfCover, tableOfMappingIds,
	    fieldForCost, fieldForCompatibility, fieldForCover, fieldPrimary,
	    fieldPrimaryDescription, fieldItem, fieldItemCompat1, fieldItemCompat2, budget);
	return theProblem;
}
