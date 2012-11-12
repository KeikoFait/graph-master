#pragma once

#include <string>
using std::string;

#include <vector>
using std::vector;

#include <list>
using std::list;

class Graph
{
public:
	Graph();
	bool makeGraph(string url, unsigned short int repr);
	void outputInfo();
	void BFS(unsigned long root);
	void DFS(unsigned long root);
	void conComp();
	~Graph();

private:
	//File read and output attributes
	unsigned long numV;
	unsigned long numA;
	double medGrau;
	double* distEmp;

	//Graph representation attributes
	//Incializarei dentro das funcoes
	vector <bool>* adjMatrix;
	vector <list<unsigned long> >* adjList;
};

