/*
    <one line to give the program's name and a brief idea of what it does.>
    Copyright (C) 2013  Juan <email>

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
*/

/* Ejemplo de un archivo de configuracion
 * #Archivo de configuracion para el programa tesis-jaks
 * #Con # son los comentarios, y los datos estan separados por una tabulacion
 * #Nombre del directorio de trabajo
 * DIRECTORY_WORK	/home/zero/Projects/tesis-jaks/build/
 * #Nombre de los archivos
 * FILE_COSTS	node_cost.csv
 * FILE_COMPAT	node_compatibility.csv
 * FILE_COVER	node_cover.csv
 * FILE_NODE_NAME	node_name.csv
 * FILE_TYPE_NAME	type_name.csv
 * #Cantidad de SnowFlakes
 * NUM_FLAKES	4
 * #Cantidad maxima de iteraciones
 * MAX_ITER	100000
 * #Algoritmo que se va a ejecutar, las opciones son:
 * #ClusterAndPickSolver = 0
 * #RestrictedHACSolver = 1
 * #RestrictedHACSpecificSolver = 2
 * #RandomBOBOSolver = 3
 * #RandomSOBOSolver = 4
 * #ExhaustiveGreedyAnySimSolver = 5
 * #ExhaustiveGreedySumSimSolver = 6
 * SOVLER	0
 */


#ifndef CONFIGURATIONJAKS_H
#define CONFIGURATIONJAKS_H

#include <map>
#include <string>

class ConfigurationJaks {
private:
	static char COMMENT;
	static std::string SEPARATOR;
	std::map<std::string, std::string> *keyValues_;
	void parseFile(char* fileName);
public:
    ConfigurationJaks(char* fileName);
    ~ConfigurationJaks();
    
    std::string giveMeValue(std::string key);
    std::string operator[](std::string key);
};

#endif // CONFIGURATIONJAKS_H
