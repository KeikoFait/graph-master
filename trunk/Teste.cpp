#include <iostream>
#include <vector>
#include <list>
using namespace std;

bool * getArray();
void printVector(vector<int>* v);

int main()
{
	vector <int>* v;
	vector <int> grau;
	int size = 4;
	v = new vector<int> (size*size, 0);
	v->at(1*4 + 0) = 1;
	grau.resize(4);
	grau.at(2) = 5;
	printVector(&grau);
	grau.resize(5);
	printVector(&grau);
}

void printVector(vector<int>* v)
{
	for(int i=0; i<v->size();i++)
	{
		if (i%v->size() == 0)
		{
			cout << endl;
		}
		cout << v->at(i) << " ";
	}
	cout << "\n\n";
	cin.ignore();
}

bool * getArray(){
	bool * array = new bool[10];
	for (int i = 0; i < 10; i++)
	{
		if (i % 2 == 0){
			array[i] = false;
		} else {
			array[i] = true;
		}
	}
	cout << array[1];
	return array;
}