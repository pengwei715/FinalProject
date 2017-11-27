/**
@file HashTableNode.h
@Purpose: head file of the HashTableNode ADT.
@author PengWei & Tiffany Liew
@version 1.1 11/21/17
*/
#pragma once 
#ifndef _HASH_TABLE_NODE
#define _HASH_TABLE_NODE

#include "Link.h"

/* Project Option#1:
BST, Hash Table, and Self - Adjusting Linked Lists
1.Solve collisions using linked list resolution.
2.A self - adjusting list is like a regular list,
except that all insertions are performed at the front,
and when an element is accessed by a search, it is moved to the front of the list,
without changing the relative order of the other items.
The elements with highest access probability are expected to be close to the front.
3.Save data to file in hash table sequence.
4.Efficiency :
a.Load Factor
b.Longest Linked List
c.Average number of nodes in linked lists
*/


class HashTableNode
{
	private:
		int currentNum;
		std::string key;
		Book* item;
		Link* LinkedlistPtr; // Pointer to linkedlist
	public:
		HashTableNode();
		HashTableNode(Book* anItem);
		void clear();
		~HashTableNode();
		void setItem( Book* anItem);
		void setKey(std::string Key);
		Book* getItem(std::string aKey) ;
		std::string getKey();	
		Link* getlist();
		bool addItem(Book* item);
		bool removeItem(std::string key);
		void display();
		int getCurrentNum();
}; 

void HashTableNode::display()
{
	std::cout << *item << std::endl;
	if(LinkedlistPtr)
	LinkedlistPtr->showItems();
}

void HashTableNode::clear()
{
	delete LinkedlistPtr;
}


bool HashTableNode::addItem(Book* anItem)
{
	if (item == nullptr)
	{
		item = anItem;
		key = anItem->getAuthor();
		currentNum++;
	}
	else if (LinkedlistPtr == nullptr)
	{
		LinkedlistPtr = new Link;
		LinkedlistPtr->insertStart(anItem);
		currentNum++;

	}
	else
	{
		LinkedlistPtr->insertStart(anItem);
		currentNum++;
	}

	return true;

		
}

bool HashTableNode::removeItem(std::string akey)
{
	if (LinkedlistPtr)
	{
		if (akey == key)
		{
			item=nullptr;
			item = LinkedlistPtr->peek();
			key = item->getAuthor();
			LinkedlistPtr->pop();
			currentNum--;
			
		}
		else
		{
			LinkedlistPtr->removeFromAnywhere(akey);
			currentNum--;
		}
		return true;
	}
	else
	{
		if (akey == key)
		{
			item=nullptr;
			key = "";
			currentNum--;
			return true;
		}
		else 
		{
			std::cerr << "There is no item ";
			return false;
		}
	}
	
}

HashTableNode::HashTableNode() :item(nullptr), LinkedlistPtr(nullptr),currentNum(0){}

HashTableNode::HashTableNode(Book* anitem) :key(anitem->getAuthor()), item(anitem), LinkedlistPtr(nullptr) {}

 HashTableNode:: ~HashTableNode()
{
	clear();
}

void HashTableNode::setItem(Book* anItem)
{
	item = anItem;
}

void HashTableNode::setKey(std::string aKey) { key = aKey; }


Book* HashTableNode::getItem(std::string akey) 
{ 
	if (LinkedlistPtr)
	{
		if (akey == key)
		{
			return item;
		}
		else
		{
			return LinkedlistPtr->findItem(akey);
		}
	}
	else
	{
		if (akey == key)
		{
			return item;
		}
		else std::cerr << "There is no item ";
	}


}

std::string  HashTableNode::getKey()  { return key; }

int HashTableNode::getCurrentNum() { return currentNum; }
Link* HashTableNode::getlist(){ return LinkedlistPtr; }

#endif

