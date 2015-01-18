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
#include "LinkedList.cpp"

using namespace std;

class ListNode
{
	public:
		ListNode *previous, *next;
		string listID;
		LinkedList list;
		ListNode();
};

class ListContainer
{
	public:
		ListNode *head;
		ListContainer();
		int initialize(string listID, string filename); //initializes list under the listID returns -1 if invalid filename
		int union_initialize(string listname1, string listname2, string listname3); //setting up the call to the recursive definition of union
		int intersect_initialize(string listname1, string listname2, string listname3);//setting up the call to the recursive definition of intersection
		ListNode *find_list(string listname); //finds the listcontainer at the location listID == listname
		LinkedList union_func(Node* list1, Node* list2, LinkedList newList); // recursive definition of union
		LinkedList intersection_func(LinkedList list1, Node* list2, LinkedList newList); //recursive definition of intersection
		void add_list(ListNode *thelist); // adds *thelist to the listcontainer in the first available spot
		int writeForward(string listID, string filename); //writes the list at listID out to filename 
		int writeReverse(string listID, string filename); // writes the list at listID out to filename in reverse order
		void armageddon(); //destroys and frees all memory from all lists
		void error(string error_message); //generic output for error messages to log file
};
		

int main(int argc, char *argv[])
{
	ListContainer list_container;
	LinkedList list;
	if ( argc != 2 )
	{
		list_container.error("No file input or too many arguments, please try again");
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
		list_container.error("Failure to open script file "+fn+" exiting program...");
		return -1;
	}
	list_container.error("||||||||||||| Start log for script file "+fn+" |||||||||||||");
	while(getline(fin, line)) 
	{
		scriptparse.ParseLine(line);
		//cout << "listID: " << scriptparse.cmd.listID <<" value 1 " << scriptparse.cmd.value1 << " value 2 " << scriptparse.cmd.value2 << " op code: " << scriptparse.operationCode() << endl;
		switch (scriptparse.operationCode())
		{
		case 1:
			//track = list_container.insert(scriptparse.cmd.listID, scriptparse.cmd.value1, scriptparse.cmd.value2); //inserts value 2 into the list after position value 1 is at
			break;
		case 2:
			//track = list_container.del(scriptparse.cmd.listID, scriptparse.cmd.value1); //deletes the word that is stored in value1
			break;
		case 3:
			track = list_container.initialize(scriptparse.cmd.listID, scriptparse.cmd.value1); // reads file into list
			break;
		case 4:
			track = list_container.writeForward(scriptparse.cmd.listID, scriptparse.cmd.value1); //outputs file to specified output file
			break;
		case 5:
			track = list_container.writeReverse(scriptparse.cmd.listID, scriptparse.cmd.value1); //outputs file to specified output file in reverse order
			break;
		case 6:
			track = list_container.union_initialize(scriptparse.cmd.listID, scriptparse.cmd.value1, scriptparse.cmd.value2);
			break;
		case 7:
			track = list_container.intersect_initialize(scriptparse.cmd.listID, scriptparse.cmd.value1, scriptparse.cmd.value2);
			break;
		case 0:
			list_container.error("Operation not recognized, check your script file for errors! Exiting program...");
			track = -2;
			break;
		  }
	
		if(track == -1)
			break;
    }
	
	if(track == -1)
	{
		list_container.error("failed to initialize list due to invalid input file name");
	}
	if(track == -3)
	{
		list_container.error("The list was not initiated before performing operations.");
	}

	list_container.armageddon();
	list_container.error("||||||||||||| End log for script file "+fn+" |||||||||||||");
	return 99;
}
 
 ListNode::ListNode()
 {
	listID = "";
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
	if(head == NULL)
	{
		head = new ListNode();
		head->listID = listID;
		head->list.initialize(filename);
		head->list.del("");
		head->list.alphabetize();
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
			current->next->list.del(""); //deletes any empty words in list if they exist //not working
			current->next->list.alphabetize();
			return 99;
		}
		current = current->next;
	}
	return -1;
}
ListNode *ListContainer::find_list(string listname) // working as intended, TODO: change to recursive
{
	ListNode *current = head;
	while(current != NULL)
	{
		if(current->listID == listname)
			return current;
		current = current->next;
	}
	return NULL;
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

int ListContainer::writeForward(string listID, string filename)
{
	ofstream fout;
	fout.open(filename.c_str());
	if(fout.fail())
	{
		error(filename+" has failed to open for writeForward function");
		return 0;
	}
	
	ListNode *current;
	current = find_list(listID);
	if(current == NULL)
		return -3;
	
	current->list.writeForward(current->list.head, fout); // calls recursive definition to write forward
	fout.close();
	return 99;
}

int ListContainer::writeReverse(string listID, string filename)
{
	ofstream fout;
	fout.open(filename.c_str());
	if(fout.fail())
	{
		error(filename+" has failed to open for writeForward function");
		return 0;
	}
	
	ListNode *current;
	current = find_list(listID);
	if(current == NULL)
		return -3;
	
	current->list.writeReverse(current->list.head, fout); // calls recursive definition to write reverse
	fout.close();
	return 99;
}

int ListContainer::union_initialize(string listname1, string listname2, string listname3) // finds union of list1 and list2 and stores it into list3
{
	ListNode *list1, *list2, *list3;
	if(head == NULL) //checks that a read input has occurred, if not returns -3 which triggers an error message.
		return -3;
	list1 = find_list(listname1); // calls a recursive search function that finds the list named listname1
	list2 = find_list(listname2); // calls a recursive search function that finds the list named listname2
	if(list1 == NULL || list2 == NULL)
	{
		error("either "+listname1+" or "+listname2+" do not exist therefore the union cannot be executed");
		return 5;
	}
		
	list3 = new ListNode(); //allocates memory for a new ListNode
	list3->listID = listname3; //sets the List name in the ListNode object
	list3->list = union_func(list1->list.head, list2->list.head, list3->list); // calls the main recursive definition of union
	list3->list.alphabetize();

	add_list(list3); //place list3 into ListContainer list at the first opening
	
	return 99;
}

int ListContainer::intersect_initialize(string listname1, string listname2, string listname3)
{
	ListNode *list1, *list2, *list3;
	if(head == NULL)
		return -3;
	list1 = find_list(listname1);
	list2 = find_list(listname2);
	
	if(list1 == NULL || list2 == NULL)
	{
		error("either "+listname1+" or "+listname2+" do not exist therefore the union cannot be executed");
		return 5;
	}
	
	list3 = new ListNode();//allocates memory for a new ListNode
	list3->listID = listname3;//sets the List name in the ListNode object
	list3->list = intersection_func(list1->list, list2->list.head, list3->list);// calls the main recursive definition of intersection
	
	add_list(list3); //place list3 into ListContainer list at the first opening
	return 99;
}


LinkedList ListContainer::union_func(Node* list1, Node* list2, LinkedList newList) //recursive function to create a union of list1 and list2 and store it into newList
{
	if(list2 == NULL)
		return newList;
	if(list1 == NULL)
	{
		if(!newList.doesWordExist(newList.head, list2->word))
		{
			newList.addWord(list2->word); //add word to newList here only if the word is not in the list
			union_func(list1, list2->next, newList);
		}
		else
		{
			newList.increaseCount(list2->word); //increase count of word in newList here only if the word is already in the list
			union_func(list1, list2->next, newList);
		}
		return newList;
	}
	else if(!newList.doesWordExist(newList.head, list1->word))
	{
		newList.addWord(list1->word); //add word to newList here only if the word is not in the list
		union_func(list1->next, list2, newList);
	}
	else
	{
		newList.increaseCount(list1->word); //increase count of word in newList here only if the word is already in the list
		union_func(list1->next, list2, newList);
	}
	return newList;
}

LinkedList ListContainer::intersection_func(LinkedList list1, Node* list2, LinkedList newList)
{
	if(list2 == NULL)
	{
		return newList;
		
	}
	bool exp = (!newList.doesWordExist(newList.head, list2->word));
	if(exp)
	{
		if(list1.doesWordExist(list1.head, list2->word))
		{
			newList.addWord(list2->word);
			return intersection_func(list1, list2->next, newList);
		}
	}
	return intersection_func(list1, list2->next, newList);
}

void ListContainer::armageddon()
{
	ListNode *current = head;
	ListNode *temp = NULL;
	while(current != NULL)
	{
		(current->list).armageddon(current->listID);
		current = current->next;
	}
	return;
}