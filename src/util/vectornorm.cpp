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

#include "vectornorm.h"

double dotProductOf(IntVector* vector1, IntVector* vector2){
	double product = 0.0;
	int size = vector1->size();
	for (unsigned i=0; i<size; i++){
		product += (*vector1)[i] * (*vector2)[i];
	}

	return product;
}

double angleBetweenVectors(IntVector* vector1, IntVector* vector2){
	double norm1 = normOf(vector1);
	double norm2 = normOf(vector2);
	double dotProduct = dotProductOf(vector1, vector2);

	return dotProduct * (norm1 / norm2);
}

double normOf(IntVector* vector){
	double norm = 0.0;
	for (IntVector::iterator it = vector->begin(); it != vector->end(); ++it) {
		norm += std::pow(*it,2);
	}

	return std::sqrt(norm);
}