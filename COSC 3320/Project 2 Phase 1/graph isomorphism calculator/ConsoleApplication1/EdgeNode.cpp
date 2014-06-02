#include "EdgeNode.h"

using namespace std;


EdgeNode::EdgeNode()
{
	x = '\0';
	y = '\0';
	value = 0;
}

EdgeNode::EdgeNode(char x, char y)
{
	this->x = x;
	this->y = y;
	value = 0;
}

EdgeNode::EdgeNode(char x, char y, int value)
{
	this->x = x;
	this->y = y;
	this->value = value;
}