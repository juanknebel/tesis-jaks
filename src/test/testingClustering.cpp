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


#include <iostream>
#include "testingClustering.h"

TestingClustering::TestingClustering()
{
}

TestingClustering::~TestingClustering()
{
}

void TestingClustering::testCluster ( const MatrixWrapper& graph, int numClusters )
{
	IntVector* result = Clustering::cluster(graph, numClusters);

	for (int node = 0; node < result->size(); ++node) {
		std::cout<<"El nodo: "<<node<<" pertence a la particion: "<<(*result)[node]<<std::endl;
	}

	delete result;
}

void TestingClustering::testSymmetrizeCluster ( MatrixWrapper& graph, int numClusters )
{
	IntVector* result = Clustering::symmetrizeAndCluster(graph, numClusters);

	for (int node = 0; node < result->size(); ++node) {
		std::cout<<"El nodo: "<<node<<" pertence a la particion: "<<(*result)[node]<<std::endl;
	}

	delete result;
}
