/*
 * problemInstanceFromFiles.h
 *
 *  Created on: 24/07/2013
 *      Author: jknebel
 */

#ifndef PROBLEMINSTANCEFROMFILES_H_
#define PROBLEMINSTANCEFROMFILES_H_

#include "problemInstance.h"

class ProblemInstanceFromFiles : public ProblemInstance {
public:
    ProblemInstanceFromFiles(std::string fileCosts, std::string fileCompat, std::string fileCover, double budget);
	ProblemInstanceFromFiles();
	~ProblemInstanceFromFiles();

private:
    void init(std::string fileCosts, std::string fileCompat, std::string fileCover);
    void loadIdMapping(std::string fileName);
    void loadInt2Double(std::string fileName);
    void loadAndSymmetrizeMatrix(int nElements, std::string fileName);
    void loadInt2IntSet(std::string fileName);
};


#endif /* PROBLEMINSTANCEFROMFILES_H_ */
