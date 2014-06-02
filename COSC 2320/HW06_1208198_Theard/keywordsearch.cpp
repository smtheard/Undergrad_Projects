#include <iostream>
#include <iomanip>
#include <fstream>
#include <cctype>
#include <string>
#include <sstream>
#include <stdio.h>
#include <string.h>
#include <cstring>
#include "ArgumentManager.cpp"
#include "OperationQueue.cpp"
#include "TreeContainer.cpp"

using namespace std;

class HashContainer
{
	public:
		int table_size;
		TreeContainer *stopword_tree;
		ListContainer *all_lists;
		ListNode *hash_table[100000];//26759]; //table_size is equal to 26759, a prime number around 26000
		
		HashContainer();
		
		void filter(string listname);
		void index(string corpus);
		void search(string listID, string keyword);
		
		//auxillary functions
		void copy(LinkedList& newlist, LinkedList oldlist);
		int hash(string word);
		void output();
		bool isNumeric(string str);
};

int main(int argc, char *argv[])
{
	ListContainer list_container;
	StackContainer stack_container;
	stack_container.all_lists = &list_container;
	TreeContainer tree_container;
	tree_container.all_lists = &list_container;
	HashContainer hash_container;
	hash_container.all_lists = &list_container;
	hash_container.stopword_tree = &tree_container;

	if ( argc != 2 )
	{
		list_container.error("No file input or too many arguments, please try again");
		return -1;
	}
	ArgumentManager argMgr(argv[1]);
	string filename = argMgr.get("script");
	//string dict_filename = argMgr.get("dictionary");  

	char* fn = new char[filename.length()+1];
	strcpy(fn, filename.c_str());
	
	//list_container.initialize("dictionary", dict_filename); //insert the dictionary into a list
	//ListNode* dictionary_list = list_container.find_list("dictionary");
	//tree_container.initiate_tree(dictionary_list->list);
	//tree_container.printLevelOrder(tree_container.root, 6);
	
	
	ifstream fin(fn);
	if(fin.fail())
	{
		list_container.error("Failure to open script file "+filename+" exiting program...");
		return -1;
	}
	
	list_container.error("||||||||||||| Start log for script file "+filename+" |||||||||||||");
	
	OperationQueue opQueue(filename);
	
	while(!opQueue.isEmpty())
	{
		Operation op = opQueue.pop();
		//cout << op << endl;
		if(op.isExpression())	//if true, operation is an expression that needs to be evaluated
		{
			stack_container.convertToPostfix(op.getExpression()); //convert infix to postfix
			stack_container.postfixCalc(op.getName()); //calculte the postfix expression and perform the operations
		}
		else if(op.getName() == "write" || op.getName() == "read")			//if false, the operation could be a simple read or write
		{
			if(op.getName() == "write")
			{	
				if(op.parameterCount() == 2)	//this means there is no 'forward' or 'reverse' specification in which we will just assume forward
				{
					list_container.writeForward(op.getParameter(0), op.getParameter(1), "iterative");
				}
				else if(op.getParameter(2) == "forward")
				{
					list_container.writeForward(op.getParameter(0), op.getParameter(1), "iterative");
				}
				else if(op.getParameter(2) == "reverse")
				{
					list_container.writeReverse(op.getParameter(0), op.getParameter(1), "iterative");
				}
				else
				{
					list_container.writeForward(op.getParameter(0), op.getParameter(1), "recursive");
				}
				continue;
			}
			
			if(op.getName() == "read")
			{
				list_container.initialize(op.getParameter(0), op.getParameter(1));
				continue;
			}
		}
		else if(op.getName() == "union" || op.getName() == "intersection" || op.getName() == "check") //if not expression or read/write, it must be a union or intersection command
		{
			if(op.getName() == "union")
			{
				//call union func from list container with op.getParameter(0) 1 and 2
				list_container.union_initialize(op.getParameter(0), op.getParameter(1), op.getParameter(2), "recursive");
				//continue;
			}
			else if(op.getName() == "intersection")
			{
				//call intersection func from list container with op.getParameter(0) 1 and 2
				list_container.intersect_initialize(op.getParameter(0), op.getParameter(1), op.getParameter(2), "recursive");
				//continue;
			}
			else if(op.getName() == "check")
			{
				//call function that checks the op.getParameter(1) list with the dictionary passed earlier and then stores
				//the misspelled words or words that aren't in the dictionary to op.getParameter(0).
				tree_container.check(op.getParameter(0), op.getParameter(1));
			}
		}
		else if(op.getName() == "load" || op.getName() == "filter" || op.getName() == "index" || op.getName() == "search")
		{
			if(op.getName() == "load")
			{
				//cout << "op name: " << op.getName() << endl;
				list_container.initialize(op.getParameter(0), op.getParameter(1));
				
				ListNode* temp;
				temp = list_container.find_list(op.getParameter(0)); //find corpus list
				
				Node* current;
				current = temp->list.head;
				
				while(current != NULL)
				{
					list_container.initialize(current->word, current->word);
					current = current->next;
				}
			}
			else if(op.getName() == "filter")
			{
				//cout << "op name: " << op.getName() << endl;
				list_container.initialize("stopwordUNIQ", op.getParameter(1)); //insert the stop word dictionary into a list
				ListNode* stopword_list = list_container.find_list("stopwordUNIQ");
				tree_container.initiate_tree(stopword_list->list);
				//since hash_container has an object of tree_container given to it earlier, this tree is now created and stored
				//in hash_container for use as a filter.
				
				hash_container.filter(op.getParameter(0));
				//tree_container.printLevelOrder(tree_container.root, 6);
				//hash_container.stopword_tree->printLevelOrder(hash_container.stopword_tree->root, 6);
			}
			else if(op.getName() == "index")
			{
				hash_container.index(op.getParameter(0));
			}
			else if(op.getName() == "search")
			{
				int i = 1;
				for(i; i < op.parameterCount()-1;i++)
				{
					string keyword = list_container.clean_file_name(op.getParameter(i));
					hash_container.search(op.getParameter(0), keyword);
				}
			}
		}
		else
			list_container.error("operation is neither an expression, read/write, or union/intersection and therefore invalid");
	}

	//list_container.armageddon(); //deallocates all memory taken by the various lists and crashes the program currently, after merge was implemented in union_func_iterative
	list_container.error("||||||||||||| End log for script file "+filename+" |||||||||||||");
	return 99;
}


HashContainer::HashContainer()
{
	stopword_tree = NULL;
	all_lists = NULL;
	table_size = 100000;//26759;
	for(int i = 0; i<table_size; i++)
		hash_table[i] = NULL;
}

void HashContainer::filter(string listname)
{
	ListNode* corpus_list;
	corpus_list = all_lists->find_list(listname);
	
	Node* current = corpus_list->list.head;
	
	while(current != NULL)
	{
		ListNode* temp_list = all_lists->find_list(current->word);
		Node* temp_current = temp_list->list.head;
		Node* del_temp;
		
		while(temp_current != NULL)
		{
			if(stopword_tree->search(temp_current->word) || isNumeric(temp_current->word)) //if the word is found in the stopword tree or is numeric, remove it.
			{
				string temp_str = temp_current->word;
				temp_current = temp_current->next;
				temp_list->list.del(temp_str);
				continue;
			}
			temp_current = temp_current->next;
		}
		
		
		current = current->next;
	}
	return;
}

void HashContainer::index(string corpus) 
{
	int hash_num = 0, j = 0;
	ListNode* corpus_list, *temp_list, *chain_list;
	corpus_list = all_lists->find_list(corpus);

	Node* corpus_current, *current;
	
	corpus_current = corpus_list->list.head;
	
	while(corpus_current != NULL) //iterate through corpus list.. (the list of text file names)
	{
		temp_list = all_lists->find_list(corpus_current->word); //find the list at a given text file name. store it into temp_list
		current = temp_list->list.head; //assign the text file's list to current
		while(current != NULL)//iterate through text file
		{	//cout << current->word << " WORD HERE " << endl;
			hash_num = hash(current->word); //hash algorithm applied to current word and store it into hash_num
			if(hash_table[hash_num] == NULL)	//if there is no collision insert into hash table as usual.
				hash_table[hash_num] = new ListNode(current->word, temp_list->listID);
			else //there is a collision or duplicate
			{
				chain_list = hash_table[hash_num];
				while(chain_list != NULL)
				{
					if(strcmp(chain_list->listID.c_str(), current->word.c_str()) == 0 || chain_list->listID == current->word) //if the word stored in listID and current->word are the same
					{																										  //this is a duplicate, and the file name should be added to the list.
						if(!chain_list->list.doesWordExist(temp_list->listID))
							chain_list->list.addWord(temp_list->listID, 1);
						break;
					}
					else if(chain_list->next == NULL) //if the end of the list is next, that means there is a collision
					{								//and a new node should be created with the listID of the second word that shares a hash.
						j++;
						//cout << current->word << " has collided with "<< chain_list->listID<<" and temp_list->listID is: " <<temp_list->listID << endl;
						chain_list->next = new ListNode(current->word, temp_list->listID);
						chain_list->next->previous = chain_list;
						break;
					}
					chain_list = chain_list->next;
				}
			}
			current = current->next;
		}
		corpus_current = corpus_current->next;
	}
	//output();
	//cout << "Number of collisions: " << j << endl;
	return;
}

void HashContainer::copy(LinkedList& newList, LinkedList oldlist)
{
	LinkedList building_list;
	Node* current_rhs = oldlist.head;
	while(current_rhs != NULL)
	{
		if(building_list.head == NULL)
		{
			Node* newNode = new Node;
			newNode->word = current_rhs->word;
			newNode->cleaned_word = current_rhs->cleaned_word;
			newNode->count = current_rhs->count;
			newNode->punc_count = current_rhs->punc_count;
			building_list.head = newNode;
		}
		else
		{
			Node* temp = building_list.head;
			while(temp->next != NULL)
			{
				
				temp = temp->next;
			}
			temp->next = new Node;
			temp->next->word = current_rhs->word;
			temp->next->cleaned_word = current_rhs->cleaned_word;
			temp->next->count = current_rhs->count;
			temp->next->punc_count = current_rhs->punc_count;
			temp->next->previous = temp;
			
		}
		current_rhs = current_rhs->next;
	}
	//building_list.output();
	newList.head = building_list.head;
	return;
}

void HashContainer::search(string listID, string keyword)
{
	int hash_num = hash(keyword);
	ListNode* search_list, *chain_list;
	Node* current;
	
	bool list_is_null = false;
	
	search_list = all_lists->find_list(listID);
	
	if(search_list == NULL)
		list_is_null = true;
	
	if(hash_table[hash_num] == NULL) //make a blank list because the word searched does not exist
	{
		search_list = new ListNode;
		search_list->listID = listID;
		all_lists->add_list(search_list);
		return;
	}
	else if(hash_table[hash_num]->listID == keyword)
	{
		if(list_is_null)
		{
			search_list = new ListNode;
			copy(search_list->list, hash_table[hash_num]->list);
			search_list->listID = listID;
			all_lists->add_list(search_list);
			return;
		}
		else
		{
			//new code: takes an intersection of the file lists common to multiple keywords if given more than one.
			current = search_list->list.head;
			while(current != NULL)
			{	
				Node* temp = current;
				current = current->next;
				if(!hash_table[hash_num]->list.doesWordExist(temp->word))
				{
					//cout << temp->word << " was not in the list for " << hash_table[hash_num]->listID << endl;
					search_list->list.del(temp->word);
				}
			}
			return;
		}
	}
	else
	{
		chain_list = hash_table[hash_num];
		while(chain_list != NULL)
		{
			if(chain_list->listID == keyword)
			{
				if(list_is_null)
				{
					search_list = new ListNode;
					copy(search_list->list, chain_list->list);
					search_list->listID = listID;
					all_lists->add_list(search_list);
					return;
				}
				else
				{
					current = search_list->list.head; 
					while(current != NULL)
					{
						Node* temp = current;
						current = current->next;
						if(!chain_list->list.doesWordExist(temp->word))
						{
							//cout << temp->word << " was not in the list for " << chain_list->listID << endl;
							search_list->list.del(temp->word);
						}
					}
					return;
				}
			}
			chain_list = chain_list->next;
		}
		if(chain_list == NULL) //if after iterating the chain, it is null and hasn't returned earlier, the keyword doesn't exist in the hash table
		{					   //and so there is a blank list created.
			search_list = new ListNode;
			search_list->listID = listID;
			all_lists->add_list(search_list);
			return;
		}
	}
}

int HashContainer::hash(string word)
{
	double sum = 0;
	for(unsigned int i = 0; i < word.length() ; i++)
	{
		sum = sum + static_cast<int>(word.at(i));
		sum = sum + sum/7;
		sum+=3;
	}
	sum = sum + 15;
	sum = sum*(sum/2);
	return (static_cast<int>(sum)%table_size);
}

void HashContainer::output()
{
	ListNode* current;
	int j = 0;
	for(int i = 0 ; i<table_size; i++)
	{
		if(hash_table[i] == NULL)
			cout << "";
		else
		{
			current = hash_table[i];
			while(current != NULL)
			{
				if(current->listID == "keyword"){
					cout<<"bucket " << i << " has item: " << current->listID << " and list data: " << endl;
					current->list.output();
					}
				current = current->next;
			}
			j++;
		}
	}
	cout<<endl<<"amount of buckets that have items: "<< j << endl;
}

bool HashContainer::isNumeric(string str)
{
	for(unsigned int i = 0; i < str.length(); i++)
	{
		if(!isdigit(str.at(i)))
			return false;
	}
	return true;
}
