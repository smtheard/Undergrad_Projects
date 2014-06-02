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
#include "HashContainer.cpp"

using namespace std;

class Vertex
{
	public:
		string id;
		int indegree, outdegree;
		string links_out[512];
		
		Vertex();
		void increaseIn(int amt);
		void increaseOut(int amt);
};

class GraphContainer
{
	public:
		Vertex *adjacency_list[512];
		string web_id;
		string broken_links[512];
		string sink_links[512];
		
		GraphContainer();
		
		void initialize_graph(string filename);
		bool isWebLink(string str);
		void set_in_and_out();
		Vertex* find_vertex(string id);
		void add_broken_link(string link_name);
		void rank_output(string filename);
		bool is_broken_link(string link_name);
		void sort_broken_links();
		void sort_adjacency_list();
		void sort_sink_links();
		void add_sink_link(string link_name);
		void dijkstra_calculate(string vertex_name);
		void dijkstra_output();
		
		void output();
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
	GraphContainer *graph_container[64];
	
	for(int i = 0; i<64; i++)
		graph_container[i] = NULL;

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
		//cout << op;
		if(op.isExpression())	//if true, operation is an expression that needs to be evaluated
		{
			stack_container.convertToPostfix(op.getExpression()); //convert infix to postfix
			stack_container.postfixCalc(op.getName()); //calculte the postfix expression and perform the operations
		}
		else if(op.getName() == "load" || op.getName() == "rank" || op.getName() == "dijkstra" || op.getName() == "topsort" )
		{
			if(op.getName() == "load") //loads a file-list text file into an object of graph_container, that is unique to the graph_container's web_id.
			{							//and then uses the objects initialize_graph function to build a graph based on the given file-list text file.
				string cleaned_filename = list_container.clean_file_name(op.getParameter(1));
				for(int i = 0; i<64; i++)//find the first empty graph_container. (support for up to 64 different load functions)
				{
					if(graph_container[i] == NULL) //once found, create an instance of the object, and initialize the graph with the given file list
					{
						graph_container[i] = new GraphContainer();
						graph_container[i]->web_id = op.getParameter(0);
						graph_container[i]->initialize_graph(cleaned_filename);
						break;
					}
				}
			}
			else if(op.getName() == "rank")
			{
				string cleaned_filename = list_container.clean_file_name(op.getParameter(1));
				for(int i = 0; i<64; i++)
				{
					if(op.getParameter(0) == graph_container[i]->web_id)
					{
						graph_container[i]->rank_output(cleaned_filename);
						break;
					}
				}
			}
			else if(op.getName() == "dijkstra")//call in script with dijkstra(WEBNAME,'vertexname.html')
			{
				string cleaned_filename = list_container.clean_file_name(op.getParameter(1));
				for(int i = 0; i<64; i++)
				{
					if(op.getParameter(0) == graph_container[i]->web_id)
					{
						graph_container[i]->dijkstra_calculate(cleaned_filename);
						break;
					}
				}
			}
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
		else if(/*op.getName() == "load" ||*/ op.getName() == "filter" || op.getName() == "index" || op.getName() == "search")
		{
			/*if(op.getName() == "load")
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
			else*/ 
			if(op.getName() == "filter")
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

Vertex::Vertex()
{
	id = "";
	indegree = 0;
	outdegree = 0;
	for(int i = 0; i<512; i++)
		links_out[i] = "";
}

void Vertex::increaseIn(int amt)
{
	indegree = indegree+amt;
	return;
}

void Vertex::increaseOut(int amt)
{
	outdegree = outdegree+amt;
	return;
}

GraphContainer::GraphContainer()
{
	web_id = "";
	for(int i = 0; i<512; i++)
	{
		adjacency_list[i] = NULL;
		broken_links[i] = "";
		sink_links[i] = "";
	}
}

void GraphContainer::initialize_graph(string filename)
{
	ifstream fin, fin2;
	fin.open(filename.c_str());
	if(fin.fail())
		return;
 
	string temp_str, templine;
	char* temp;
	char* buffer;
	
	while(getline(fin, templine)) //triggers as long as there are words in the file
	{
		buffer = strdup(templine.c_str());
		temp = strtok(buffer, " ");
		while(temp != NULL)
		{
			 for(int i = 0; i<512; i++)
			 {
				if(adjacency_list[i] == NULL)
				{
					adjacency_list[i] = new Vertex();
					adjacency_list[i]->id = temp;
					
					
					fin2.open(temp);
					if(fin2.fail())
						return;
					
					string temp_str2, templine2;
					char* temp2;
					char* buffer2;
					
					while(getline(fin2, templine2))
					{
						buffer2 = strdup(templine2.c_str());
						temp2 = strtok(buffer2, "\"");
						while(temp2 != NULL)
						{
							if(isWebLink(temp2))
							{
								for(int j = 0; j<512; j++)
								{
									if(adjacency_list[i]->links_out[j] == "")
									{
										adjacency_list[i]->links_out[j] = temp2;
										break;
									}
								}
							}
							temp2 = strtok(NULL, "\"\n");
						}
					}
					fin2.close();
					break;
				}
			 }
			 
			temp = strtok(NULL, " \n"); // grabs the file name from the getline
		}
	}
	set_in_and_out();
	//output(); //testing purposes
	fin.close();
}

bool GraphContainer::isWebLink(string str)
{
	for(unsigned int i = 0; i<str.length(); i++)
	{
		if(i != 0 && i != str.length()-1)
			if(str.at(i) == '.')
				return true;
	}
	return false;
}

void GraphContainer::output()
{
	cout << "web ID: " << web_id << endl;
	for(int i = 0; i < 512; i++)
	{
		if(adjacency_list[i] != NULL)
		{
			cout << "vector id: " << adjacency_list[i]->id << endl;
			cout << "indegree: " << adjacency_list[i]->indegree << endl;
			cout << "outdegree: " << adjacency_list[i]->outdegree << endl;
			cout << "links: " << endl;
			for(int j = 0; j<512; j++)
			{
				if(adjacency_list[i]->links_out[j] != "")
				{
					cout << "link at position: " <<j<<" " << adjacency_list[i]->links_out[j] << endl;
				}
				else
					break;
			}
			cout<<endl;
		}
		else
			break;
	}
	cout << "broken links: " <<endl;
	for(int i = 0; i<512 ; i++)
	{
		if(broken_links[i] == "")
			break;
		else
			cout << broken_links[i] << endl;
	}
}

Vertex* GraphContainer::find_vertex(string id)
{
	for(int i = 0; i<512; i++)
	{
		if(adjacency_list[i] == NULL)
			return NULL;
		else if(adjacency_list[i]->id == id)
			return adjacency_list[i];
	}
	return NULL;
}

void GraphContainer::set_in_and_out()
{
	for(int i = 0; i < 512; i++) // loop for setting out-degree
	{
		if(adjacency_list[i] == NULL)
			break;
		else
		{
			for(int j = 0; j < 512; j++)
			{
				if(adjacency_list[i]->links_out[j] == "")
				{
					adjacency_list[i]->increaseOut(j);
					break;
				}
			}
		}
	}
	
	for(int i = 0; i < 512; i++) // loop for setting in-degree
	{
		if(adjacency_list[i] == NULL)
			break;
		else
		{
			for(int j = 0; j < 512; j++)
			{
				if(adjacency_list[i]->links_out[j] == "")
					break;
				else
				{
					Vertex *temp;
					temp = find_vertex(adjacency_list[i]->links_out[j]);
					if(temp == NULL) //found broken link here, so add it to the list of broken links and decrease outdegree by 1
					{
						add_broken_link(adjacency_list[i]->links_out[j]);
						adjacency_list[i]->increaseOut(-1);
						continue;
					}
					else
					{
						temp->increaseIn(1);
					}
				}
			}
		}
	}
	
	for(int i = 0; i < 512; i++)//set sink boolean value
	{
		if(adjacency_list[i] == NULL)
			break;
		else if(adjacency_list[i]->outdegree == 0)
		{
			add_sink_link(adjacency_list[i]->id);
		}
	}
}

void GraphContainer::add_broken_link(string link_name)
{
	for(int i = 0; i<512; i++)
	{
		if(broken_links[i] == "")
		{
			broken_links[i] = link_name;
			return;
		}
	}
}

void GraphContainer::add_sink_link(string link_name)
{
	for(int i = 0; i<512; i++)
	{
		if(sink_links[i] == "")
		{
			sink_links[i] = link_name;
			return;
		}
	}
}

bool GraphContainer::is_broken_link(string link_name)
{
	for(int i = 0; i<512; i++)
	{
		if(broken_links[i] == link_name)
			return true;
		else if(broken_links[i] == "")
			return false;
	}
	return false;
}

void GraphContainer::rank_output(string filename)
{
	ofstream fout;
	fout.open(filename.c_str());
	if(fout.fail())
		return;
	
	sort_broken_links();
	sort_adjacency_list();
	sort_sink_links();
	
	for(int i = 0; i<5; i++) //only output top 5, since its sorted just until i<5 is fine
	{
		if(adjacency_list[i] == NULL)
			break;
		else
			fout << adjacency_list[i]->id << " " << adjacency_list[i]->indegree << endl;
	}
	
	fout << endl;
	
	for(int i = 0; i<512; i++)
	{
		if(broken_links[i] == "" && i == 0)
		{
			fout << "No Broken Links" << endl;
			break;
		}
		else if(broken_links[i] == "")
			break;
		else
			fout << broken_links[i] << " Broken Link" << endl;
	}
	
	fout << endl;
	
	for(int i = 0; i<512; i++)
	{
		if(sink_links[i] == "" && i == 0)
		{
			fout << "No Sinks" << endl;
			break;
		}
		else if(sink_links[i] == "")
			break;
		else
			fout << sink_links[i] << " Sink" << endl;
	}
}

void GraphContainer::sort_broken_links()
{
	for(int i = 0; i<512; i++)
	{
		if(i != 511)
		{
			if(broken_links[i+1] == "")
				return;
		}
		
		for(int j = 0; j<512; j++)
		{
			if(j != 511)
			{
				if(broken_links[j+1] == "")
					break;
			}
			
			if(strcmp(broken_links[j].c_str(), broken_links[j+1].c_str()) > 0)
			{
				string temp = broken_links[j];
				broken_links[j] = broken_links[j+1];
				broken_links[j+1] = temp;
			}
		}
	}
	return;
}

void GraphContainer::sort_adjacency_list() //sorts adjacency list by indegree for outputting purposes.
{
	for(int i = 0; i<512; i++)
	{
		if(i != 511)
		{
			if(adjacency_list[i+1] == NULL)
				return;
		}
		for(int j = 0; j<512; j++)
		{
			if(adjacency_list[j+1] == NULL)
				break;
			if(adjacency_list[j]->indegree == adjacency_list[j+1]->indegree)
			{
				if(strcmp(adjacency_list[j]->id.c_str(), adjacency_list[j+1]->id.c_str()) > 0)
				{
					Vertex *temp = adjacency_list[j];
					adjacency_list[j] = adjacency_list[j+1];
					adjacency_list[j+1] = temp;
				}
			}
			else if(adjacency_list[j]->indegree < adjacency_list[j+1]->indegree)
			{
				Vertex *temp = adjacency_list[j];
				adjacency_list[j] = adjacency_list[j+1];
				adjacency_list[j+1] = temp;
			}
		
		}
	}
}

void GraphContainer::sort_sink_links()
{
	for(int i = 0; i<512; i++)
	{
		if(i != 511)
		{
			if(sink_links[i+1] == "")
				return;
		}
		
		for(int j = 0; j<512; j++)
		{
			if(j != 511)
			{
				if(sink_links[j+1] == "")
					break;
			}
			
			if(strcmp(sink_links[j].c_str(), sink_links[j+1].c_str()) > 0)
			{
				string temp = sink_links[j];
				sink_links[j] = sink_links[j+1];
				sink_links[j+1] = temp;
			}
		}
	}
	return;
}

void GraphContainer::dijkstra_calculate(string vertex_name)
{

}

void GraphContainer::dijkstra_output()
{

}
