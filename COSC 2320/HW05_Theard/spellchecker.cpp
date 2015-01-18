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
#include "StackContainer.cpp"

using namespace std;

class TreeNode
{
	public:
		string word;
		int balance_factor;
		TreeNode *left;
		TreeNode *right;
		TreeNode();
};

class TreeContainer
{
	public:
		TreeNode *root;
		ListContainer *all_lists;
		
		int tree_height(); //gets height of the full tree
		int get_tree_height(TreeNode *root); //gets height of a given sub-tree
		//int node_count(); //gets total node count for the tree
		//int get_node_count(TreeNode *root); //gets total node count for the given sub-tree
		int leaves_count(); //gets number of leaves in tree
		int get_leaves_count(TreeNode *root); //gets number of leaves in given tree
		void balance_from_right(TreeNode* &root);
		void balance_from_left(TreeNode* &root);
		void rotate_to_left(TreeNode* &root);
		void rotate_to_right(TreeNode* &root);
		bool search(string word);
		void check(string old_list, string new_list);
		bool is_empty();
		void inorderTraversal();
		void inorder(TreeNode *p);
		//void preorderTraversal();
		void postorderTraversal();
		void postorder(TreeNode *p);
		void print(TreeNode *p, int indent);
		void insert(TreeNode* &root, TreeNode *newNode, bool &is_taller);
		void insert_initialize(string newWord);
		void initiate_tree(LinkedList list); //function that initiates a tree from a list input
		int max(int first_int, int second_int);
		TreeContainer();
		void destroy_tree();
		
		//testing functions
		//string printLevel(TreeNode *root, int level, string gap);
		//void printLevelOrder(TreeNode *root, int depth);
};

int main(int argc, char *argv[])
{
	ListContainer list_container;
	StackContainer stack_container;
	stack_container.all_lists = &list_container;
	TreeContainer tree_container;
	tree_container.all_lists = &list_container;

	if ( argc != 2 )
	{
		list_container.error("No file input or too many arguments, please try again");
		return -1;
	}
	ArgumentManager argMgr(argv[1]);
	string filename = argMgr.get("script");
	string dict_filename = argMgr.get("dictionary"); 

	char* fn = new char[filename.length()+1];
	strcpy(fn, filename.c_str());
	
	list_container.initialize("dictionary", dict_filename); //insert the dictionary into a list
	ListNode* dictionary_list = list_container.find_list("dictionary");
	tree_container.initiate_tree(dictionary_list->list);
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
					list_container.writeForward(op.getParameter(0), op.getParameter(1), "iterative");
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
		else
			list_container.error("operation is neither an expression, read/write, or union/intersection and therefore invalid");
	}

	list_container.armageddon(); //deallocates all memory taken by the various lists and crashes the program currently, after merge was implemented in union_func_iterative
	list_container.error("||||||||||||| End log for script file "+filename+" |||||||||||||");
	return 99;
}

TreeNode::TreeNode()
{
	word		   = "";
	balance_factor = 0;
	left 		   = NULL;
	right 		   = NULL;
}

bool TreeContainer::is_empty()
{
	return (root == NULL);
}

TreeContainer::TreeContainer()
{
	root = NULL;
}

int TreeContainer::tree_height()
{
	return get_tree_height(root);
}

//int TreeContainer::node_count()
//{
	//return get_node_count(root);
//}

//int TreeContainer::get_node_count(TreeNode *root)
//{
	
//}
void TreeContainer::print(TreeNode* p, int indent)
{

    if(p != NULL) 
	{
        if(p->left) 
			print(p->left, indent+4);
        if(p->right) 
			print(p->right, indent+4);
        if (indent) 
		{
           cout << setw(indent) << ' ';
        }
        cout<< p->word << "\n ";
    }
}

int TreeContainer::leaves_count()
{
	return get_leaves_count(root);
}

int TreeContainer::get_leaves_count(TreeNode *parent)
{
	if(parent->left == NULL && parent->right == NULL)
		return 1;
	else if(parent->right != NULL)
		return get_leaves_count(parent->right);
	else if(parent->left != NULL)
		return get_leaves_count(parent->left);
	else
		return get_leaves_count(parent->left) + get_leaves_count(parent->right);
}

void TreeContainer::inorderTraversal()
{
	inorder(root);
}

void TreeContainer::inorder(TreeNode *p)
{
	if(p != NULL)
	{
		inorder(p->left);
		cout << p->word <<" ";
		inorder(p->right);
	}
}

void TreeContainer::postorderTraversal()
{
	postorder(root);
}

void TreeContainer::postorder(TreeNode *p)
{
	if(p != NULL)
	{
		inorder(p->left);
		inorder(p->right);
		cout << p->word <<" ";
	}
}
		

int TreeContainer::get_tree_height(TreeNode *parent)
{
	if(parent == NULL)
		return 0;
	else
		return 1 + max(get_tree_height(parent->left), get_tree_height(parent->right));
}

int TreeContainer::max(int first_int, int second_int)
{
	if(first_int >= second_int)
		return first_int;
	else
		return second_int;
}

void TreeContainer::insert_initialize(string newWord)
{
	bool isTaller = false;
	TreeNode *newNode;
	
	newNode = new TreeNode;
	
	newNode->word 			= newWord;
	newNode->balance_factor = 0;
	newNode->left 			= NULL;
	newNode->right 			= NULL;
	
	insert(root, newNode, isTaller);
}

void TreeContainer::rotate_to_left(TreeNode* &root)
{
	TreeNode *p;
	
	if(root == NULL)
		cout<<"error in rot_to_left" << endl;//TODO: change to error to log
	else if(root->right == NULL)
		cout <<"no right tree to rotate (in rot_to_left)"<<endl;//TODO: change to error to log
	else //the swap
	{
		p = root->right;
		root->right = p->left; // left subtree of p becomes right subtree of root
		p->left = root;
		root = p;
	}
}

void TreeContainer::rotate_to_right(TreeNode* &root)
{
	TreeNode *p;
	
	if(root == NULL)
		cout<<"error in rot_to_left" << endl;//TODO: change to error to log
	else if(root->left == NULL)
		cout <<"no right tree to rotate (in rot_to_left)"<<endl;//TODO: change to error to log
	else //the swap
	{
		p = root->left;
		root->left = p->right; // right subtree of p becomes left subtree of root
		p->right = root;
		root = p; //make p new root
	}
}

void TreeContainer::balance_from_left(TreeNode* &root)
{
	TreeNode *p, *w;
	
	p = root->left;
	
	switch(p->balance_factor)
	{
		case -1:
			root->balance_factor = 0;
			p->balance_factor = 0;
			rotate_to_right(root);
			break;
			
		case 0:
			//TODO: output error to log "cannot balance from the left" (missing node?)
			break;
		
		case 1:
			w = p->right;
			
			switch(w->balance_factor) //adjusting balance factors
			{
				case -1:
					root->balance_factor = 1;
					p->balance_factor = 0;
					break;
				
				case 0:
					root->balance_factor = 0;
					p->balance_factor = 0;
					break;
				
				case 1:
					root->balance_factor = 0;
					p->balance_factor = -1;
			}
			
			w->balance_factor = 0;
			rotate_to_left(p);
			root->left = p;
			rotate_to_right(root);
	}
}

void TreeContainer::balance_from_right(TreeNode* &root)
{
	TreeNode *p, *w;
	
	p = root->right;
	
	switch(p->balance_factor)
	{
		case -1:
			w = p->left;
			
			switch(w->balance_factor) //adjusting balance factors
			{
				case -1:
					root->balance_factor = 0;
					p->balance_factor = 1;
					break;
				
				case 0:
					root->balance_factor = 0;
					p->balance_factor = 0;
					break;
				
				case 1:
					root->balance_factor = -1;
					p->balance_factor = 0;
			}
			
			w->balance_factor = 0;
			rotate_to_right(p);
			root->right = p;
			rotate_to_left(root);
			break;
			
		case 0:
			//TODO: output error to log "cannot balance from the left" (missing node?)
			break;
		
		case 1:
			root->balance_factor = 0;
			p->balance_factor = 0;
			rotate_to_left(root);
	}
}

void TreeContainer::insert(TreeNode* &root, TreeNode *newNode, bool &isTaller)
{
	if(root == NULL)
	{
		root = newNode;
		isTaller = true;
	}
	else if(strcmp(root->word.c_str(), newNode->word.c_str()) == 0)
	{
		//TODO: output error to log for no repeated info allowed
		return;
	}
	else if(strcmp(root->word.c_str(), newNode->word.c_str()) > 0)
	{
		insert(root->left, newNode, isTaller);
		
		if(isTaller) // after inserting the sub-tree is now taller
		{
			switch(root->balance_factor)
			{
				case -1:
					balance_from_left(root);
					isTaller = false;
					break;
				
				case 0:
					root->balance_factor = -1;
					isTaller = true;
					break;
					
				case 1:
					root->balance_factor = 0;
					isTaller = false;
			}
		}
	}
	else
	{
		insert(root->right, newNode, isTaller);
		
		if(isTaller) // after inserting the sub-tree is now taller
		{
			switch(root->balance_factor)
			{
				case -1:
					root->balance_factor = 0; 
					isTaller = false;
					break;
				
				case 0:
					root->balance_factor = 1;
					isTaller = true;
					break;
					
				case 1:
					balance_from_right(root);
					isTaller = false;
			}
		}
	}
}

void TreeContainer::initiate_tree(LinkedList list)
{
	if(list.head == NULL)
	{
		//output error to log, empty dictionary file
		return;
	}
	
	Node* current = list.head;
	
	while(current != NULL)
	{
		insert_initialize(current->word);
		current = current->next;
	}
}

bool TreeContainer::search(string word)
{
	TreeNode *current;
	
	if(root == NULL)
		return false;
	else
	{
		current = root;
		
		while(current != NULL)
		{
			if(strcmp(current->word.c_str(), word.c_str()) == 0)
				return true;
			else if(strcmp(current->word.c_str(), word.c_str()) > 0)
				current = current->left;
			else
				current = current->right;
		}
	}
	
	return false;
}

void TreeContainer::check(string new_list, string old_list) //creates a new_list of the incorrectly spelled words out of the old_list
{
	ListNode *oldlist = all_lists->find_list(old_list);
	ListNode *newlist = new ListNode;
	newlist->listID = new_list;
	
	Node *current = oldlist->list.head;
	
	while(current != NULL)
	{
		if(!search(current->word))
			newlist->list.addWord(current->word, current->cleaned_word, current->count, current->punc_count);
		current = current->next;
	}
	
	all_lists->add_list(newlist);
}

 /*string TreeContainer::printLevel(TreeNode *root, int level, string gap)
{
	if (root == 0) 
	{
    return gap + "-" + gap;
  }
  if (level==1) 
  {
    stringstream out;
    out<<root->word;
    return gap + out.str() + gap;
  } 
  else if (level>1) 
  {
    string leftStr = printLevel(root->left, level-1, gap);
    string rightStr = printLevel(root->right, level-1, gap);
    return leftStr + " " + rightStr;
  } 
  else return "";
}

void TreeContainer::printLevelOrder(TreeNode *root, int depth)
{
	for (int i=1; i<=depth; i++) 
	{
    string gap="";
    for (int j=0; j<pow(2,depth-i)-1; j++) 
	{
      gap+=" ";
    }
    string levelNodes = printLevel(root, i, gap);
    cout<<levelNodes<<endl;
  }
}*/