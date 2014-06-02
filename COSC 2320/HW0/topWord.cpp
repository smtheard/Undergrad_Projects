#include <iostream>
#include <iomanip>
#include <cstring>
#include <fstream>
#include <cctype>

using namespace std;

class Parser
{
	private:
		char* argument;
		char delimiter;
		char* full_data;
		int input_size;
	
	public:
		Parser(char* argument, char delimiter); //contructor 2 parameters
		char* clean(); // function to clean the argument and get filename
		void read_input(char* filename, string database[]); // reads input from file given in argument
};

class Wordct
{
	public:
		string word;
		string raw_word; // used to maintain punctuation to display, however does not effect program logic.
		int count;
		Wordct(); //default constructor

};

class Database
{
	private:
		string input_database[512]; // arbitrary length to avoid memory issues
		string cleaned_database[512]; // arbitrary length to avoid memory issues
		Wordct word[512]; // arbitrary length to avoid memory issues
	public:
		Database(string db[]);
		void strip_punctuation(); //strips all punctuation and stores the words in cleaned_database
		void tolowercase();  //forces everything to lower-case and stores it in cleaned_database
		void find_word_counts(); //gets the words and word counts stored into the Wordct array
		void output_results(); //sorts the word array and outputs the most frequent word or words if multiple are tied for the #1 spot.
};

int main(int argc, char *argv[])
{
	if ( argc != 2 )
	{
		cout << endl << "No file input or too many arguments!" << endl;
		cout << "This program supports exactly one argument and it must be a .txt file." << endl;
		return -1;
	}
	Parser parser(argv[1], ';');
	char* cleaned_argument;
	string input_database[512]; //arbitrary size of array, just used to avoid memory problems
	
	cleaned_argument = parser.clean();
	parser.read_input(cleaned_argument, input_database);
	
	Database db(input_database); //calls Database constructor with 1 parameter that holds the database of all words in the input file.
	db.strip_punctuation();
	db.tolowercase();
	db.find_word_counts();
	db.output_results();
	
	delete cleaned_argument; //pointer memory clean-up
	cleaned_argument = NULL;
	return 0;
}

 Wordct::Wordct()
 {
	word = "";
	count = 0;
}

Parser::Parser(char* argument, char delimiter)
 {
	this->argument = argument;
	this->delimiter = delimiter;
 }
 
char* Parser::clean() //perfect working order, no errors (remove if edits occur)
 {
	int argument_length;
	char* cleaned_argument = new char[256]; //arbitrary [length] here so I can make sure to not get any memory issues
	
	//gets full argument length, this includes any delimiters and serves as support for multiple arguments.
	for(argument_length = 0; this->argument[argument_length] != '\0'; argument_length++);
	
	//cycles through the argument up until either the delimiter or '\0' are hit.
	for(int i = 0; argument[i] != '\0' && argument[i] != delimiter; i++) 
	{
		if(argument[i] == '=')
		{
			for(int j = 0; argument[i+j+1] != '\0' && argument[i+j+1] != delimiter; j++)	// TODO: add logic to handle multiple arguments.
			{
				cleaned_argument[j] = argument[i+j+1];
			}
			break;
		}
	}

	return cleaned_argument;
 }
 
 void Parser::read_input(char* filename, string database[]) //perfect working order, no errors (remove if edits occur)
 {
	ifstream fin;
	fin.open(filename);
	if(fin.fail()) //extra safety net to catch if given a file that is not in the same folder as the executable.
		cout << "There was an error opening your file, please try again.(This could be either a malformed argument or the .txt file you are searching for is not located in the same folder as the .exe of this program)" << endl;
	int i = 0;
	while(fin >> database[i]) // loops sending every word into an array of strings at position i.
		i++;
	
	fin.close();
	return;
 }
 
 
 Database::Database(string db[])  //perfect working order, no errors (remove if edits occur)
 {
	for(int i = 0; db[i] != "\0"; i++) //puts input data into the class Database's privately stored input_database string array
		input_database[i] = db[i];
	for(int i = 0; db[i] != "\0"; i++)
		cleaned_database[i] = db[i];
 }
 
 void Database::strip_punctuation() //simple function and re-usable code to remove all punctuation.
 {
	for(int i = 0; input_database[i] != "\0"; i++)
	{
		for(int j = 0; j<input_database[i].length(); j++)
		{
			 if(!isalpha(input_database[i].at(j)))
				cleaned_database[i].at(j) = ' ';
		}
	}	
 }
 
 void Database::tolowercase() //simple function and re-usable code to make everything in the database lowercase.
 {
	for(int i = 0; input_database[i] != "\0"; i++)
	{
		for(int j = 0; j<input_database[i].length(); j++)
		{
			 if(isupper(input_database[i].at(j)))
				cleaned_database[i].at(j) = tolower(input_database[i].at(j));
		}
	}
 }
 
 void Database::find_word_counts() //perfect working order, no errors (remove if edits occur)
 {
	bool alreadyExists = false;
	for(int i = 0; cleaned_database[i] != "\0"; i++)
	{
		for(int j = 0; cleaned_database[j] !="\0"; j++)//TODO: figure out this conditional, not sure if this is the correct route to take.
		{
			if(cleaned_database[i] == word[j].word) //if the word is already in the word array, this increases the count, and sets a conditional to true, and then breaks the loop
			{
				word[j].count++;
				alreadyExists = true;
				break;
			}
		}
		
		if(alreadyExists == true) //if the word alreadyexists, the loop skips anything below this if statement.
		{						  //if it doesn't exist, it goes down to the next for loop and puts it into the word array.
			alreadyExists = false;
			continue;
		}
		
		for(int j = 0; cleaned_database[j] != "\0"; j++) //inserts the word that is at cleaned_database[i] into the first open slot in the word array and increases the count.
		{
			if(word[j].word != "\0") // if the word is not a null character, skip anything below this and increment j.
				continue;
			word[j].word = cleaned_database[i];
			word[j].raw_word = input_database[i]; //stores the original un-cleaned version of the word, this is to keep things like "you're" with the apostrophe intact for displaying purposes.
			word[j].count++;
			break;
		}
	}
 }
 
void Database::output_results()
{
	int temp_int;
	string temp_string1;
	string temp_string2;
	//string orgnized_array[512];	 //might need something like this in the future, not sure.
	
	for(int i = 0; word[i].word != ""; i++) //basic descending order sort and swap, uses word.count for the order.
	{
		for(int j = 0; word[j].word != ""; j++)
		{
			if(word[j].count < word[j+1].count)
			{
				temp_int = word[j].count;
				temp_string1 = word[j].word;
				temp_string2 = word[j].raw_word;
				
				word[j].count = word[j+1].count;
				word[j].word = word[j+1].word;
				word[j].raw_word = word[j+1].raw_word;
				
				word[j+1].count = temp_int;
				word[j+1].word = temp_string1;
				word[j+1].raw_word = temp_string2;
			}
		}
	}
	
	for(int i = 0; word[i].word != ""; i++)
	{
		cout << "Result: " << word[i].word << "=" << word[i].count << endl;
		if(word[i].count > word[i+1].count)
			break;
	}
}

	
 