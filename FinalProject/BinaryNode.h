/**
@file BinaryNode.h
@Purpose: head file of the BinaryNode ADT.
@partner's score 3
@author PengWei & Tiffany Liew
@version 1.1 11/21/17
*/
#pragma once 
#ifndef _BINARY_NODE
#define _BINARY_NODE

#include "Book.h"

template < typename KeyType, typename ItemType>
class BinaryNode
{
	private:
		KeyType key;
		ItemType item; // Data portion
		BinaryNode<KeyType,ItemType>* leftChildPtr; // Pointer to left child
		BinaryNode<KeyType,ItemType>* rightChildPtr; // Pointer to right child
	public:
		BinaryNode();
		BinaryNode(const KeyType& aKey, const ItemType& anItem) ;
		BinaryNode(const KeyType& aKey, const ItemType& anItem,BinaryNode<KeyType,ItemType>* leftPtr,BinaryNode<KeyType,ItemType>* rightPtr);
		~BinaryNode();
		void setItem(const ItemType& anItem);
		void setKey(const KeyType& aKey);
		ItemType getItem() const;
		KeyType getKey() const;
		bool isLeaf() const;
		BinaryNode<KeyType,ItemType>* getLeftChildPtr() const;
		BinaryNode<KeyType,ItemType>* getRightChildPtr() const;
		void setLeftChildPtr(BinaryNode<KeyType,ItemType>* leftPtr);
		void setRightChildPtr(BinaryNode<KeyType,ItemType>* rightPtr);
}; // end BinaryNode

template < typename KeyType, typename ItemType>
BinaryNode<KeyType, ItemType>::BinaryNode() {}


template < typename KeyType, typename ItemType>
BinaryNode<KeyType, ItemType>::BinaryNode(const KeyType& aKey, const ItemType& anItem) :key(aKey), item(anItem), leftChildPtr(nullptr), rightChildPtr(nullptr) {}



template < typename KeyType, typename ItemType>
BinaryNode<KeyType, ItemType>::BinaryNode(const KeyType& aKey, const ItemType& anItem, BinaryNode<KeyType, ItemType>* leftPtr, BinaryNode<KeyType, ItemType>* rightPtr)
	: key(aKey), item(anItem), leftChildPtr(leftPtr), rightChildPtr(rightPtr) {}



template < typename KeyType, typename ItemType>
BinaryNode<KeyType, ItemType>::~BinaryNode() {}



template < typename KeyType, typename ItemType>
void BinaryNode<KeyType, ItemType>::setItem(const ItemType& anItem)
{
	item = anItem;
}


template < typename KeyType, typename ItemType>
void BinaryNode<KeyType, ItemType>::setKey(const KeyType& aKey) { key = aKey; }


template < typename KeyType, typename ItemType>
ItemType BinaryNode<KeyType, ItemType>::getItem() const { return item; }


template < typename KeyType, typename ItemType>
KeyType BinaryNode<KeyType, ItemType>::getKey() const { return key; }


template < typename KeyType, typename ItemType>
bool BinaryNode<KeyType, ItemType>::isLeaf() const
{
	return (rightChildPtr==nullptr&&leftChildPtr==nullptr);
}


template < typename KeyType, typename ItemType>
BinaryNode<KeyType, ItemType>* BinaryNode<KeyType, ItemType>::getLeftChildPtr() const { return leftChildPtr; }


template < typename KeyType, typename ItemType>
BinaryNode<KeyType, ItemType>* BinaryNode<KeyType, ItemType>::getRightChildPtr() const { return rightChildPtr; }



template < typename KeyType, typename ItemType>
void BinaryNode<KeyType, ItemType>::setLeftChildPtr(BinaryNode<KeyType, ItemType>* leftPtr) { leftChildPtr = leftPtr; }


template < typename KeyType, typename ItemType>
void BinaryNode<KeyType, ItemType>::setRightChildPtr(BinaryNode<KeyType, ItemType>* rightPtr) { rightChildPtr = rightPtr; }


#endif


