//VideoStoreController.cpp programming assignment 4
//cpp file for programming assignment 4
//Stefan Theard
//7/1/2013
#include <string>
#include "VideoStoreController.h"

using std::string;


bool VideoStoreController::checkOut(string videoName, int id)
{
	return storeDatabase.checkOut(videoName, id);
}
bool VideoStoreController::checkIn(string videoName, int id)
{
	return storeDatabase.checkIn(videoName, id);
}
bool VideoStoreController::createDatabase(string fileName)
{
	return storeDatabase.createDatabase(fileName);
}
bool VideoStoreController::findVideo(string videoName)
{
	return storeDatabase.findVideo(videoName);
}
bool VideoStoreController::displayVideoList()
{
	return storeDatabase.displayVideoList();
}
bool VideoStoreController::findCustomer(int id)
{
	return storeDatabase.findCustomer(id);
}
bool VideoStoreController::listAllCheckedOut()
{
	return storeDatabase.listAllCheckedOut();
}