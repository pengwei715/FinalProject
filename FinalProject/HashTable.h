#ifndef HASH_H
#define HASH_H

#include "HashTableNode.h"
#include <iostream>
#include <string>


class HashTable 
{
	private:
		int TABLESIZE=29;
		int currentItemNum;
		int collisionCount;
		int itemNumInlongestlist;
		int indexOfLongestBucket;
		float averageNumberinLinklist;
		float loadFactor;
		HashTableNode* hashNodeArray;		
	public:
		HashTable();
		~HashTable();
		bool add(std::string keyValue, Book* object);
		void caculateStatus();
		void tabledisplay();
		Book *getData(std::string keyValue);
		bool removeData(std::string keyValue);
		int hashFunction(std::string& keyValue);		
};

HashTable::HashTable()
{
	hashNodeArray = new HashTableNode[TABLESIZE];
	itemNumInlongestlist = 0;
	collisionCount = 0;
	indexOfLongestBucket = 0;
	currentItemNum = 0;
	averageNumberinLinklist = 0;
	loadFactor = 0;
}
HashTable::~HashTable()
{
	for (int i = 0; i < TABLESIZE; i++)
	{
		if (hashNodeArray[i].getCurrentNum())
			hashNodeArray[i].clear();
	}
	delete[]hashNodeArray;
}

bool HashTable::add(std::string keyValue, Book* object)
{
	int index = hashFunction(keyValue);

	currentItemNum++;
	return hashNodeArray[index].addItem(object);
}

void HashTable::caculateStatus()
{
	int temp = 0, count = 0, temp2 = 0, temp3 = 0;
	for (int i = 0; i < TABLESIZE; i++)
	{
		if (hashNodeArray[i].getCurrentNum())
			temp3++;
		if (hashNodeArray[i].getlist())
		{
			if (hashNodeArray[i].getlist()->getCurrentSize() > temp2)
				temp2 = hashNodeArray[i].getlist()->getCurrentSize();
			temp = temp + hashNodeArray[i].getlist()->getCurrentSize();
			count++;
		}
	}
	collisionCount = temp;
	if (count != 0)
		averageNumberinLinklist = float(temp) / count;
	loadFactor = float(temp3) / TABLESIZE;
	itemNumInlongestlist = temp2;
	for (int j = 0; j < TABLESIZE; j++)
	{
		if (hashNodeArray[j].getCurrentNum() == temp2 + 1)
			indexOfLongestBucket = j;
		break;
	}

}


void HashTable::tabledisplay()
{
	for (int i = 0; i < TABLESIZE; i++)
	{
		if (hashNodeArray[i].getCurrentNum())
			hashNodeArray[i].display();
	}
}

Book *HashTable::getData(std::string keyValue)
{
	int index = hashFunction(keyValue);
	return hashNodeArray[index].getItem(keyValue);
}


/*
deleteObject requires that you verify the object exists already.
*/

bool HashTable::removeData(std::string keyValue)
{
	int index = hashFunction(keyValue);
	return hashNodeArray[index].removeItem(keyValue);
}

int HashTable::hashFunction(std::string& keyValue)
{
	int value = 0;
	for (int i = 0; i < keyValue.length(); i++) {
		value += keyValue.at(i);
	}
	return (((16 * value) + 18) % 271) % TABLESIZE;
}
#endif