#include <iostream>
#include <iomanip>
#include <fstream>
#include <cctype>
#include <string>
#include <stdio.h>
#include <string.h>
#include <cstring>
#include "ScriptParser.cpp"
#include "CommandLineParser.cpp"

using namespace std;

class Node
{
	public:
		Node *previous, *next;
		string word;
		Node();
};

class LinkedList
{
	public:
		Node *head;
		string listID;
		
		LinkedList(); //default constructor
		int initialize(string listID, string filename); //initializes list returns -1 if invalid filename
		int writeForward(string listID, string filename); //writes the list out to filename 
		int writeReverse(string listID, string filename); // writes the list out to filename in reverse order
		int insert(string listID, string old_word, string new_word); //inserts new word at the position after old word
		int del(string listID, string word); //deletes word from the list
		void log_data_size(string operation_name); //calculates the size of the data in bytes that the list is occupying
		void armageddon(); //destroys and frees all memory from the list
		void error(string error_message); //generic output for error messages to log file
		bool hasEndLine(string word); // augmentative function that checks a string for an end of line character
		string cleaned(string str);
};

int main(int argc, char *argv[])
{
	LinkedList list;
	if ( argc != 2 )
	{
		list.error("No file input or too many arguments, please try again");
		return -1;
	} 
	CommandLineParser cmdparse(argv[1], ';');
	
	int track = 0;
	char *filename = cmdparse.extract("script");
	string line;
	ScriptParser scriptparse =  ScriptParser();
	ifstream fin(filename);
	string fn = filename;
	if(fin.fail())
	{
		list.error("Failure to open script file "+fn+" exiting program...");
		return -1;
	}
	list.error("||||||||||||| Start log for script file "+fn+" |||||||||||||");
	while(getline( fin, line )) 
	{
		scriptparse.ParseLine(line);
		switch (scriptparse.operationCode())
		{
		case 1:
			track = list.insert(scriptparse.cmd.listID, scriptparse.cmd.value1, scriptparse.cmd.value2); //inserts value 2 into the list after position value 1 is at
			break;
		case 2:
			track = list.del(scriptparse.cmd.listID, scriptparse.cmd.value1); //deletes the word that is stored in value1
			break;
		case 3:
			track = list.initialize(scriptparse.cmd.listID, scriptparse.cmd.value1); // reads file into list
			break;
		case 4:
			track = list.writeForward(scriptparse.cmd.listID, scriptparse.cmd.value1); //outputs file to specified output file
			break;
		case 5:
			track = list.writeReverse(scriptparse.cmd.listID, scriptparse.cmd.value1); //outputs file to specified output file in reverse order
			break;
		case 0:
			list.error("Operation not recognized, check your script file for errors! Exiting program...");
			track = -2;
			break;
		  }
	
		if(track == -1 || track == -2 || track == -3)
			break;
    }
	
	if(track == -1)
	{
		list.error("failed to initialize list due to invalid input file name");
	}
	if(track == -3)
	{
		list.error("Either the list was not initiated before performing operations, OR the most recent list ID did not match the initial list ID... Program forced to exit");
	}
	list.armageddon();
	list.error("||||||||||||| End log for script file "+fn+" |||||||||||||");
	return 0;
}
 
 Node::Node()
 {
	word = "";
	previous = NULL;
	next = NULL;
 }
 
 LinkedList::LinkedList()
 {
	head = NULL;
	listID = "";
 }
 
 bool LinkedList::hasEndLine(string word)
 {
	for(unsigned int i = 0; i<word.size(); i++)
		{
			if(word.at(i) == '\n')
				return true;
		}
	return false;
 }
 
 string LinkedList::cleaned(string str)
 {
	for(unsigned int i = 0; i<str.size(); i++)
		{
			if(str.at(i) == '\n')
				str.at(i) = ' ';
		}
	return str;
 }
 
int LinkedList::initialize(string listID, string filename)
 {												//this function initializes our list with data from the given input file
	this->listID = listID;
	ifstream fin;
	fin.open(filename.c_str());
	if(fin.fail())
	{
		return -1;
	}
 
	string templine;
	char* temp;
	char* buffer;
	head = new Node();
	Node *current = head;
	
	while(getline(fin, templine)) //triggers as long as there are words in the file
	{
		buffer = strdup(templine.c_str());
		temp = strtok(buffer, " ");
		while(temp != NULL)
		{
			current->word = temp; //stores data in current node
			current->next = new Node(); //creates a new link
			current->next->previous = current; //sets the new links prev to the current node (the link backward)
			current = current->next; //moves to the newly created next node
			temp = strtok(NULL, " "); // grabs the next word from the getline
		}
		//if(!fin.eof()) // checks if end of file is triggered, if not it adds a carriage return into the list
		//{
		
		//Below is for adding carriage returns to the word before they actually occur, and also to the word before the <eof>
			current = current->previous; // moves back one node
			current->word = current->word+'\n'; //adds carriage return to the last word on the line
			current->next = new Node(); //creates a new link
			current->next->previous = current; //sets the new links prev to the current node (the link backward)
			current = current->next;
		
			// below here is all for storing carriage returns in their own node
			//current->word = "\n"; //stores data in current node
			//current->next = new Node(); //creates a new link
			//current->next->previous = current; //sets the new links prev to the current node (the link backward)
			//current = current->next; //moves to the newly created next node
		//}
	}
	log_data_size("after initialization");
	fin.close();
	return 0; 
 }

 int LinkedList::writeForward(string listID, string filename)  //currently working order, remove if edits occur
 {
	if(this->listID != listID || this->listID == "")
		return -3;
	ofstream fout;
	fout.open(filename.c_str());
	if(fout.fail())
	{
		error(filename+" has failed to open for writeForward function");
		return 0;
	}
	
	Node *temp = head;
	while(temp != NULL)
	{
		fout << temp->word;
		if(!hasEndLine(temp->word))
		{
			if(temp->next != NULL)
			{
				//if(!hasEndLine(temp->next->word))
					fout << " ";
			}
		}
		temp = temp->next;
	}
	
	fout.close();
	return 99;
 }
 
int LinkedList::writeReverse(string listID, string filename)  //currently working order, remove if edits occur
 {
	if(this->listID != listID || this->listID == "")
		return -3;
	ofstream fout;
	fout.open(filename.c_str());
	if(fout.fail())
	{
		error(filename+" has failed to open for writeReverse function");
		return 0;
	}
	
	Node *temp = head;
	while(temp->next != NULL)		//moves temp pointer to the end of the tail
		temp = temp->next;
		
	while(temp != NULL)		//starts at the tail and works it way backward outputting each word in reverse
	{
		if(hasEndLine(temp->word))
			fout << cleaned(temp->word); // if a word has an end line clean it (take out the end line) and output that word instead
		else
			fout << temp->word;
		if(!hasEndLine(temp->word))
		{
			if(temp->previous != NULL && temp->next != NULL)
			{
				if(!hasEndLine(temp->previous->word))
						fout << " ";
			}
		}
		temp = temp->previous;
	}
	
	fout.close();
	return 99;
 }
 
int LinkedList::insert(string listID, string old_word, string new_word) // modify for the insert at head, and insert at end of tail cases
{
	if(this->listID != listID || this->listID == "")
		return -3;
	Node *current = head;
	Node *newNode = new Node();
	Node *temp, *temp_curr;
	newNode->word = new_word;
	
	while(current != NULL)
	{
		if(current->word == old_word || current->word == old_word+'\n') //inserts newNode after current and before temp, which is the 'next' node after current
		{
			if(current->next != NULL)
			{
				temp = current->next;
				newNode->previous = current;
				newNode->next = temp;
				temp->previous = newNode;
				current->next = newNode;
				break;
			}
			newNode->previous = current;
			newNode->next = NULL;
			current->next = newNode;
			break;
			
		}
		current = current->next;
	}
	log_data_size("after insertion");
	return 99;
}

 int LinkedList::del(string listID, string word) // deletes 'word' from the list, checks for end of list and start of list pointers
 {
	if(this->listID != listID || this->listID == "")
		return -3;
	
	Node *current = head;
	Node *temp;
	
	while(current != NULL)
	{
		if(current->word == word)
		{
			if(current->previous != NULL)
			{
				if(current->next != NULL)
				{
					current->previous->next = current->next;
					current->next->previous = current->previous;
					delete current;
					break;
				}
				
				current->previous->next = NULL;
				delete current;
				break;
			}
			delete current;
			break;
		}
		current = current->next;
	}
	log_data_size("after deletion");
	return 99;
 }
 
 void LinkedList::log_data_size(string operation_name)
 {
	int total_size = 0;
	ofstream fout;
	Node *current = head;
	fout.open("log.txt", ios::out | ios::app);
	while(current != NULL)
	{
		total_size = total_size + sizeof(current);
		current = current->next;
	}
	fout << "Size in memory " << operation_name << " " << total_size << endl;
	fout.close();
	return;
 }
 
 void LinkedList::armageddon() //first outputs the current size of the memory the list is occupying
 {								//and then deletes everything and outputs how much it is occupying after deletion
	log_data_size("before delete all");
	
	Node *current = head;
	Node *temp;
	while(current != NULL)
	{
		temp = current;
		current = current->next;
		if(temp->previous)
			temp->previous = NULL;
		if(temp->next)
			temp->next = NULL;
		delete temp;
	}
	
	log_data_size("after delete all");
	return;
 }
 
 void LinkedList::error(string error_message)
 {
	ofstream fout;
	fout.open("log.txt", ios::out | ios::app);
	fout << error_message << endl;
	fout.close();
	return;
 }