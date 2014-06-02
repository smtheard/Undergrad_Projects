#include <iostream>
#include <string>
#include "Graph.h"
#include "EdgeNode.h"

using namespace std;

bool areIsomorphic(Graph g1, Graph g2);

int main(int argc, char *argv[])
{
	int vertecies_g1 = -1, vertecies_g2 = 0, exit = 0;
	string filename1 = "", filename2 = "";
	
	while (exit == 0)
	{
		cout << "How many vectors are in the graphs you wish to compare?" << endl
			 << "(keep in mind: graphs with non-equal vectors cannot be isomorphic)" << endl;
		cout << "Vertecies for graph V: ";
		cin >> vertecies_g1;
		cout << "Vertecies for graph H: ";
		cin >> vertecies_g2;
		cout << "File Name for graph V: ";
		cin >> filename1;
		cout << "File Name for graph H: ";
		cin >> filename2;

		if (vertecies_g1 != vertecies_g2)
			cout << " Verteces not equal therefore graphs are not isomorphic." << endl;
		else
		{
			Graph graph1(vertecies_g1, filename1), graph2(vertecies_g2, filename2);
			//graph1.displayGraph();
			//graph2.displayGraph();
			if (areIsomorphic(graph1, graph2))
				cout << "Graph V and H ARE isomorphic!" << endl;
			else
				cout << "Graph V and H are NOT isomorphic!" << endl;
		}
		
		cout << "enter 0 to try again, or 1 to exit" << endl;
		cin >> exit;
	}
	
	return 0;
}

bool areIsomorphic(Graph g1, Graph g2) // algorithm to determine isomorphism between two graphs g1 and g2.
{
	if (g1.vertexCount != g2.vertexCount)
		return false;

	int vertexCount = g1.vertexCount;

	for (int i = 0; i < vertexCount; i++)
	{
		for (int j = 0; j < vertexCount; j++)
		{
			if (g1.adj_matrix[i][j]->value != g2.adj_matrix[i][j]->value)
				return false;
		}
	}
	return true;
}