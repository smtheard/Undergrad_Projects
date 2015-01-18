//MenuView.cpp programming assignment 4
//cpp file for programming assignment 4
//Stefan Theard
//7/1/2013
#include <iostream>


#include "MenuView.h"

using namespace std;

int MenuView::initMenu()	
{
	int userin = 0;
	cout <<"*** Video Store Program *** " <<endl
		 << "1. Check out video " << endl
		 << "2. Check in video " << endl
		 << "3. Initialize video & customer database " << endl
		 << "4. Find video in database " << endl
		 << "5. Display all videos in database " << endl
		 << "6. Find customer in customer database " << endl
		 << "7. List all videos currently checked out " << endl
		 << "9. Exit Program " << endl;
	cin >> userin;
	return userin;
}

void MenuView::getVideoAndId(string& userIn, int& id)
{
	cout <<"Enter video name: ";
	cin.ignore();
	getline(cin, userIn);
	cout<< "Enter customer ID: ";
	cin >> id;
}

void MenuView::getFileName(string& userIn)
{
	cout <<"Enter raw text data file name(default is \"Programming Assignment 4 Data.txt\"): ";
	cin.ignore();
	getline(cin, userIn);
}

void MenuView::getVideoName(string& userIn)
{
	cout << "Enter video name: ";
	cin.ignore();
	getline(cin, userIn);
}

void MenuView::getCustomerId(int& id)
{
	cout<< "Enter customer ID: ";
	cin >> id;
}

void MenuView::invalidEntry()
{
	cout << "Invalid Entry!" << endl;
}

void MenuView::fileError()
{
	cout << "Exception caught! File input error has occured" << endl;
}

void MenuView::checkError()
{
	cout << "Invalid video name or user id " << endl;
}

void MenuView::noInputYet()
{
	cout << "No database input yet! Please input the database text file and try again. " << endl;
}

void MenuView::videoNotFound()
{
	cout << "Video not found! Please try again. " << endl;
}

void MenuView::invalidId()
{
	cout << "Customer not found! Please try again. " << endl;
}

void MenuView::success()
{
	cout << "Successfully initialized database. Please proceed. " << endl;
}