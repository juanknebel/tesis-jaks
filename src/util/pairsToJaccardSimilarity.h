/*
 * pairsToJaccardSimilarity.h
 *
 *  Created on: 15/08/2013
 *      Author: zero
 */

#ifndef PAIRSTOJACCARDSIMILARITY_H_
#define PAIRSTOJACCARDSIMILARITY_H_

#include "redefinitions.h"

class PairsToJaccardSimilarity {
public:
	static void execute(String fileParams);
	static void execute(String fileNameInput, String fileNameOutput, bool intersection, int keyField);
private:
	static String DEFAULT_FIELD_SEPARATOR;
	String fileNameInput_;
	String fileNameOutput_;
	bool intersection_;
	int keyField_;
	int valueField_;

	PairsToJaccardSimilarity();
	PairsToJaccardSimilarity(String fileNameInput, String fileNameOutput, bool intersection, int keyField);
	~PairsToJaccardSimilarity();

	void init(String fileNameInput, String fileNameOutput, bool intersection, int keyField);
	Double computeIntersection(StringSet& set1, StringSet& set2);
	Double computeJaccard(StringSet& set1, StringSet& set2);
};


#endif /* PAIRSTOJACCARDSIMILARITY_H_ */
