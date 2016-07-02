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


#include "configurationJaks.h"
#include <algorithm>
#include <fstream>
#include <vector>
#include <stdexcept>
#include "../system/stringUtilities.h"

char ConfigurationJaks::COMMENT = '#';
std::string ConfigurationJaks::SEPARATOR = "\t";

ConfigurationJaks::ConfigurationJaks(char* fileName)
{
	this->keyValues_ = new std::map<std::string, std::string>();
	this->parseFile(fileName);
}

ConfigurationJaks::~ConfigurationJaks()
{
	delete this->keyValues_;
}

std::string ConfigurationJaks::giveMeValue(std::string key)
{
	std::transform(key.begin(), key.end(),key.begin(), ::toupper);
	std::string result;

	try {
		result = this->keyValues_->at(key);
	}

	catch (const std::out_of_range& oor) {
		result = "Error: Clave no encontrada.";
	}

	return result;
}

std::string ConfigurationJaks::operator[](std::string key)
{
	return this->giveMeValue(key);
}

void ConfigurationJaks::parseFile(char* fileName)
{
	std::ifstream file;
	file.open(fileName);
	std::string line;

	while(getline(file, line, '\n')) {
		if (line[0] == ConfigurationJaks::COMMENT || line.empty()) {
			continue;
		}

		std::vector<std::string> tokens;
		stringToVectorSplit(line, ConfigurationJaks::SEPARATOR, tokens);
		std::string key = tokens[0];
		std::string value = tokens[1];
		trim(key);
		trim(value);
		std::transform(key.begin(), key.end(),key.begin(), ::toupper);
		(*(this->keyValues_))[key] = value;
	}

	file.close();
}
