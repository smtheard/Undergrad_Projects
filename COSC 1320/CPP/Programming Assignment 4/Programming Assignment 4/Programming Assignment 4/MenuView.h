//MenuView.h programming assignment 4
//.h file for programming assignment 4
//Stefan Theard
//7/1/2013
#include <iostream>
#include <string>
using std::string;
class MenuView
{
public:
	int initMenu();
	void getVideoAndId(string& userIn, int& id);
	void getFileName(string& userIn);
	void getVideoName(string& userIn);
	void getCustomerId(int& id);
	void invalidEntry();
	void fileError();
	void checkError();
	void noInputYet();
	void videoNotFound();
	void invalidId();
	void success();
};