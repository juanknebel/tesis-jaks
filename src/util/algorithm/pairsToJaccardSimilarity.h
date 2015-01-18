/*
 * pairsToJaccardSimilarity.h
 *
 *  Created on: 15/08/2013
 *      Author: zero
 */

#ifndef PAIRSTOJACCARDSIMILARITY_H_
#define PAIRSTOJACCARDSIMILARITY_H_

#include <string>
#include <set>
#include <map>
#include <fstream>

class PairsToJaccardSimilarity {
public:
    static void execute(std::string fileParams);
    static void execute(std::string fileNameInput, std::string fileNameOutput, bool intersection, int keyField);
private:
    static std::string DEFAULT_FIELD_SEPARATOR;
    std::string fileNameInput_;
    std::string fileNameOutput_;
	bool intersection_;
	int keyField_;
	int valueField_;

	PairsToJaccardSimilarity();
    PairsToJaccardSimilarity(std::string fileNameInput, std::string fileNameOutput, bool intersection, int keyField);
	~PairsToJaccardSimilarity();

    void init(std::string fileNameInput, std::string fileNameOutput, bool intersection, int keyField);
    double computeIntersection(std::set<std::string>& set1, std::set<std::string>& set2);
    double computeJaccard(std::set<std::string>& set1, std::set<std::string>& set2);
};


#endif /* PAIRSTOJACCARDSIMILARITY_H_ */
