/**
@file Link.h
@Purpose: head file of the queue ADT

@author PengWei & Tiffany Liew
@version 1.1 10/25/17
*/

#ifndef GUARD__QUEUE
#define GUARD__QUEUE

#include "Link.h"

template<class ItemType>
class Queue :protected Link <ItemType>
{
	//enqueue, dequeue, front, rear, empty etc.
	public:
		Queue<ItemType>() {};
		~Queue<ItemType>() {};
		/** Adds a new entry to the rear of this Queue.
		@post If the operation was successful, newEntry is at the rear of the Queue.
		@param newEntry The object to be added as a new entry.
		@return True if the addition is successful  */
		bool enqueue(const ItemType& newEntry);

		/** Removes the front of this Queue.
		@post If the operation was successful, the front of the Queue has been removed.
		@return True if the removal is successful  */
		bool dequeue();

		/** Returns the front of this Queue.
		@pre The Queue is not empty.
		@post The front of the Queue has been returned, and the Queue is unchanged.
		@return The front of the Queue. */
		ItemType front() const;

		/** Returns the rear of this Queue.
		@pre The Queue is not empty.
		@post The rear of the Queue has been returned, and the Queue is unchanged.
		@return The rear of the Queue. */
		ItemType rear() const;

		int getSize()const;

		bool isEmpty() const;
		bool empty();

		void show();
};

template<class ItemType>
bool Queue <ItemType>::enqueue(const ItemType& newEntry)
{
	 this->insertEnd(newEntry);
	 return true;
}


template<class ItemType>
bool Queue <ItemType>::dequeue()
{
	if (this->getHead() == nullptr)
	{
		throw std::underflow_error("error, nothing to dequeue!");
	}
	else
	{
		std::cout << this->front() << " will be dequeued " << std::endl;
		system("pause");
		this->setHead(this->getHead()->getNext());
		this->setCount(this->getCount() - 1);
		return true;
	}
}


template<class ItemType>
ItemType  Queue<ItemType>::front() const
{
	if (this->getHead() == nullptr)
		throw std::underflow_error("The Queue don't have any item!");
	else  return this->getHead()->getItem();
}

template<class ItemType>
ItemType Queue<ItemType>::rear() const
{
	Node<ItemType>* curPtr =this->getHead();
	if (curPtr)
	{
		while (curPtr->getNext())
		{
			curPtr = curPtr->getNext();
		}
	return curPtr->getItem();

	}
	return ItemType();
}

template<class ItemType>
inline int Queue<ItemType>::getSize() const
{
	return this->getCurrentSize();
}

template<class ItemType>
inline bool Queue<ItemType>::isEmpty() const
{
	return !this->getSize();
}

template<class ItemType>
bool Queue<ItemType>::empty()
{
	this->clear();
	return true;
}

template<class ItemType>
void Queue<ItemType>::show()
{
	Node<ItemType>* tempPtr = this->getHead();
	std::cout << "======================" << std::endl;
	while (tempPtr != nullptr)
	{

		std::cout << tempPtr->getItem() << std::endl;
		tempPtr = tempPtr->getNext();
	}
	std::cout << "======================" << std::endl;
	system("pause");
}

#endif
