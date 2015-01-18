//Video.cpp programming assignment 4
//cpp file for programming assignment 4
//Stefan Theard
//7/1/2013
#include <iostream>
#include <string>
#include "Video.h"

using namespace std;


Video::Video()
{
	title = "";
	star1 = "";
	star2 = "";
	producer = "";
	director = "";
	productionCo = "";
	copiesInStock = 0;
}

void Video::checkOut()
{
	copiesInStock--;
}

void Video::checkIn()
{
	copiesInStock++;
}

void Video::showDetails()
{
	cout << "Title: " << title << endl
		 << "Stars: " << star1 << " & " << star2 << endl
		 << "Producer: " << producer << endl
		 << "Director: " << director << endl
		 << "Production Company: " << productionCo << endl
		 << "Copies in stock: " << copiesInStock << endl;
}

//mutators
void Video::setTitle(string newTitle) {title = newTitle;}

void Video::setStar1(string newStar) {star1 = newStar;}

void Video::setStar2(string newStar) {star2 = newStar;}

void Video::setProducer(string newProducer) {producer = newProducer;}

void Video::setDirector(string newDirector) {director = newDirector;}

void Video::setProductionCo(string newProductionCo) {productionCo = newProductionCo;}

void Video::setCopiesInStock(int numberOfCopies) { copiesInStock = numberOfCopies; }

//accessors
string Video::getTitle() { return title; }