//VideoStoreController.h programming assignment 4
//.h file for programming assignment 4
//Stefan Theard
//7/1/2013
#include <iostream>
#include <string>
#include "StoreDatabase.h"

using std::string;

class VideoStoreController
{
private:
	StoreDatabase storeDatabase;
public:
	bool checkOut(string videoName, int id);		//uc1
	bool checkIn(string videoName, int id);			//uc2
	bool createDatabase(string fileName);			//uc3
	bool findVideo(string videoName);				//uc4
	bool displayVideoList();						//uc5
	bool findCustomer(int id);						//uc6
	bool listAllCheckedOut();						//uc7
};
