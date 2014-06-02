#include <iostream>
#include <iomanip>
#include <cstring>
#include <fstream>
#include <cctype>
#include <string.h>
#include <stdio.h>

using namespace std;

class Node
{
	private:
		Node *previous, *next;
		string word;
	public:
		Node();
		Node(string initWord, Node* prev);
		Node(string initWord, Node* prev, Node* next);
};

class LinkedList
{
	private:
		Node *head;
	public:
		string separated_args[256];
		LinkedList(); //default constructor
};

class Parser
{
	private:
		char* argument; //stores the initial argument (non-separated)
		char* delimiter; //stores the delimiter;
	
	public:
		Parser(char* argument, char* delimiter); //contructor 2 parameters
		void parse_arguments(string separated_args[]);
};

int main(int argc, char *argv[])
{
	if ( argc != 2 )
	{
		cout << endl << "No file input or too many arguments!" << endl;
		cout << "This program supports exactly one argument with" << endl;
		return -1;
	} 
	
	LinkedList list;
	
	Parser parser(argv[1], ";");
	parser.parse_arguments(list.separated_args);
	

	return 0;
}

Parser::Parser(char* argument, char* delimiter)
 {
	this->argument = argument;
	this->delimiter = delimiter;
 }
 
void Parser::parse_arguments(string separated_args[])
 {
	for(int i = 0; i<256; i++)
		separated_args[i] = "\0";
	char *ptr;
	ptr = strtok(argument, delimiter);
	for(int i = 0; ptr != NULL; i++)
	{
		separated_args[i] = ptr;
		ptr = strtok(NULL, delimiter);
	}
 }
 
 Node::Node()
 {
	word = "";
	previous = NULL;
	next = NULL;
 }
 
 Node::Node(string initWord, Node* prev)
 {
	word = initWord;
	previous = prev;
	next = NULL;
 }
 
 Node::Node(string initWord, Node* prev, Node* next)
 {
	word = initWord;
	previous = prev;
	this->next = next;
 }
 
 LinkedList::LinkedList()
 {
	head = NULL;
 }
 
 