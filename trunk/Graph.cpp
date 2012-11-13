#include "Graph.h"

#include <fstream>
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

Graph::Graph()
{
	numV = 0;
	numA = 0;
	//medGrau = 0.0;
}


Graph::~Graph()
{
	delete adjMatrix;
	delete adjList;
	//delete distEmp;
}

bool Graph::makeGraph(string url, unsigned short int repr)
{	
	unsigned long long v1;
	unsigned long long v2;		//Variables for connected vertices	ifstream file
	ifstream file;

	//Opening and reading file
	file.open(url);
	if (!file.is_open())
	{
		cout << "Error while opening file!" << endl;
		cin.ignore();
		return false;
	}

	//Read first line with number of vertices
	file >> numV;

	if (repr == 1)
	//Store on adjacency matrix
	{
		adjMatrix = new vector<bool> (numV*numV, false);
		while (!file.eof())
		{
			file >> v1 >> v2;
			numA++;
			adjMatrix->at( getPos( &v1, &v2) ) = true;
			adjMatrix->at( getPos( &v2, &v1) ) = true;
		}
	} else {
		adjList = new vector< vector<unsigned long long> >(numV, vector<unsigned long long>());
		while (!file.eof())
		{
			file >> v1 >> v2;
			numA++;
			adjList->at(v1-1).push_back(v2);
			adjList->at(v2-1).push_back(v1);
		}	
	}

	file.close();
	
	//Output info about graph to a file
	outputInfo(repr);

	return true;
}

bool Graph::outputInfo(unsigned short int repr)
{
	ofstream file;

	//Opening and reading file
	file.open("graphInfo.txt");
	if (!file.is_open())
	{
		cout << "Error while opening file!" << endl;
		cin.ignore();
		return false;
	}

	file << "n = " << numV << endl;
	file << "a = " << numA << endl;
	
	if (repr == 1)
	{
	} 
	else
	{
		vector<unsigned long long>* distEmp = distEmpList(adjList);
		
		file << "d_medio = " << avgDegreeList(adjList) << endl;
 		for (unsigned long long i = 0; i < distEmp->size(); i++)
 		{
 			file << i << " " << distEmp->at(i) << endl;
 		}
 		delete distEmp;
	}

	file.close();

	return true;
}

double Graph::avgDegreeList(vector<vector<unsigned long long> >* aList)
{
	double med = 0;
	for(int i = 0; i < aList->size(); i++){
		med += aList->at(i).size();
	}
	med /= aList->size();
	return med;
}

vector <unsigned long long>* Graph::distEmpList(vector <vector<unsigned long long> >* aList)
{
	vector<unsigned long long>* distEmp = new vector<unsigned long long>;

	for(int i = 0; i < aList->size(); i++){
		if (aList->at(i).size() > distEmp->size()) distEmp->resize(aList->at(i).size() + 1);
		distEmp->at(aList->at(i).size()) +=  1;
	}

	return distEmp;
}

unsigned long long Graph::getPos(unsigned long long* x, unsigned long long* y)
{
	//Access value in matrix: adjMatrix (i*size + j)
	return ((*x-1) * numV + (*y-1));
}

void Graph::printMatrix()
{
	for(int i=0; i<numV*numV;i++)
	{
		if (i%numV == 0)
		{
			cout << endl;
		}
		cout << adjMatrix->at(i) << " ";
	}
	cout << "\n\n";
	cin.ignore();
}

void Graph::printList()
{
	unsigned long long j;
	for (unsigned long long i=0; i < numV; i++)
	{
		cout << i+1 << "\t";
		for (j=0; j < adjList->at(i).size(); j++)
		{
			cout << (*adjList)[i][j] << " ";
		}
		cout << endl;
	}
}

int main()
{
	cout << "rodou!" << endl;
	Graph* graph = new Graph();
	graph->makeGraph("as_graph.txt", 2);
	cin.ignore();

	return 0;
}