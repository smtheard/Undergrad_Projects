//Video.h programming assignment 4
//.h file for programming assignment 4
//Stefan Theard
//7/1/2013
#ifndef Video_H
#define Video_H

#include <iostream>
#include <string>

using namespace std;

class Video
{
private:
	string title, star1, star2, producer, director, productionCo;
	int copiesInStock;
public:
	Video();
	void checkOut();
	void checkIn();
	void showDetails();

	//mutators
	void setTitle(string newTitle);
	void setStar1(string newStar);
	void setStar2(string newStar);
	void setProducer(string newProducer);
	void setDirector(string newDirector);
	void setProductionCo(string newProductionCo);
	void setCopiesInStock(int numberOfCopies);

	//accessors
	string getTitle();
};
#endif