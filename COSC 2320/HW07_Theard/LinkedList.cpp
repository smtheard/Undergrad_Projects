#include <iostream>
#include <iomanip>
#include <fstream>
#include <cctype>
#include <string>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <cstring>

using namespace std;

class Node
{
	public:
		Node *previous, *next;
		string word, cleaned_word;
		int count, punc_count;
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
		void writeForwardIterative(ofstream& fout);
		void writeReverseIterative(ofstream& fout);
		string tolowercase(string str);
		string clean(string str);
		void addWord(string theword, string thecleanedword, int thecount, int thepunc_count);
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
		//LinkedList* operator=(const LinkedList rhs);
};

 Node::Node()
 {
	word = "";
	cleaned_word = "";
	previous = NULL;
	next = NULL;
	count = 1;
	punc_count = 0;
 }
 
 LinkedList::LinkedList()
 {
	head = NULL;
 }
 
 /*LinkedList* LinkedList::operator=(const LinkedList rhs)
 {
	cout << " linked list operator = used " << endl;
	LinkedList *building_list = new LinkedList;
	Node* current_rhs = rhs.head;
	while(current_rhs != NULL)
	{cout << " in while = word " << current_rhs->word << endl;
		if(building_list->head == NULL)
		{
			Node* newNode = new Node;
			newNode->word = current_rhs->word;
			newNode->cleaned_word = current_rhs->cleaned_word;
			newNode->count = current_rhs->count;
			newNode->punc_count = current_rhs->punc_count;
			building_list->head = newNode;
		}
		else
		{
			Node* temp = building_list->head;
			while(temp->next != NULL)
			{
				
				temp = temp->next;
			}
			temp->next = new Node;
			temp->next->word = current_rhs->word;
			temp->next->cleaned_word = current_rhs->cleaned_word;
			temp->next->count = current_rhs->count;
			temp->next->punc_count = current_rhs->punc_count;
		}
		current_rhs = current_rhs->next;
	}
	building_list->output();
	return building_list;
 }*/
 
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
 
 string LinkedList::clean(string str)
 {
	char c;
	for(unsigned int i = 0; i<str.length(); i++)
	{
		c = str.at(i);
		if(i == 0)
		{
			if(ispunct(c))
			{
				str.erase(0,1);
				//c = '\0';
				//str.at(i) = c;
				//node->punc_count++;
			}
			else
				str.at(i) = tolower(c);
		}
		else if( i == str.length()-1)
		{
			if(ispunct(c))
			{
				str.erase(str.length()-1,1);
			}
			else
				str.at(i) = tolower(c);
		}
		else if(!ispunct(c))
			str.at(i) = tolower(c);
	}
	return str;
 }
 
 void LinkedList::alphabetize() //bubble sort for alphabetical ordering
 {
	Node *current = head;
	Node *current2 = head;
	Node *temp, *temp2, *temp3, *temp4;

	while(current != NULL)
	{
		
		while(current2 != NULL)
		{ 
			
			if(current2->next == NULL)
			{
				
				break;
			}
			if(strcmp(current2->word.c_str(), current2->next->word.c_str()) == 0)//if the words are identical, delete the second one and increase the count of the first then continue at the next node
			{
					if(current2->next->next != NULL) 
					{
						current2->count = current2->count + current2->next->count; //increase count of current2's word
						temp = current2->next;
						temp2 = current2->next->next;
						
						//now remove current2->next..
						current2->next = temp->next;
						temp2->previous = current2;
					}
					else //operation for special case of current2->next being the last node in list
					{
						temp = current2->next;
						
						current2->count = current2->count + current2->next->count;
						current2->next = NULL;
						
						temp->previous = NULL;
						delete temp;
					}
			}
			else if(strcmp(current2->word.c_str(), current2->next->word.c_str()) > 0)
			{
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
					}
					else // if there are only the first node and the second node
					{
						temp = current2;
						temp2 = current2->next;
						
						current2->next = NULL;
						current2->previous = temp2;
						
						temp2->next = temp;
						temp2->previous = NULL;
					}
				}
				
			}
			current2 = current2->next;
		}
		current2 = head;
		current = current->next;
	}
	//special case for if there are two of a word, and one is at the beginning of the list, one is at the end
	if(head != NULL)
	{
		if(head->next != NULL)
		{
			if(head->word == head->next->word)
			{
				if(head->next->next != NULL)
				{
					head->count = head->count + head->next->count; //increase count of heads's word
					temp = head->next;
					temp2 = head->next->next;
							
					//now remove head->next..
					head->next = temp->next;
					temp2->previous = head;
				}
			}
		}
	}
 }

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
			//current->word = tolowercase(temp); //stores data in current node
			current->word = clean(temp);
			//current->cleaned_word = clean(temp, current); //stores cleaned data in current node (no punctuation)
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
 
 void LinkedList::writeForwardIterative(ofstream& fout)
 {
	if(head == NULL)
		return;
	
	Node* current = head;
	while(current != NULL)
	{
		for(unsigned int i = 0; i < (current->word.length() - current->punc_count); i++)
			fout<<current->word.at(i);
		//fout<<" "<<current->count;
		if(current->next != NULL)
			fout<<endl;
			
		current = current->next;
	}
 }
 
int LinkedList::writeReverse(Node* thenode, ofstream& fout)
 {
	if(thenode == NULL)
		return 99;
	writeReverse(thenode->next, fout);
	fout << thenode->word << " " << thenode->count << endl;
	return 99;
 }
 
 void LinkedList::writeReverseIterative(ofstream& fout)
 {
	if(head == NULL)
		return;
	
	Node* current = head;
	while(current->next != NULL)
		current = current->next;
	while(current != NULL)
	{
		for(unsigned int i = 0; i < (current->word.length() - current->punc_count); i++)
			fout<<current->word.at(i);
		//fout<<" "<<current->count<<endl;
		if(current->previous != NULL)
			fout<<endl;
		current = current->previous;
	}
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
		if(strcmp(current->word.c_str(),word.c_str()) == 0)
		{
			if(current->previous == NULL && current->next != NULL) //if current is head and there is more than 1 node in list
			{
				head = current->next;
				current->next->previous = NULL;
				delete current;
				return 99;
			}
			else if(current->next == NULL && current->previous != NULL)//else if current is tail
			{
				current->previous->next = NULL;
				delete current;
				return 99;
			}
			else if(current->previous == NULL && current->next == NULL)//else if the node is the only one in the list
			{
				head = NULL;
				delete current;
				return 99;
			}
			else
			{
				current->previous->next = current->next;
				current->next->previous = current->previous;
				delete current;
				return 99;
			}
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
	while(current != NULL)
	{	
		if(strcmp(current->word.c_str(),theword.c_str()) == 0)
			return true;
		current = current->next;
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
 
 void LinkedList::addWord(string theword, string thecleanedword, int thecount, int thepunc_count)
 {
	Node* current;
	current = head;

	if(head != NULL) //this if statement makes sure that the list is not empty and the head is not NULL
	{

		while(current->next != NULL)
		{
			current = current->next; // moves pointer to the end of the list unless the head is NULL
		}
		current->next = new Node(); //creates a new node at the end of the list
		current->next->previous = current; //sets the *previous in the newly created node, to the current node
		current = current->next; //moves to the newly created node
		current->word = theword; // sets the word data to theword
		current->cleaned_word = thecleanedword;
		current->count = thecount; // sets the word equal to the count that it occurs in the original list
		current->punc_count = thepunc_count;
	}
	else // if the head is NULL, create a new node at that position and do the same thing as above and allocate data
	{
		head = new Node();
		head->word = theword;
		head->cleaned_word = thecleanedword;
		head->count = thecount;
		head->punc_count = thepunc_count;
	}
	return; // 2*n + 8
 }
 
  void LinkedList::addWord(string theword, int thecount)
 {
	Node* current;
	current = head;

	if(head != NULL) //this if statement makes sure that the list is not empty and the head is not NULL
	{

		while(current->next != NULL)
		{
			current = current->next; // moves pointer to the end of the list unless the head is NULL
		}
		current->next = new Node(); //creates a new node at the end of the list
		current->next->previous = current; //sets the *previous in the newly created node, to the current node
		current = current->next; //moves to the newly created node
		current->word = theword; // sets the word data to theword
		current->count = thecount; // sets the word equal to the count that it occurs in the original list
	}
	else // if the head is NULL, create a new node at that position and do the same thing as above and allocate data
	{
		head = new Node();
		head->word = theword;
		head->count = thecount;
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
 
 