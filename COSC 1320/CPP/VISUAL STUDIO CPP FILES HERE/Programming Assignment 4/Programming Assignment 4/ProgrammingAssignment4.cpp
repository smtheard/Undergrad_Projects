//ProgrammingAssignment4.cpp programming assignment 4
//cpp file for programming assignment 4
//Stefan Theard
//7/1/2013
#include <iostream>
#include <string>
#include <fstream>
#include "MenuView.h"
#include "VideoStoreController.h"

using namespace std;

int main()
{
	int id = 0, menuIn = 0;
	string stringIn = "";
	MenuView view;
	VideoStoreController controller;
	while(menuIn != 9)
	{
		menuIn = view.initMenu();
	
		switch(menuIn)
		{
		case 1: 
			view.getVideoAndId(stringIn, id);
			if(!controller.checkOut(stringIn, id))
				view.checkError();
			break;
		case 2:
			view.getVideoAndId(stringIn, id);
			if(!controller.checkIn(stringIn, id))
				view.checkError();
			break;
		case 3:
			view.getFileName(stringIn);
			if(!controller.createDatabase(stringIn))
				view.fileError();
			else
				view.success();
			break;
		case 4:
			view.getVideoName(stringIn);
			if(!controller.findVideo(stringIn))
				view.videoNotFound();
			break;
		case 5:
			if(!controller.displayVideoList())
				view.noInputYet();
			break;
		case 6:
			view.getCustomerId(id);
			if(!controller.findCustomer(id))
				view.invalidId();
			break;
		case 7:
			controller.listAllCheckedOut();
			break;
		case 9:
			break;
		default:
			view.invalidEntry();
			break;
		}
		
	}
	return 0;
}
