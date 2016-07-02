/*
 * systemUtilities.cpp
 *
 *  Created on: 25/08/2013
 *      Author: zero
 */

#include "systemUtilities.h"

String runExternalProgram(int argc, char *argv[])
{
	/**
	 * TODO: si bien recibe un vector donde en el primer elemento deberia ser el comando y el resto los argumentos.
	 * Por ahora solo se usa el primer elemento donde esta el comando y los argumentos juntos en el mismo string.
	**/
	String toExucute = "";

	for (int i = 0; i < argc; ++i) {
		toExucute.append(argv[i]).append(" ");
	}

	FILE *tempFile = popen(toExucute.c_str(), "r");
	String output = "";
	char buffer [100];

	while (!feof(tempFile)) {
		if ( fgets (buffer , 100 , tempFile) == 0 ) break;

		output.append(buffer);
	}

	pclose(tempFile);
	return output;
}
