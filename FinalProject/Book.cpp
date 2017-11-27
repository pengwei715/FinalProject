/**
@file People.h
@Purpose: head file of the people class 
@partner's score 3
@author PengWei & Tiffany Liew
@version 1.1 11/21/17
*/
#include "Book.h"

void Book::setTitle(std::string aTitle)
{
	title = aTitle;
}
void Book::setAuthor(std::string anAuthor)
{
	author = anAuthor;
}
void Book::setISBN(std::string aISBN)
{
	ISBN = aISBN;
}
void Book::setEdition(std::string anEdition)
{
	edition = anEdition;
}

//getters
std::string Book::getTitle()
{
	return title;
}
std::string Book::getAuthor()
{
	return author;
}
std::string Book::getISBN()
{
	return ISBN;
}
std::string Book::getEdition()
{
	return edition;
}

//Global stream operators overloading
std::istream& operator>>(std::istream& is, Book& aBook) 
{
	std::string temp;
	std::getline(is, temp);
	aBook.setTitle(temp);
	std::getline(is, temp);
	aBook.setAuthor(temp);
	std::getline(is, temp);
	aBook.setISBN(temp);
	std::getline(is, temp);
	aBook.setEdition(temp);
	return is;
}

std::ostream& operator<<(std::ostream& os,  Book& aBook)
{
	os << aBook.getTitle() << '\n' << aBook.getAuthor() << '\n' << aBook.getISBN() << '\n' << aBook.getEdition() << '\n'<<'\n';
	return os;
}