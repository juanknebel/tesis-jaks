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
	ProblemInstanceFromFiles(String fileCosts, String fileCompat, String fileCover, Double budget);
	ProblemInstanceFromFiles();
	~ProblemInstanceFromFiles();

private:
	void init(String fileCosts, String fileCompat, String fileCover);
	void loadIdMapping(String fileName);
	void loadInt2Double(String fileName);
	void loadAndSymmetrizeMatrix(int nElements, String fileName);
	void loadInt2IntSet(String fileName);
};


#endif /* PROBLEMINSTANCEFROMFILES_H_ */
