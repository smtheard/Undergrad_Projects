#include <iostream>
#include <iomanip>
#include <fstream>
#include <cctype>
#include <string>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <cstring>
#include "global.h"

using namespace std;

class Node
{
	public:
		Node *previous, *next;
		string word;
		char ch;
		int count;
		Node();
};

class LinkedList
{
	public:
		Node *head;
		
		LinkedList(); //default constructor
		int initialize(string filename); //initializes list returns -1 if invalid filename
		int writeForward(Node* thenode, ofstream& fout); //writes the list out to filename  recursively
		int writeReverse(Node* thenode, ofstream& fout); // writes the list out to filename in reverse order recursively
		string tolowercase(string str);
		void addWord(string theword, int thecount);
		//void addChar(char c);
		void alphabetize();
		void increaseCount(string theword, int thecount);
		bool doesWordExist(Node *thenode, string theword); //this is for the recursive version
		bool doesWordExist(string theword);
		void error(string error_message); //creates a generic error message
		void output();
		//void output_char();
		void log_data_size(string operation_name); //calculates the size of the data in bytes that the list is occupying
		void armageddon(string listID); //destroys and frees all memory from the list
		string find_location(string str); // finds the location where str should go alphabetically and returns the string held in the node before it
		int insert(string old_word, string new_word); //inserts new word at the position after old word
		int del(string word); //deletes word from the list
};

 Node::Node()
 {
	word = "";
	previous = NULL;
	next = NULL;
	ch = '\0';
	count = 1;
 }
 
 LinkedList::LinkedList()
 {
	head = NULL;
 }
 
/*  void LinkedList::addChar(char c)
 {
	if(head == NULL)
	{
		head = new Node();
		head->ch = c;
		return;
	}
	else
	{
		Node *current = head;
		while(current->next != NULL) //move pointer to the last node in the list
			current = current->next;
		
		current->next = new Node();
		current->next->ch = c;
		current->next->previous = current;
	}
 } 
 
 void LinkedList::output_char()
 {
	if(head == NULL)
		return;
	
	Node *current = head;
	while(current != NULL)
	{
		cout << current->ch <<" ";
		current = current->next;
	}
	cout << endl;
 }*/
 
string LinkedList::tolowercase(string str)
 {
	char c;
	for(unsigned int i = 0; i<str.length(); i++)
	{
		c = str.at(i);
		str.at(i) = tolower(c);
	}
	return str;
 }
 
 void LinkedList::alphabetize() //bubble sort for alphabetical ordering
 {
	Node *current = head;
	Node *current2 = head;
	Node *temp, *temp2, *temp3, *temp4;
	time_actual += 8;
	while(current != NULL)
	{
		time_actual += 1;
		while(current2 != NULL)
		{ 
			time_actual += 1;
			if(current2->next == NULL)
			{
				time_actual += 1;
				break;
			}
			if(strcmp(current2->word.c_str(), current2->next->word.c_str()) == 0)//if the words are identical, delete the second one and increase the count of the first then continue at the next node
			{
				time_actual += 1;
					if(current2->next->next != NULL) 
					{
						current2->count = current2->count + current2->next->count; //increase count of current2's word
						temp = current2->next;
						temp2 = current2->next->next;
						
						//now remove current2->next..
						current2->next = temp->next;
						temp2->previous = current2;
						
						time_actual += 6;
					}
					else //operation for special case of current2->next being the last node in list
					{
						temp = current2->next;
						
						current2->count = current2->count + current2->next->count;
						current2->next = NULL;
						
						temp->previous = NULL;
						delete temp;
						time_actual += 6;
						
					}
			}
			else if(strcmp(current2->word.c_str(), current2->next->word.c_str()) > 0)
			{
				
				time_actual += 2;
				if(current2->previous != NULL)
				{
					if(current2->next->next != NULL)
					{
						temp = current2->previous;
						temp2 = current2;
						temp3 = current2->next;
						temp4 = current2->next->next;
							
						temp4->previous = current2;

						current2->previous = temp3;
						current2->next = temp4;
						
						temp3->next = temp2;
						temp3->previous = temp;
						temp->next = temp3;
						time_actual += 11;
					}
					else //operation for special case of current2->next being the last node in list
					{
						temp = current2->previous;
						temp2 = current2;
						temp3 = current2->next;

						temp->next = temp3;
						temp3->next = temp2;
						temp3->previous = temp;
						current2->previous = temp3;
						current2->next = NULL;
						time_actual += 9;
						continue;
					}
				}
				else //operation for special case of first node in list
				{
					if(current2->next->next != NULL) // if there are at least 3 nodes in the list total
					{
						temp = current2;
						temp2 = current2->next;
						temp3 = current2->next->next;
						
						temp2->previous = NULL;
						temp2->next = temp;
						
						current2->previous = temp2;
						current2->next = temp3;
						
						temp3->previous = temp;
						head = temp2; //updates the lists head to the new head
						time_actual += 10;
					}
					else // if there are only the first node and the second node
					{
						temp = current2;
						temp2 = current2->next;
						
						current2->next = NULL;
						current2->previous = temp2;
						
						temp2->next = temp;
						temp2->previous = NULL;
						time_actual += 7;
					}
				}
				
			}
			current2 = current2->next;
			time_actual += 1;
		}
		current2 = head;
		current = current->next;
		time_actual += 3;
	}
 }         //time complexity tracing : (n*(8*n))+ 9;     //n is the outer loop (n*8) is the inner loop

int LinkedList::initialize(string filename)//this function initializes our list with data from the given input file // working as intended //
 {												
	ifstream fin;
	fin.open(filename.c_str());
	if(fin.fail())
	{
		return -1;
	}
 
	string temp_str, track, templine;
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
			current->word = tolowercase(temp); //stores data in current node
			temp = strtok(NULL, " \n"); // grabs the next word from the getline
			
			current->next = new Node(); //creates a new link
			current->next->previous = current; //sets the new links prev to the current node (the link backward)
			current = current->next; //moves to the newly created next node
		}
	}

	log_data_size("after initialization");
	fin.close();
	return 0; 
 }
 
 int LinkedList::writeForward(Node* thenode, ofstream& fout)
 {
	if(thenode == NULL)
		return 99;
	fout << thenode->word << " " << thenode->count << endl;
	writeForward(thenode->next, fout);
	return 99;
 }
 
int LinkedList::writeReverse(Node* thenode, ofstream& fout)
 {
	if(thenode == NULL)
		return 99;
	writeReverse(thenode->next, fout);
	fout << thenode->word << " " << thenode->count << endl;
	return 99;
 }
 
int LinkedList::insert(string old_word, string new_word) // modify for the insert at head, and insert at end of tail cases
{
	Node *current = head;
	Node *newNode = new Node();
	Node *temp, *temp_curr;
	newNode->word = new_word;
	
	while(current != NULL)
	{
		if(current->word == old_word) //inserts newNode after current and before temp, which is the 'next' node after current
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
 int LinkedList::del(string word) // deletes 'word' from the list, checks for end of list and start of list pointers
 {
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
	//log_data_size("after deletion");
	return 99;
 }
 
 void LinkedList::log_data_size(string operation_name)
 {
	int total_size = 0;
	ofstream fout;
	Node *current = NULL;
	if(head != NULL)
		current = head;
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
 
 void LinkedList::armageddon(string listID) //first outputs the current size of the memory the list is occupying
 {								//and then deletes everything and outputs how much it is occupying after deletion
	log_data_size("before delete all in " + listID);
	Node *current = head;
	Node *temp;
	while(current != NULL)
	{
		temp = current; 
		current = current->next;
		if(temp->previous != NULL)
			temp->previous = NULL;
		if(temp->next != NULL)
			temp->next = NULL;
		if(temp != NULL)
			delete temp;
	}
	// if(head != NULL) this causes the program to crash because of calling delete twice only in certain circumstances, TODO: figure it out
	// {
		// delete head;
	// }
	head = NULL;
	log_data_size("after delete all in " + listID);
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
 
 void LinkedList::output() //function for testing, making sure that list has the correct words and count
 {
	Node *current;
	current = head;
	while(current != NULL)
	{
		cout << current->word <<" " << current->count << endl;
		current = current->next;
	}
	cout << endl;
	return;
 }
 
 bool LinkedList::doesWordExist(string theword) //iterative search definition.. recursive is below
 {
	Node* current = head;
	time_actual++;
	
	while(current != NULL)
	{
		if(current->word == theword)
		{
			time_actual+=2;
			return true;
		}
		current = current->next;
		time_actual += 2;
	}
	
	return false;
 } 
 
 // recursive version of doesWordExist ::
 
 bool LinkedList::doesWordExist(Node *thenode, string theword) //recursive search definition that returns true if theword is in the list, false otherwise
 {
	if(thenode == NULL)
		return false;
	if(thenode->word == theword)
		return true;
	else
		return doesWordExist(thenode->next, theword);
 }
 
 void LinkedList::addWord(string theword, int thecount)
 {
	Node* current;
	current = head;
	time_actual += 2;
	if(head != NULL) //this if statement makes sure that the list is not empty and the head is not NULL
	{
		time_actual++;
		while(current->next != NULL)
		{
			current = current->next; // moves pointer to the end of the list unless the head is NULL
			time_actual+=2;
		}
		current->next = new Node(); //creates a new node at the end of the list
		current->next->previous = current; //sets the *previous in the newly created node, to the current node
		current = current->next; //moves to the newly created node
		current->word = theword; // sets the word data to theword
		current->count = thecount; // sets the word equal to the count that it occurs in the original list
		time_actual += 5;
	}
	else // if the head is NULL, create a new node at that position and do the same thing as above and allocate data
	{
		head = new Node();
		head->word = theword;
		head->count = thecount;
		time_actual += 4;
	}
	return; // 2*n + 8
 }
 
 void LinkedList::increaseCount(string theword, int thecount)
 {
	Node* current;
	current = head;
	while(current != NULL)
	{
		if(current->word == theword)
		{
			current->count = current->count + thecount;
			return;
		}
	current = current->next;
	}
	return;
 }
 
 