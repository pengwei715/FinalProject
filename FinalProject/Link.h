/**
@file Link.h
Purpose: head file of the singly linked list ADT

@author PengWei & Tiffany Liew
@version 1.1 10/25/17
*/

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


#ifndef GUARD__LINK
#define GUARD__LINK
#include "Node.h"

class Link
{
	private:
		Node* headPtr; // Pointer to first Node
		int itemCount; //Current count of items
	public:
		Link();
		virtual ~Link();   //Destructor should be virtual
		int getCurrentSize() const;//get the current size of the list
		bool isEmpty() const;//check the list is empty or not
		bool insertStart(Book* &newItem);
		Node* getPointerTo(std::string key);
		Book* findItem(std::string key);
		bool removeFromAnywhere(std::string key);
		bool removeFirst();

		void showItems() const;
		void clear();

		/**check wether or not the item is in the list
		@pre The linked list is not empty
		@post nothing changed
		@return ture if the item exisit**/
		//bool contains(std::string) ;

		bool sortByhistory();

		Node* getHead() const { return headPtr; } //getter for head pointer
		void setHead( Node* aPtr) { headPtr = aPtr; }//setter for head pointer
		void setCount( int num) { itemCount = num; }//setter for curre
		bool pop();
		Book* peek() const;

}; 

Link::Link(): headPtr(nullptr), itemCount(0)
{}

bool Link::insertStart(Book*&newItem)
{
	Node* newNodePtr = new Node;
	newNodePtr->setItem(newItem);
	newNodePtr->setNext(headPtr); // New node points to chain
	newNodePtr->setKey();
	newNodePtr->setPriority(0);
	headPtr = newNodePtr;       // New node is now first node
	itemCount++;

	return true;
}  

Link:: ~Link()
{
	clear();
}

bool Link::isEmpty() const
{
	return itemCount == 0;
} 

int Link::getCurrentSize() const
{
	return itemCount;
}


bool Link::removeFromAnywhere(std::string key)
{
	Node* deleteNodePtr = getPointerTo(key);
	Node* prePtr=headPtr;
	bool canRemoveItem = !isEmpty() && (deleteNodePtr != nullptr);
	if (canRemoveItem)
	{
		while (prePtr->getNext() != deleteNodePtr)
		{
			prePtr = prePtr->getNext();
		}
		
		prePtr->setNext(deleteNodePtr->getNext());
		deleteNodePtr->setNext(nullptr);
		delete deleteNodePtr;
		deleteNodePtr = nullptr;
		itemCount--;
	} 
	return canRemoveItem;
}

Node* Link::getPointerTo(std::string key) 
{
	bool found = false;
	Node * curPtr = headPtr;
	while (!found && (curPtr != nullptr))
	{
		if (key == curPtr->getKey())
		{
			found = true;
			curPtr->setPriority(curPtr->getPriority() + 1);
			return curPtr;
		}
		else
			curPtr = curPtr->getNext();
	}
	return nullptr;
}

bool Link::removeFirst()
{
	Node* nodeToDeletePtr = headPtr;
	headPtr = headPtr->getNext();
	// Return node to the system
	nodeToDeletePtr->setNext(nullptr);
	delete nodeToDeletePtr;
	nodeToDeletePtr = nullptr;
	itemCount--;

	return true;
}

void Link::clear()
{
	while (headPtr != nullptr)
	{
		Node* nodeToDeletePtr = headPtr;
		headPtr = headPtr->getNext();
		nodeToDeletePtr->setNext(nullptr);
		delete nodeToDeletePtr;
	} 
	itemCount = 0;
} 

bool Link::sortByhistory()
{
	Node* curPtr = headPtr->getNext();
	Node* nextPtr = curPtr->getNext();
	if (nextPtr->getPriority() > curPtr->getPriority())
	{
		Book* tempPtr = nullptr;
		tempPtr = nextPtr->getItem();
		nextPtr->setItem(curPtr->getItem());
		curPtr->setItem(tempPtr);
		int tempnum = curPtr->getPriority();
		curPtr->setPriority(nextPtr->getPriority());
		nextPtr->setPriority(tempnum);
		curPtr->setKey();
		nextPtr->setKey();
		nextPtr = nextPtr->getNext();
	}
	return true;
 }

Book* Link::findItem(std::string key)
{
	Node* find = getPointerTo(key);
	if (find != nullptr)
	{
		if (find != headPtr)
		{
			Node* newNodePtr = new Node(find->getItem());
			newNodePtr->setPriority(find->getPriority());
			newNodePtr->setNext(headPtr); // New node points to chain
			headPtr = newNodePtr;
			Node* curPtr = headPtr;
			while (curPtr->getNext() != find)
			{
				curPtr = curPtr->getNext();
			}
			curPtr->setNext(find->getNext());			
		}
		sortByhistory();
		return headPtr->getItem();
	}
	else return nullptr;
}


 void  Link::showItems() const
 {
	 Node * curPtr = headPtr;
	 while (curPtr != nullptr)
	 {
	 std::cout << *(curPtr->getItem()) << std::endl;
	 curPtr = curPtr->getNext();
	 }
 }


 bool Link::pop()
 {
	 if (this->getHead() == nullptr)
	 {
		 throw std::underflow_error("error, nothing to pop!");
	 }
	 else
	 {
		 std::cout << *(this->peek()) << " will be poped " << std::endl;
		 delete this->peek();
		 this->setHead(this->getHead()->getNext());
		 this->setCount(this->getCurrentSize() - 1);
		 return true;
	 }
 }


 Book*  Link::peek() const
 {
	 if (this->getHead() == nullptr)
		 throw std::underflow_error("The stack don't have any item!");
	 else  return this->getHead()->getItem();
 }



#endif
