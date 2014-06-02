
/*private:
	char* argument;
	char delimiter;
	char* full_data;
	int input_size;
														personal reminder for variable and function names
public:
	Parser(char*, char); //contructor 2args
	char* clean(char*); // function to clean the argument and get filename
	void read_input(char* filename); // reads input from file given in argument
 */
#include <iostream>
#include <iomanip>
#include <string>
#include "Parser.h"
 
 using namespace std;
 
 Parser::Parser(char* argument, char delimiter)
 {
	this->argument = argument;
	this->delimiter = delimiter;
 }
 
 char* Parser::clean(char* variable)
 {
	int argument_length;
	
	for(argument_length = 0; this->argument[argument_length] != '\0'; argument_length++);
	
	cout << "inside of parser.clean" << endl;
	cout << " LENGTH: " <<  argument_length << endl;
 
	return variable;
 }
 
 void Parser::read_input(char* filename)
 {
	cout << filename;
	return;
 }