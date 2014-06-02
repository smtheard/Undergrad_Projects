#ifndef GRAPH_H
#define GRAPH_H

#include <string>
#include "EdgeNode.h"

using namespace std;

class Graph
{
	public:
		int vertexCount;
		string graphName;
		EdgeNode* adj_matrix [128][128]; //adjacency matrix representation
		char nodeNames[128];

		Graph(int vertexCount, string filename); //default constructor with one argument 
												 //that is the vertex count
		void createEdge(int i, int j);
		void removeEdge(int i, int j);
		bool edgeExists(int i, int j);
		int findNode(char ch);

		void generateGraph(string filename);
		void generateMatrixLabels();

		void insertToTable(char ch);
		void displayGraph(); //function for testing program
};		
#endif