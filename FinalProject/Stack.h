/**
@file Link.h
@Purpose: head file of the Stack ADT it allows puch, pop,peek,isempty.

@author PengWei & Tiffany Liew
@version 1.1 10/25/17
*/

#ifndef GUARD__STACK
#define GUARD__STACK

#include "Link.h"

template<class ItemType>
class Stack:protected Link <ItemType>
{

public:
	Stack<ItemType>() {};
	~Stack<ItemType>() {};
	/** Adds a new entry to the top of this stack.
    @post If the operation was successful, newEntry is at the top of the stack.
    @param newEntry The object to be added as a new entry.
    @return True if the addition is successful or false if not. */
    bool push(const ItemType& newEntry) ;

    /** Removes the top of this stack.
    @post If the operation was successful, the top of the stack has been removed.
    @return True if the removal is successful or false if not. */
    bool pop();

    /** Returns the top of this stack.
    @pre The stack is not empty.
    @post The top of the stack has been returned, and the stack is unchanged.
    @return The top of the stack. */
    ItemType peek() const;


	/**get the number of items in the stack
    @post the stack is unchanged.
    @return number of items in the stack.
	*/
	int getSize()const;

	/**check if the stack is empty or not
	@post the stack is unchanged.
    @return true if the stack is empty, return false if the stack is not empty.*/
	bool isEmpty() const;

	/*Show all the items in the stack
	@post the stack is unchanged.*/
	void show() ;
}; 

template<class ItemType>
bool Stack <ItemType>::push(const ItemType& newEntry)
{
	return this->insertStart(newEntry);
}


template<class ItemType>
bool Stack <ItemType>::pop()
{
	if (this->getHead() == nullptr)
	{
		throw std::underflow_error("error, nothing to pop!");
	}
	else
	{
		std::cout << this->peek() << " will be poped " << std::endl;
		system("pause");
		this->setHead(this->getHead()->getNext());
		this->setCount(this->getCount()-1);
		return true;
	}
}


template<class ItemType>
ItemType  Stack<ItemType>::peek() const
{
	if (this->getHead() == nullptr)
		throw std::underflow_error("The stack don't have any item!");
	else  return this->getHead()->getItem();
}

template<class ItemType>
inline int Stack<ItemType>::getSize() const
{
	return this->getCurrentSize();
}

template<class ItemType>
inline bool Stack<ItemType>::isEmpty() const
{
	return !this->getSize();
}

template<class ItemType>
void Stack<ItemType>::show()
{
	Node<ItemType>* tempPtr = this->getHead();
	std::cout << "======================" << std::endl;
	while (tempPtr != 0)
	{
		
		std::cout << tempPtr->getItem() << std::endl;
		tempPtr = tempPtr->getNext();
	}
	std::cout << "======================" << std::endl;
	system("pause");
}

#endif
