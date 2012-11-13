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
	bool outputInfo(unsigned short int repr);
	void BFS(unsigned long long root);
	void DFS(unsigned long long root);
	void conComp();
	~Graph();

private:
	//File read and output attributes
	unsigned long long numV;
	unsigned long long numA;

	//Graph representation attributes
	vector <bool>* adjMatrix;
	vector <vector<unsigned long long> >* adjList;


	//Method to get coordinates in vector for adjacency matrix
	unsigned long long getPos(unsigned long long* x, unsigned long long* y);

	//Methods to measure the average degree of the vertices
	double avgDegreeList(vector <vector<unsigned long long> >* aList);
	double avgDegreeMatrix(vector <bool>* aMatrix);

	//Method to get the vetices empyrical distribution of degrees
	vector<unsigned long long>* distEmpList(vector <vector<unsigned long long> >* aList);
	vector<unsigned long long>* distEmpMatrix(vector <bool>* aMatrix);

	//Methods to print graph on screen
	void printMatrix();
	void printList();
};

