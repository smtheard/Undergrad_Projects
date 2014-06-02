#include <iostream>
#include <iomanip>
#include <string>
#include "Parser.h"

using namespace std;

int main(int argc, char *argv[])
{
	if ( argc != 2 )
	{
		cout<< "No file input or too many arguments!" << endl;
		return -1;
	}
	cout << argv[1] << endl;
	Parser parser(argv[1], ';');
	char* variable;
	variable = parser.clean(variable);
	cout << variable;
	
	system("PAUSE");
	return 0;
}