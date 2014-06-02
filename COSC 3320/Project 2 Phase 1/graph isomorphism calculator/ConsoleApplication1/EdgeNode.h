#ifndef EDGENODE_H
#define EDGENODE_H

#include <iostream>
#include <string>

using namespace std;

class EdgeNode
{
	public:
		char x, y;
		int value;
		EdgeNode();
		EdgeNode(char x, char y);
		EdgeNode::EdgeNode(char x, char y, int value);
};

#endif