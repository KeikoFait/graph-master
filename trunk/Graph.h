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
	bool outputInfo();
	void BFS(unsigned long long root);
	void DFS(unsigned long long root);
	void conComp();
	~Graph();

private:
	//File read and output attributes
	unsigned short int reprStruct;
	unsigned long long numV;
	unsigned long long numA;

	//Graph representation attributes
	vector <bool>* adjMatrix;
	vector <vector<unsigned long long> >* adjList;

	
	//Methods to get the neighbours of a vertice
	vector<unsigned long long>* getNeighboursList(unsigned long long v);
	vector<unsigned long long>* getNeighboursMatrix(unsigned long long v);

	//Method to get coordinates in vector for adjacency matrix
	unsigned long long getPos(unsigned long long* x, unsigned long long* y);

	//Method to get the vetices empyrical distribution of degrees and their average degree
	double degreeInfoList(vector <vector<unsigned long long> >* aList, vector<unsigned long long>* distEmp);
	double degreeInfoMatrix(vector <bool>* aMatrix, vector<unsigned long long>* distEmp);

	//Methods to print graph on screen
	void printVector(vector<unsigned long long>* v);
	void printMatrix();
	void printList();
};

