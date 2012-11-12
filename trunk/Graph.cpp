#include "Graph.h"

#include <fstream>
using std::ifstream;

Grafo::Grafo()
{
	numV = 0;
	numA = 0;
	medGrau = 0.0;
}


Grafo::~Grafo()
{
}

void Grafo::makeGraph(string url, unsigned short int repr)
{	
	unsigned long v1, v2;		//Variables for connected vertices	ifstream file
	ifstream file;

	//Opening and reading file
	file.open(url);

	//Read first line with number of vertices
	file >> numV;
	adjMatrix = new vector<bool> (numV*numV,false)
	while (!file.eof())
	{
		file >> v1 >> v2;
		numA++;
		
		if (repr == 1)
		//Store on adjecency matrix
		{
			//Access value in matrix: adjMatrix (i*size + j)
			adjMatrix.at(v1*numV+v2) = 1;

			
		} else
		//Store on adjecency list
		{
			
		}
	}

}

