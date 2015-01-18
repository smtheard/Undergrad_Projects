//Customer.h programming assignment 4
//.h file for programming assignment 4
//Stefan Theard
//7/1/2013
#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <iostream>
#include <string>
#include "Video.h"

using std::string;

class Customer
{
private:
	string fname, lname;
	int id;

public:
	Customer();
	Video videosRented[15];
	string getFname();
	void setFname(string newName);
	string getLname();
	void setLname(string newLname);
	int getId();
	void setId(int newId);
	void displayInfo();
	bool checkOut(Video video);
	bool checkIn(string title, Video video);
};
#endif