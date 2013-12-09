/*
 * <one line to give the program's name and a brief idea of what it does.>
 * Copyright (C) 2013  Juan <email>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 * 
 */

#ifndef VECTORNORM_H
#define VECTORNORM_H

#include <string>
#include <cmath>
#include "redefinitions.h"

float normOf(std::vector<float>* vector);
float dotProductOf(std::vector<float>* vector1, std::vector<float>* vector2);
float angleBetweenVectors(std::vector<float>* vector1, std::vector<float>* vector2);
void insertSimilarity();
int indexOf(String key);

#endif // VECTORNORM_H
