#include <iostream>
#include <string>
#include <fstream>
#include "Graph.h"

using namespace std;

Graph::Graph(int vertexCount, string filename)
{
	this->vertexCount = vertexCount;
	graphName = filename;

	for(int i = 0; i < 128; i++) 
	{
		for (int j = 0; j < 128; j++)
			adj_matrix[i][j] = NULL;
		nodeNames[i] = '\0';
	}
	generateGraph(filename);
}

void Graph::createEdge(int i, int j)
{
	if (i >= 0 && i < vertexCount && j > 0 && j < vertexCount) 
	{
		adj_matrix[i][j]->value = 1;
		adj_matrix[j][i]->value = 1;
	}
}

void Graph::removeEdge(int i, int j)
{
	if (i >= 0 && i < vertexCount && j > 0 && j < vertexCount) 
	{
		adj_matrix[i][j] = 0;
		adj_matrix[j][i] = 0;
	}
}

bool Graph::edgeExists(int i, int j)
{
	if (i >= 0 && i < vertexCount && j > 0 && j < vertexCount)
		return true;
	else
		return false;
}

void Graph::displayGraph()
{
	cout << "Displaying Graph: " << graphName << endl;
	for (int i = 0; i < vertexCount; i++)
	{
		for (int j = 0; j < vertexCount; j++)
		{
			if (adj_matrix[i][j] != NULL)
				cout << adj_matrix[i][j]->value << "(" << adj_matrix[i][j]->x <<","<< adj_matrix[i][j]->y << ") ";
			else
				cout << "NULL";
		}
		cout << endl;
	}
	cout << endl;
}

void Graph::generateGraph(string filename)
{
	int temp2 = 0;
	ifstream fin;
	fin.open(filename.c_str());
	if (fin.fail())
	{
		cout << "Error with input file press enter a number to exit" << endl;
		cin >> temp2;
		exit(1);
	}
	string temp_str, templine;

	while (getline(fin, templine)) //triggers as long as there are lines in the file
	{								//inserting node names into table on first pass through the file
		//cout << "getline executed" << endl;
		insertToTable(templine.at(0)); 
		insertToTable(templine.at(4));
	}

	/*cout << "in nodeNames: " << endl;
	for (int i = 0; i < vertexCount; i++)
	{
		cout << nodeNames[i] << " ";
	}*/
	//cout << endl;
	generateMatrixLabels(); //generating the matrix with all x and y values attached for constant time location
	fin.close();
	fin.open(filename.c_str()); //reopen file to start from the beginning
	if (fin.fail())
	{
		cout << "Error with input file press enter a number to exit" << endl;
		cin >> temp2;
		exit(1);
	}

	while (getline(fin, templine)) //triggers as long as there are lines in the file
	{
		int hash1 = -1, hash2 = -1;
		hash1 = findNode(templine.at(0));
		hash2 = findNode(templine.at(4));
		createEdge(hash1, hash2);
	}
	fin.close();
}

int Graph::findNode(char ch)
{
	for (int i = 0; i < vertexCount; i++)
	{
		if (nodeNames[i] == ch)
			return i;
	}
	return -1;
}

void Graph::insertToTable(char ch)
{
	for (int i = 0; i < vertexCount; i++)
	{
		if (nodeNames[i] == ch)
			return;
		if (nodeNames[i] == '\0')
		{
			nodeNames[i] = ch;
			return;
		}
	}
	return;
}

void Graph::generateMatrixLabels()
{
	for (int i = 0; i < vertexCount; i++)
	{
		for (int j = 0; j < vertexCount; j++)
		{
			if (adj_matrix[i][j] == NULL)
				adj_matrix[i][j] = new EdgeNode(nodeNames[i], nodeNames[j], 0);
		}
	}
}