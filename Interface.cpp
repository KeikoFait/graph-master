#include <iostream>
using namespace std;

#include "Graph.h"

int main()
{
	//Variables initialization
	Graph graph = new Graph();

	//Validate graph making
	if (getGraphInfo(&graph) == false)
	{
		//Error
		cout << "Nome do arquivo ou opcao invalida, tente novamente...\n\n" << endl;
		getGraphInfo(&graph);
	}
	//Success
	cout << "Arquivo lido e grafo armazenado com sucesso!\n" << endl;

	//Menu with options
	selectMenu(&graph);

	return 0;
}

bool getGraphInfo(Graph* graph)
{
	string url;
	unsigned short int repr;

	//Obtaining graph file address
	cout << "Insira o nome do arquivo a ser analisado:" << endl;
	cin >> url;

	//Selecting how the graph is stored
	cout >> "\nInsira como deseja que o grafo seja representado:\n" <<
		"1) Matriz de adjacencia\n" <<
		"2) Lista de adjacencia\n" << endl;
	cin >> repr;

	cout >> "Informacoes sobre o grafo gravadas no arquivo \"graphInfo.txt\"\n" << endl;

	return graph->makeGraph(url, repr);
}

void selectMenu(Graph* graph)
{
	//Selecting one of the options for searching graph
	unsigned short int option;
	unsigned long root;
	cout << "Selecione uma das opcoes de busca:\n" << 
		"1) Busca em largura\n" <<
		"2) Busca em profundidade\n" <<
		"3) Sair do programa\n" << endl;
	cin >> option;

	switch(option)
	{
	case 1:
		//Use the BFS algorithm and obtain info from it
		cout << "Insira o vertice inicial da busca em largura:" << endl;
		cin >> root;
		graph->BFS(root);
		cout << "Busca em largura realizada! Informacoes sobre o grafo no arquivo \"bfs.txt\"\n" << endl;
		break;
	case 2:
		//Use the DFS algorithm and obtain info from it
		cout << "Insira o vertice inicial da busca em profundidade:" << endl;
		cin >> root;
		graph->BFS(root);
		cout << "Busca em profundidade realizada! Informacoes sobre o grafo no arquivo \"dfs.txt\"\n" << endl;
		break;
	case 3:
		//Exit program
		exit();
	default:
		cout << "Opcao invalida... Selecione 1,2 ou 3/n" << endl;
		selectMenu(graph);
	}

	//Connected components information
	cout << "Componentes conexos:" << endl;
	graph->ConComp();
}