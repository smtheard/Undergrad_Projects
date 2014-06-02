class Parser
{
private:
	char* argument;
	char delimiter;
	char* full_data;
	int input_size;
	
public:
	Parser(char* argument, char delimiter); //contructor 2args
	char* clean(char* argument); // function to clean the argument and get filename
	void read_input(char* filename); // reads input from file given in argument
};