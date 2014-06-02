#include <iostream>
#include <iomanip>
#include <fstream>
#include <cctype>
#include <string>
#include <stdio.h>
#include <string.h>
#include <cstring>
#include "LinkedList.cpp"

using namespace std;

class ListNode
{
	public:
		ListNode *previous, *next;
		string listID;
		LinkedList list;
		ListNode();
		ListNode(string newListID, string headData);
};

class ListContainer
{
	public:
		ListNode *head;
		ListContainer();
		
		//main functions
		int initialize(string listID, string filename); //initializes list under the listID returns -1 if invalid filename
		int union_initialize(string listname1, string listname2, string listname3, string op); //setting up the call to the recursive definition of union
		int intersect_initialize(string listname1, string listname2, string listname3, string op);//setting up the call to the recursive definition of intersection
		LinkedList union_func(Node* list1, Node* list2, LinkedList newList); // recursive definition of union
		LinkedList intersection_func(LinkedList list1, Node* list2, LinkedList newList); //recursive definition of intersection
		Node* union_func_iterative(Node* list1, Node* list2); // iterative definition of union (merging two sorted lists)
		LinkedList intersection_func_iterative(LinkedList list1, Node* list2, LinkedList newList); //iterative definition of intersection
		int writeForward(string listID, string filename, string op); //writes the list at listID out to filename 
		int writeReverse(string listID, string filename, string op); // writes the list at listID out to filename in reverse order
		
		//auxiliary functions
		string clean_file_name(string filename);
		ListNode *find_list(string listname); //finds the listcontainer at the location listID == listname
		void add_list(ListNode *thelist); // adds *thelist to the listcontainer in the first available spot
		void armageddon(); //destroys and frees all memory from all lists
		long ListContainer::getN(string listname); // gets number of nodes in list listname
		void error(string error_message); //generic output for error messages to log file
};

 ListNode::ListNode()
 {
	listID = "";
	previous = NULL;
	next = NULL;
 }
 
ListNode::ListNode(string newListID, string headData)
{
	listID = newListID;
	list.head = new Node;
	list.head->word = headData;
	previous = NULL;
	next = NULL;
}

ListContainer::ListContainer()
{
	head = NULL;
}
 
 void ListContainer::error(string error_message)
 {
	ofstream fout;
	fout.open("log.txt", ios::out | ios::app);
	fout << error_message << endl;
	fout.close();
	return;
 }
 
int ListContainer::initialize(string listID, string filename)
{
	if(find_list(listID) != NULL)
	{
		error("You are trying to overwrite an already existing list, this is illegal.. Skipping this operation. List: "+listID);
		return 99;
	}
	filename = clean_file_name(filename); //takes away single quotes from the filename
	if(head == NULL)
	{
		head = new ListNode();
		head->listID = listID;
		head->list.initialize(filename);
		if(head->list.head->word == "")
				head->list.head = NULL;
		head->list.del("");
		//head->list.alphabetize();
		//head->list.output();
		return 99;
	}
	ListNode *current = head;
	
	while(current != NULL)
	{
		if(current->next == NULL)
		{
			current->next = new ListNode();
			current->next->previous = current;
			current->next->listID = listID;
			current->next->list.initialize(filename);
			if(current->next->list.head->word == "")
				current->next->list.head = NULL;
			current->next->list.del(""); //deletes any empty words in list
			//current->next->list.alphabetize();
			//current->next->list.output();
			return 99;
		}
		current = current->next;
	}
	return -1;
}

void ListContainer::add_list(ListNode *thelist) //working as intended
{
	ListNode *current = head;
	while(current != NULL)
	{
		if(current->next == NULL)
		{
			current->next = thelist;
			current->next->previous = current;
			return;
		}
		current = current->next;
	}
}

int ListContainer::writeForward(string listID, string filename, string op)
{
	ofstream fout;
	filename = clean_file_name(filename); //takes away single quotes from the filename
	
	ListNode *current;
	current = find_list(listID); //finds the list in the list of lists, if it doesn't exist, return
	if(current == NULL)
	{
		fout.open(filename.c_str());
		if(fout.fail())
		{
			error(filename+" has failed to open for writeForward function");
			return 0;
		}
		fout << "List "+listID+" does not exist " << endl;
		fout.close();
		return -3;
	}
	
	fout.open(filename.c_str());
	if(fout.fail())
	{
		error(filename+" has failed to open for writeForward function");
		return 0;
	}
	if(op == "iterative")
		current->list.writeForwardIterative(fout);
	else
		current->list.writeForward(current->list.head, fout); // calls recursive definition to write forward
	fout.close();
	return 99;
}

int ListContainer::writeReverse(string listID, string filename, string op)
{
	ofstream fout;
	filename = clean_file_name(filename); //takes away single quotes from the filename
	
	ListNode *current;
	current = find_list(listID); //finds the list in the list of lists, if it doesn't exist, return
	if(current == NULL)
	{
		fout.open(filename.c_str());
		if(fout.fail())
		{
			error(filename+" has failed to open for writeForward function");
			return 0;
		}
		fout << "List "+listID+" does not exist " << endl;
		fout.close();
		return -3;
	}
	fout.open(filename.c_str());
	if(fout.fail())
	{
		error(filename+" has failed to open for writeForward function");
		return 0;
	}
	if(op == "iterative")
		current->list.writeReverseIterative(fout);
	else
		current->list.writeReverse(current->list.head, fout); // calls recursive definition to write reverse
	fout.close();
	return 99;
}

int ListContainer::union_initialize(string listname1, string listname2, string listname3, string op) // finds union of list1 and list2 and stores it into list3
{
	
	ListNode *list1, *list2, *list3;
	if(head == NULL) //checks that a read input has occurred, if not returns -3 which triggers an error message.
		return -3;
	list1 = find_list(listname1); // calls a recursive search function that finds the list named listname1
	list2 = find_list(listname2); // calls a recursive search function that finds the list named listname2
	list1->list.alphabetize(); //calls a bubble sort that alphabetizes and merges identical words
	list2->list.alphabetize(); //calls a bubble sort that alphabetizes and merges identical words
	//list1->list.output();
	//cout <<  " alphabetized above " <<endl;
	//list2->list.output();
	//cout <<  " alphabetized above  ( l2 )" <<endl;
	if(list1 == NULL || list2 == NULL)
	{
		error("either "+listname1+" or "+listname2+" do not exist therefore the union cannot be executed");
		return 5;
	}
	list3 = new ListNode(); //allocates memory for a new ListNode
	list3->listID = listname3; //sets the List name in the ListNode object
	if(op == "recursive")
		list3->list = union_func(list1->list.head, list2->list.head, list3->list); // calls the main recursive definition of union
	else
	{
		list3->list.head = union_func_iterative(list1->list.head, list2->list.head); // calls iterative definition of union
	}
	//list3->list.output();
	//list3->list.alphabetize();
	add_list(list3); //place list3 into ListContainer list at the first opening
	return 99;
}

int ListContainer::intersect_initialize(string listname1, string listname2, string listname3, string op)
{
	ListNode *list1, *list2, *list3;
	if(head == NULL)
	{	
		return -3;
	}
	list1 = find_list(listname1);
	list2 = find_list(listname2);
	list1->list.alphabetize(); //calls a bubble sort that alphabetizes and merges identical words
	list2->list.alphabetize(); //calls a bubble sort that alphabetizes and merges identical words
	if(list1 == NULL || list2 == NULL)
	{
		error("either "+listname1+" or "+listname2+" do not exist therefore the union cannot be executed");
		return 5;
	}
	list3 = new ListNode();//allocates memory for a new ListNode
	list3->listID = listname3;//sets the List name in the ListNode object

	if(op == "recursive")
		list3->list = intersection_func(list1->list, list2->list.head, list3->list);// calls the main recursive definition of intersection
	else
		list3->list = intersection_func_iterative(list1->list, list2->list.head, list3->list); // calls iterative definition of intersection
	//list3->list.alphabetize();
	add_list(list3);//place list3 into ListContainer list at the first opening
	return 99; // time actual is +12 here
}


LinkedList ListContainer::union_func(Node* list1, Node* list2, LinkedList newList) //recursive function to create a union of list1 and list2 and store it into newList
{
	if(list2 == NULL && list1 == NULL)
		return newList;
	if(list1 == NULL)
	{
		if(!newList.doesWordExist(newList.head, list2->word))
		{
			newList.addWord(list2->word, "", list2->count, list2->punc_count); //add word to newList here only if the word is not in the list
			union_func(list1, list2->next, newList);
		}
		else
		{
			newList.increaseCount(list2->word, list2->count); //increase count of word in newList here only if the word is already in the list
			union_func(list1, list2->next, newList);
		}
		return newList;
	}
	else if(!newList.doesWordExist(newList.head, list1->word))
	{
		newList.addWord(list1->word, "", list1->count, list1->punc_count); //add word to newList here only if the word is not in the list
		union_func(list1->next, list2, newList);
	}
	else
	{
		newList.increaseCount(list1->word, list1->count); //increase count of word in newList here only if the word is already in the list
		union_func(list1->next, list2, newList);
	}
	return newList;
}

Node* ListContainer::union_func_iterative(Node* list1, Node* list2) //assumes both lists are sorted, and merges them
{
	Node *last_in_merged, *newHead, *temp;

	if(list1 == NULL)
		return list2;
	else if(list2 == NULL)
		return list1;
	else
	{
		if(strcmp(list1->word.c_str(), list2->word.c_str()) == 0)
		{
			int temp_count = list1->count + list2->count;
			temp = new Node;
			temp->count = temp_count;
			temp->word = list1->word;
			
			newHead = temp;
			last_in_merged = newHead;
			
			list1 = list1->next;
			list2 = list2->next;
		}
		else if(strcmp(list1->word.c_str(), list2->word.c_str()) < 0)
		{
			newHead = list1;
			list1 = list1->next;
			last_in_merged = newHead;
		}
		else
		{
			newHead = list2;
			list2 = list2->next;
			last_in_merged = newHead;
		}
	}
	
	while(list2 != NULL && list1 != NULL)
	{
		if(strcmp(list1->word.c_str(), list2->word.c_str()) == 0)
		{
			int temp_count = list1->count + list2->count;
			temp = new Node;
			temp->count = temp_count;
			temp->word = list1->word;
			
			last_in_merged->next = temp;
			last_in_merged = last_in_merged->next;
			list1 = list1->next;
			list2 = list2->next;
		} 
		else if(strcmp(list1->word.c_str(), list2->word.c_str()) < 0)
		{
			last_in_merged->next = list1;
			last_in_merged = last_in_merged->next;
			list1 = list1->next;
		}
		else
		{
			last_in_merged->next = list2;
			last_in_merged = last_in_merged->next;
			list2 = list2->next;
		}
	}
	if(list1 == NULL)
	{
		last_in_merged->next = list2;
	}
	else
	{
		last_in_merged->next = list1;
	}
	return newHead; 
}

LinkedList ListContainer::intersection_func(LinkedList list1, Node* list2, LinkedList newList)
{
	if(list2 == NULL)
	{
		return newList;
		
	}
	if(!newList.doesWordExist(newList.head, list2->word))
	{
		if(list1.doesWordExist(list1.head, list2->word))
		{
			newList.addWord(list2->word, "", 1, list2->punc_count);
			return intersection_func(list1, list2->next, newList);
		}
	}
	return intersection_func(list1, list2->next, newList);
}

LinkedList ListContainer::intersection_func_iterative(LinkedList list1, Node* list2, LinkedList newList) // TODO: test and ensure this is properly working
{
	while(list2 != NULL)
	{
		//time_actual++;
		//if(!newList.doesWordExist(list2->word)) //if a word is not in the new list
		//{ 
			if(list1.doesWordExist(list2->word))//and it IS in the other list
			{ 
				newList.addWord(list2->word, 1); //add the word to the new list
				list2 = list2->next;
				continue;
			}
			//time_actual++;
		//}
		list2 = list2->next;
	}
	return newList; // (2*n_low)*(2*n_hi+1) + (2*n_low+8)
}

void ListContainer::armageddon()
{
	ListNode *current = head;
	while(current != NULL)
	{
		current->list.armageddon(current->listID);
		current = current->next;
	}
	return;
}

long ListContainer::getN(string listname)
{
	long n = 0;
	ListNode *temp = find_list(listname);
	Node* temp_h = temp->list.head;
	while(temp_h != NULL)
	{
		temp_h = temp_h->next;
		n++;
	}
	return n;
}

ListNode *ListContainer::find_list(string listname)
{
	ListNode *current = head;
	while(current != NULL)
	{
		if(current->listID == listname)
		{
			return current;
		}
		current = current->next;
	}
	return NULL;
}

string ListContainer::clean_file_name(string filename)
{
	char* str = new char[filename.length()+1];
	strcpy(str, filename.c_str());
	str = strtok(str, "'");
	return str;
}