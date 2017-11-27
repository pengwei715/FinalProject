/**
@file DataBaseDriver.h
@Purpose: head file of the DataBaseDriver.
@partner's score 3
@author PengWei & Tiffany Liew
@version 1.1 11/21/17
*/
#pragma once
#ifndef _DATA_BASE_DRIVER
#define _DATA_BASE_DRIVER


#include <iostream>
#include <istream>
#include <ostream>
#include <fstream>
#include <string>
#include "BinarySearchTree.h"
#include"HashTable.h"

class DataBaseDriver
{

	//data section one BST tree ordered by  and by birthday
	private:
		int count;		
		BinarySearchTree<std::string, Book>* authorTreePtr;
		HashTable* tablePtr;

	//helpers of writing into two files
	protected:		
		void postWriteHelper(std::ofstream & out, const BinaryNode<std::string, People>* treePtr);
		void breadthFirstProcessByBirthdayHelper(std::ofstream& out, BinaryNode<Birthday, People>* treePtr,int level);

	public:
		DataBaseDriver();
		//input data from the inputfile, and build two trees
		DataBaseDriver(const char* fileName);
		~DataBaseDriver();


		//write the data into two different files
		void postOrderProcessByName(const char * fileName);
		void breadthFirstProcessByBirthday(const char* fileName);

		//getter of two trees
		BinarySearchTree<std::string, People> getNametree() { return nameTree; }
		BinarySearchTree<Birthday, People>  getBirthdaytree() { return birthdayTree; }
};
#endif

