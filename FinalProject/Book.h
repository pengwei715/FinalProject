/**
@file People.h
@Purpose: head file of the people.
@partner's score 3
@author PengWei & Tiffany Liew
@version 1.1 11/21/17
*/
#ifndef _BOOK
#define _BOOK

#include <iostream>
#include <istream>
#include <ostream>
#include <string>

class Book 
{
	private:
		std::string title;
		std::string author;
		std::string ISBN;
		std::string edition;
	public:

		Book() {};
		Book(std::string aTitle, std::string anAuthor,std::string aISBN,std::string edition) 
			:title(aTitle), author(anAuthor), ISBN(aISBN), edition(edition){};
		~Book() {};

		//setters
		void setTitle(std::string somedate) ;
		void setAuthor(std::string anAuthor);
		void setISBN(std::string aISBN);
		void setEdition(std::string anEdition);
		
		//getters
		std::string getTitle();
		std::string getAuthor();
		std::string getISBN();
		std::string getEdition();
		bool operator==(Book* right)const { return title== right->getTitle();}
		bool operator>(Book* right)const { return title > right->getTitle(); }
		bool operator<(Book* right)const { return title < right->getTitle(); }
};

#endif

//Global stream operators
std::istream& operator>>(std::istream& is, Book& aBook) ;
std::ostream& operator<<(std::ostream& os, Book& aBook) ;