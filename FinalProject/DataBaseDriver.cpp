
/**
@file DataBaseDriver.cpp
@Purpose: implement data management
@partner's score 3
@author PengWei & Tiffany Liew
@version 1.1 11/21/17
*/
#include"DataBaseDriver.h"

DataBaseDriver::DataBaseDriver() {}

DataBaseDriver::DataBaseDriver(const char* fileName) 
{
	std::fstream in;
	in.open(fileName);
	Book person;	
	
	while (in >> person)
	{
		nameTree.add(person.getName(),person);
		birthdayTree.add(person.getDate(),person);
		if (in.eof()) break;
	}
	in.close();
}

//Memory stack allocated, empty descructor
DataBaseDriver::~DataBaseDriver() {}

void DataBaseDriver::postOrderProcessByName(const char* fileName)
{
	std::ofstream out;
	out.open(fileName);	
	postWriteHelper(out, nameTree.getroot());	
	out.close();
}

void DataBaseDriver::postWriteHelper(std::ofstream& out, const BinaryNode<std::string, People>* treePtr)
{
	if (treePtr != nullptr)
	{
		postWriteHelper(out, treePtr->getLeftChildPtr());
		postWriteHelper(out, treePtr->getRightChildPtr());
		People theItem = treePtr->getItem();
		out << theItem<<std::endl;
	}
}


void DataBaseDriver::breadthFirstProcessByBirthday(const char* fileName)
{
	std::ofstream out;
	out.open(fileName);
	int h = birthdayTree.getHeight();
	int i;
	for (i = 1; i <= h; i++)		
		breadthFirstProcessByBirthdayHelper(out,birthdayTree.getroot(),i);

	out.close();
}

void DataBaseDriver::breadthFirstProcessByBirthdayHelper(std::ofstream& out, BinaryNode<Birthday, People>* treePtr, int level)
{
	if (treePtr != nullptr)
	{
		if (level == 1)
		{
			People  theItem = treePtr->getItem();
			out << theItem<<std::endl;
		}
		else if (level > 1)
		{
			breadthFirstProcessByBirthdayHelper(out, treePtr->getLeftChildPtr(), level - 1);
			breadthFirstProcessByBirthdayHelper(out, treePtr->getRightChildPtr(), level - 1);
		}
	}
}


