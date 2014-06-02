//Customer.cpp programming assignment 4
//cpp file for programming assignment 4
//Stefan Theard
//7/1/2013
#include "Customer.h"
#include <iostream>
#include <string>


using namespace std;

Customer::Customer()
{
	fname = "";
	lname = "";
	id = -1;
}

string Customer::getFname() { return fname; }

void Customer::setFname(string newName) { fname = newName; }

string Customer::getLname() { return lname; }

void Customer::setLname(string newLname) { lname = newLname; }

int Customer::getId() { return id; }

void Customer::setId(int newId) { id = newId; }

void Customer::displayInfo() 
{
	cout << "Name: " << fname << " " << lname << endl
		 << "ID: " << id << endl
		 <<"Videos Rented: ";
	for(int i = 0; i < 15; i++)
	{
		if(videosRented[i].getTitle() != "")
		{
			cout << videosRented[i].getTitle() << ", ";
		}
	}
	cout << endl << endl;
}

bool Customer::checkOut(Video video)
{
	for(int i = 0; i < 15; i++)
	{
		if(videosRented[i].getTitle() == video.getTitle())
		{
			cout << "Customer already has that video." << endl;
			return false;
		}
	}
	for(int i = 0; i < 15; i++)
	{
		if(videosRented[i].getTitle() == "")
		{
			videosRented[i] = video;
			return true;
		}
	}
	cout << "Customer has 15 videos and cannot rent anymore." << endl;
	return false;
}

bool Customer::checkIn(string title, Video video)
{
	for(int i = 0; i < 15; i++)
	{
		if(videosRented[i].getTitle() == title)
		{
			videosRented[i] = video;
			return true;
		}
	}
	cout << "Customer " << id << " does not currently have the video " << title << endl;
	return false;
}


