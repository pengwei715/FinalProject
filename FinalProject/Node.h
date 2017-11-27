/**
@file Node.h
Purpose: head file of the Node ADT.

@author PengWei & Tiffany Liew
@version 1.1 10/25/17
*/

#ifndef GUARD__NODE
#define GUARD__NODE

#include "Book.h"
class Node
{
	private:
		Book* item; // A data ItemType
		Node* next; //Pointer to next Node
		std::string key;//the unique key to identify this node
		int priority;
	public:
		Node();//default constructor
		Node(Book*&  anItem);//constructor
		Node(Book*&  anItem, Node* nextNodePtr);//constructor
		~Node();
  
		void setItem(Book* anItem);//setter for item
		void setNext(Node* nextNodePtr);//setter for pointer
		void setPriority(int num);
		Node*& getNext() ;//getter for pointer
		Book*& getItem()  ;//getter for item
		void setKey() ;
		std::string getKey() ;
		int getPriority();
		bool operator==(std::string akey) { return key== akey; }
}; //end Node

void Node::setKey()
{
	key = item->getAuthor();
}

std::string Node::getKey()
{
	return key;
}

int Node::getPriority()
{
	return priority;
}

void Node::setPriority(int num)
{
	priority = num;	
}

Node::~Node() { delete item; }

Node::Node()
{
	item= new Book; // A data ItemType
	next = nullptr; //Pointer to next Node
	key="";//the unique key to identify this node
	priority=0;

} // end default constructor


Node::Node(Book*& anItem) : item(anItem), next(nullptr),key(anItem->getAuthor()),priority(0)
{


} // end constructor

Node::Node(Book*& anItem, Node* nextNodePtr) : item(anItem), next(nextNodePtr)
{
} //end constructor

void Node::setItem(Book*  anItem)
{
	item = anItem;
} // end setItem

void Node::setNext(Node* nextNodePtr)
{
	next = nextNodePtr;
} // end setNext

Book*& Node::getItem() 
{
	return item;
} // end getItem

Node*& Node::getNext() 
{
	return next;
} // end getNext


#endif
