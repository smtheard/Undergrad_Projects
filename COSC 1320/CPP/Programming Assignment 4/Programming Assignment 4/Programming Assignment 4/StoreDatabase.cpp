//StoreDatabase.cpp programming assignment 4
//cpp file for programming assignment 4
//Stefan Theard
//7/1/2013
#include <iostream>
#include <string>
#include "Video.h"
#include "Customer.h"
#include "StoreDatabase.h"
#include <fstream>


using namespace std;


bool StoreDatabase::checkOut(string videoName, int id)
{
	int customerlocation = -1;
	for(int i = 0; i<200; i++)
	{
		if(customer[i].getId() == id)
		{
			customerlocation = i;
			break;
		}
	}

	if(customerlocation == -1)
		return false;

	for(int i = 0; i<NUM_VIDEOS; i++)
	{
		if(video[i].getTitle() == videoName)
		{
			video[i].checkOut();
			return customer[customerlocation].checkOut(video[i]);
		}
	}
	return false;
}

bool StoreDatabase::checkIn(string videoName, int id)
{
	Video nullVid;
	int customerlocation = -1;
	for(int i = 0; i<200; i++)
	{
		if(customer[i].getId() == id)
		{
			customerlocation = i;
			break;
		}
	}

	if(customerlocation == -1)
		return false;

	for(int i = 0; i < 15; i++)
	{
		if(customer[customerlocation].videosRented[i].getTitle() == videoName)
		{
			for(int j = 0; i < NUM_VIDEOS; j++)
			{
				if(video[i].getTitle() == videoName)
				{
					video[i].checkIn();
					return customer[customerlocation].checkIn(videoName, nullVid);
				}
			}
		}
	}
	return false;
}	

bool StoreDatabase::createDatabase(string fileName)
{
	ifstream fin;
	
	try
	{
		fin.open(fileName);
		if(!fin.is_open())
		{
			throw -1; //TODO : register error when failbit is set
		}
	}
	catch(int e)
	{
		return false;
	}
	

	int  numberOfCopies, id; 
	string title, star1, star2, producer, director, productionCo, fname, lname, numVideosString, numberOfCopiesString;

	getline(fin, numVideosString);
	NUM_VIDEOS = atoi(numVideosString.c_str());

	for(int i = 0; i<NUM_VIDEOS; i++)
	{
		getline(fin, title); 
		getline(fin, star1);
		getline(fin, star2);
		getline(fin, producer);
		getline(fin, director);
		getline(fin, productionCo);

		getline(fin, numberOfCopiesString);
		numberOfCopies = atoi(numberOfCopiesString.c_str());

		video[i].setTitle(title);
		video[i].setStar1(star1);
		video[i].setStar2(star2);
		video[i].setProducer(producer);
		video[i].setDirector(director);
		video[i].setProductionCo(productionCo);
		video[i].setCopiesInStock(numberOfCopies);


	}

	int i = 0;
	while(fin >> fname && fin >> lname && fin >> id) //still some weird issue here on the 4th iteration.
	{
		customer[i].setFname(fname);
		customer[i].setLname(lname);
		customer[i].setId(id);
		i++;
	}

	fin.close();
	return true;
}


bool StoreDatabase::findVideo(string videoName)	
{
	for(int i = 0; i < NUM_VIDEOS; i++)
	{
		if(video[i].getTitle() == videoName)
		{
			video[i].showDetails();
			return true;
		}
	}
	return false;
}

bool StoreDatabase::displayVideoList()		
{
	int i = 0;
	while(video[i].getTitle() != "")
	{
		video[i].showDetails();
		i++;
	}
	if(i == 0)
		return false;
	else
		return true;
}

bool StoreDatabase::findCustomer(int id)	
{
	for(int i = 0; i < 200; i++)
	{
		if(customer[i].getId() == id)
		{
			customer[i].displayInfo();
			return true;
		}
	}
	return false;
}

bool StoreDatabase::listAllCheckedOut()	
{
	int i = 0;
	while(customer[i].getFname() != "")
	{
		customer[i].displayInfo();
		i++;
	}
	if(i == 0)
		return false;
	else
		return true;
}

