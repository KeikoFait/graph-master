#include "Graph.h"

#include <fstream>
#include <iostream>
#include <iomanip>
#include <vector>
#include <deque>

using namespace std;

Graph::Graph()
{
	numV = 0;
	numA = 0;
}


Graph::~Graph()
{
	delete adjMatrix;
	delete adjList;
}

bool Graph::makeGraph(string url, short int repr)
{	
	//Variables for connected vertices
	unsigned long long v1;
	unsigned long long v2;
	ifstream file;
	reprStruct = repr;

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

	if (reprStruct == 1)
	//Represent graph as an adjacency matrix
	{
		adjMatrix = new vector<bool> (numV*numV, false);
		while (!file.eof())
		{
			file >> v1 >> v2;
			numA++;
			adjMatrix->at( getPos( &v1, &v2) ) = true;
			adjMatrix->at( getPos( &v2, &v1) ) = true;
		}
	} 
	else
	//Represent graph as an adjacency list
	{
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
	return true;
}

bool Graph::outputInfo()
{
	ofstream file;

	//Opening file for write
	file.open("graphInfo.txt");
	if (!file.is_open())
	{
		cerr << "Error while opening file!" << endl;
		cin.ignore();
		return false;
	}
	//Writing number of vertices and edges to file
	file << "n = " << numV << endl;
	file << "m = " << numA << endl;
	
	vector<unsigned long long> distEmp; // Will store the empirical distribution of degrees

	if (reprStruct == 1)
	{
		//Output degree information to file if adjacency matrix structure is utilized
		file << "d_medio = " << fixed << setprecision(1) << degreeInfoMatrix(adjMatrix, &distEmp) << endl;
 		for (unsigned long long i = 0; i < distEmp.size(); i++)
 		{
 			file << i << " " << fixed << setprecision(2) << (double)distEmp.at(i)/numV << endl;
 		}
	} else
	{	
		//Output degree information to file if adjacency list structure is utilized
		file << "d_medio = " << fixed << setprecision(1) << degreeInfoList(adjList, &distEmp) << endl;
 		for (unsigned long long i = 0; i < distEmp.size(); i++)
 		{
 			file << i << " " << fixed << setprecision(2) << (double)distEmp.at(i)/numV << endl;
 		}
	}
	file.close();
	return true;
}

double Graph::degreeInfoList(vector<vector<unsigned long long> >* aList, vector<unsigned long long>* distEmp)
{
	double med = 0;
	for(unsigned long long i = 0; i < aList->size(); i++)
	{
		med += aList->at(i).size();
		if (aList->at(i).size() > distEmp->size()) 
			distEmp->resize(aList->at(i).size() + 1);
		distEmp->at(aList->at(i).size()) +=  1;
	}
	med /= aList->size();
	return med;	
}

double Graph::degreeInfoMatrix(vector<bool>* aMatrix, vector<unsigned long long>* distEmp)
{
	double med = 0;
	unsigned long long degree = 0;
	for (unsigned long long i = 0; i < aMatrix->size(); i++)
	{
		if (aMatrix->at(i) == true)
			degree++;
		if ((i + 1) % numV == 0)
		{
			med += degree;
			if (degree > distEmp->size())
				distEmp->resize(degree + 1);
			distEmp->at(degree) +=  1;
			degree = 0;
		}
	}
	med /= numV;
	return med;
}

void Graph::searchGraph(unsigned long long root, short int searchMethod)
{
	vector<unsigned long long> discoverVert(numV, 0);		//Store for each vertex its component
	vector< vector<unsigned long long>> components; //Store the discovered vertices and which component it belongs
	unsigned long long compNum = 0;
	bool moreComp = true;
	ofstream searchFile, compFile;

	//Opening file
	searchFile.open("searchInfo.txt");
	compFile.open("componentsInfo.txt");

	while (moreComp == true)
	{
		compNum++;
		components.resize(compNum);
		if (searchMethod == 1)
			//BFS
			root = BFS(root, searchFile, &compNum, &moreComp, &discoverVert, &components);
		else
			//DFS
			root = DFS(root, searchFile, &compNum, &moreComp, &discoverVert, &components);
	}

	//Writing components information to file
	compFile << "Number of components: " << compNum << "\n" << endl;

	searchFile.close();
	compFile.close();
}

unsigned long long Graph::BFS(unsigned long long root, ofstream& file, unsigned long long* compNum, bool* moreComp, vector<unsigned long long>* discoverVert, vector< vector<unsigned long long>>* components)
{
	unsigned long long v, i;
	deque<unsigned long long> q;
	vector<unsigned long long>* neighbours;

	//Store the parent for each vertex
	vector<unsigned long long> parents(numV);
	file << "Component " << (*compNum) << "\n" << endl;
	file << "Search Tree:" << endl;

	//Will store the component for each vertex
	vector<unsigned long long> levels(numV);

	//Initial setup with root vertex
	discoverVert->at(root-1) = (*compNum);
	q.push_back(root);

	//Levels setup
	unsigned long long currentLevel = 0;
	unsigned long long levelSize = 1;
	unsigned long long nlevelSize = 0;
	levels.at(root) = currentLevel;

	while (!q.empty())
	{
		v = q.front();
		q.pop_front();

		//Select which neighbour function call, adjMatrix ou adjList one
		if (reprStruct == 2)
			neighbours = getNeighboursList(v);
		else
			neighbours = getNeighboursMatrix(v);

		file << v << " ";	//Store discovered element in the search tree on file 
		components->at((*compNum) - 1).push_back(v);	//Include the explorer vertex in it's component list

		for (i = 0; i < neighbours->size(); i++)
			//If vertex no discovered yet or if it's from another component
			if (discoverVert->at(neighbours->at(i)-1) < (*compNum))
			{
				//Mark vertex with actual component number, insert in queue
				discoverVert->at(neighbours->at(i)-1) = (*compNum);
				q.push_back(neighbours->at(i));
				//Storing parent node
				parents.at(neighbours->at(i) - 1) = v;
				//Storing level
				levels.at(neighbours->at(i) - 1) = currentLevel + 1;
				nlevelSize++;
			}
		//Level step setup
		levelSize--;
		if (levelSize == 0)
		{
			currentLevel++;
			levelSize = nlevelSize;
			nlevelSize = 0;
		}
	}
	
	//Writing parent and level for each vertex to file
	file << "\n\n" << left << setw(10) << "Vertex" << setw(10) << "Parent" << setw(10) << "Level" << endl;
	for (i = 0; i < numV; i++)
		if (discoverVert->at(i) == (*compNum))
			file << left << setw(10) << i + 1 << setw(10) << parents.at(i) << setw(10) << levels.at(i) << endl;
	file << "\n\n" << endl;

	//See if there are any unexplored components and return the first unknown vertex it found
 	for (i = 0; i < discoverVert->size(); i++)
 		if (discoverVert->at(i) == 0)
 			return i+1;
 	(*moreComp) = false;
	return 0;
}


unsigned long long Graph::DFS(unsigned long long root, ofstream& file, unsigned long long* compNum, bool* moreComp, vector<unsigned long long>* discoverVert, vector< vector<unsigned long long>>* components)
{
	unsigned long long v, i;
	deque<unsigned long long> q;
	vector<unsigned long long>* neighbours;

	//Store the parent for each vertex
	vector<unsigned long long> parents(numV);
	file << "Search Tree:" << endl;

	//Will store the component for each vertex
	vector<unsigned long long> levels(numV);

	//Initial setup with root vertex
	discoverVert->at(root-1) = (*compNum);
	q.push_back(root);

	//Levels setup
	unsigned long long currentLevel = 0;
	unsigned long long levelSize = 1;
	unsigned long long nlevelSize = 0;
	levels.at(root) = currentLevel;

	while (!q.empty())
	{
		v = q.back();
		q.pop_back();

		//Select which neighbour function call, adjMatrix ou adjList one
		if (reprStruct == 2)
			neighbours = getNeighboursList(v);
		else
			neighbours = getNeighboursMatrix(v);

		file << v << " ";	//Store discovered element in the search tree on file 
		components->at((*compNum) - 1).push_back(v);	//Include the explorer vertex in it's component list

		for (i = 0; i < neighbours->size(); i++)
			//If vertex no discovered yet or if it's from another component
			if (discoverVert->at(neighbours->at(i)-1) < (*compNum))
			{
				//Mark vertex with actual component number, insert in queue
				discoverVert->at(neighbours->at(i)-1) = (*compNum);
				q.push_back(neighbours->at(i));
				//Storing parent node
				parents.at(neighbours->at(i) - 1) = v;
				//Storing level
				levels.at(neighbours->at(i) - 1) = currentLevel + 1;
				nlevelSize++;
			}
			//Level step setup
			levelSize--;
			if (levelSize == 0)
			{
				currentLevel++;
				levelSize = nlevelSize;
				nlevelSize = 0;
			}
	}

	//Writing parent and level for each vertex to file
	file << "\n\n" << left << setw(10) << "Vertex" << setw(10) << "Parent" << setw(10) << "Level" << endl;
	for (i = 0; i < numV; i++)
		if (discoverVert->at(i) == (*compNum))
			file << left << setw(10) << i + 1 << setw(10) << parents.at(i) << setw(10) << levels.at(i) << endl;

	//See if there are any unexplored components and return the first unknown vertex it found
	for (i = 0; i < discoverVert->size(); i++)
		if (discoverVert->at(i) == 0)
			return i+1;
	(*moreComp) = false;
	return 0;
}


vector<unsigned long long>* Graph::getNeighboursList(unsigned long long v)
{
	return &(adjList->at(v-1));
}


vector<unsigned long long>* Graph::getNeighboursMatrix(unsigned long long v)
{
	vector<unsigned long long>* neighbours = new vector<unsigned long long>;
	for(unsigned long long i = 1; i < numV + 1; i++){
		if (adjMatrix->at(getPos(&v,&i)) == 1)
			neighbours->push_back(i);
	}
	return neighbours;
}


unsigned long long Graph::getPos(unsigned long long* x, unsigned long long* y)
{
	//Access value in matrix: adjMatrix (i*size + j); -1 because the vertices starts at 1 and indexes at 0
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

void Graph::printVector(vector<unsigned long long>* v)
{
	unsigned long long i;
	for (i = 0; i < v->size(); i++)
	{
		cout << v->at(i) << " ";
	}
	cout << "\n" << endl;
}

int main()
{
	cout << "rodou!" << endl;
	Graph* graph = new Graph();
	graph->makeGraph("teste_graph.txt", 2);
	//Output info about graph to a file
	graph->outputInfo();
	graph->searchGraph(1, 1);
	cin.ignore();

	return 0;
}