/**
@file BinarySearchTree.h
@Purpose: header file of BST ADT
@partner's score 3
@author PengWei & Tiffany Liew
@version 1.1 11/21/17
*/
#pragma once 
#ifndef _BINARY_SEARCH_TREE
#define _BINARY_SEARCH_TREE

#include<iomanip>
#include <algorithm>
#include "BinaryNode.h"
#include "NotFoundException.h"

template<typename KeyType, typename ItemType>
class BinarySearchTree
{
	private:
		BinaryNode<KeyType, ItemType>* rootPtr;

	protected:
		
		//Protected Utility Methods Section  Helper methods for public methods.
		int getHeightHelper(BinaryNode<KeyType, ItemType>* subTreePtr) const;
		int getNumberOfNodesHelper(BinaryNode<KeyType, ItemType>* subTreePtr) const;
		BinaryNode<KeyType, ItemType>* removeValue(BinaryNode<KeyType, ItemType>* subTreePtr, const KeyType target, bool& success);
		BinaryNode<KeyType, ItemType>* removeNode(BinaryNode<KeyType, ItemType>* nodeToDeletePtr);
		BinaryNode<KeyType, ItemType>* removeLeftmostNode(BinaryNode<KeyType, ItemType>* nodeToDeletePtr, KeyType& inorderSucessorKey, ItemType& inorderSucessorValue);
		bool isLeaf(BinaryNode<KeyType, ItemType>* nodeToDeletePtr);
		void destroyTree(BinaryNode<KeyType, ItemType>* subTreePtr);
		BinaryNode<KeyType, ItemType>* findNode(BinaryNode<KeyType, ItemType>* subTreePtr, const KeyType& target) const;
		BinaryNode<KeyType, ItemType>* copyTree(const BinaryNode<KeyType, ItemType>* treePtr) const;
		void inorderHelper(void visit(ItemType&), BinaryNode<KeyType, ItemType>* subTreePtr) const;
		void preorderHelper(void visit(ItemType&), BinaryNode<KeyType, ItemType>* subTreePtr) const;
		void postorderHelper(void visit(ItemType&), BinaryNode<KeyType, ItemType>* subTreePtr) const;
		void breadthFirstHelper(void visit(ItemType&), BinaryNode<KeyType, ItemType>* subTreePtr, int level) const;
		BinaryNode<KeyType, ItemType>* inorderInsertion(BinaryNode<KeyType, ItemType>* subTreePtr, BinaryNode<KeyType, ItemType>* newNodePtr);
		void  BinarySearchTree<KeyType, ItemType>::graphAux(BinaryNode<KeyType, ItemType>*subtree, int a);

	public:
		// Constructor and Destructor Section.
		BinarySearchTree(); // creates an empty BST
		BinarySearchTree(const BinarySearchTree<KeyType, ItemType>& tree);
		virtual ~BinarySearchTree();

		void graph();

		
		// Public Methods Section.
		bool isEmpty() const;
		int getHeight() const;
		int getNumberOfNodes() const;
		void add(const KeyType& newkey,const ItemType& newEntry);
		void remove(const KeyType& aKey) throw(NotFoundException);
		ItemType getEntry(const KeyType& aKey) const throw(NotFoundException);
		bool contains(const KeyType& aKey) const;
		BinaryNode<KeyType, ItemType>* getroot() { return rootPtr; }

		// Public Traversals Section.
		void preorderTraverse(void visit(ItemType&)) const;
		void inorderTraverse(void visit(ItemType&)) const;
		void postorderTraverse(void visit(ItemType&)) const;
		void breadthFirstTraverse(void visit(ItemType&)) const;
		
}; 

template<typename KeyType, typename ItemType>
BinarySearchTree<KeyType, ItemType>::BinarySearchTree() : rootPtr(nullptr) {}

//Copy constructor, utilizes copyTree helper method
template<typename KeyType, typename ItemType>
BinarySearchTree<KeyType, ItemType>::BinarySearchTree(const BinarySearchTree<KeyType, ItemType>& tree)
{
	rootPtr = copyTree(tree.rootPtr);
}

//Destructor, utilizes destroyTree helper method
template<typename KeyType, typename ItemType>
BinarySearchTree<KeyType, ItemType>::~BinarySearchTree()
{
	destroyTree(rootPtr);
}


//Boolean check - return whether or not tree contains any number of nodes
template<typename KeyType, typename ItemType>
bool BinarySearchTree<KeyType, ItemType>::isEmpty() const
{
	return rootPtr;
}

//Return height of the tree - utilizes getHeighterHelper method
template<typename KeyType, typename ItemType>
int BinarySearchTree<KeyType, ItemType>::getHeight() const
{
	return getHeightHelper(rootPtr);
}

//Return number of nodes - utilizes getNumberOfNodes helper method
template<typename KeyType, typename ItemType>
int BinarySearchTree<KeyType, ItemType>::getNumberOfNodes() const
{
	return getNumberOfNodesHelper(rootPtr);
}

//Insert new node with entry newEntry into BST - utilizes inorderInsertion helper method
template<typename KeyType, typename ItemType>
void BinarySearchTree<KeyType, ItemType>::add(const KeyType& newkey,const ItemType& newEntry)
{
	BinaryNode<KeyType, ItemType>* newNodePtr = new BinaryNode<KeyType, ItemType>(newkey,newEntry);
	rootPtr = inorderInsertion(rootPtr, newNodePtr);
}

/*
* Remove node that has associated key aKey from BST, throw exception if node does not
* exist - utilizes removeValue helper method
*/
template<typename KeyType, typename ItemType>
void BinarySearchTree<KeyType, ItemType>::remove(const KeyType& aKey) throw(NotFoundException)
{
	bool success = false;
	rootPtr = removeValue(rootPtr, aKey, success);

	if (!success)
		throw NotFoundException("key not found");

}

/*
* Return ItemType associated with KeyType aKey, throw exception if node does not exist - utilizes
* findNode helper method
*/
template<typename KeyType, typename ItemType>
ItemType BinarySearchTree<KeyType, ItemType>::getEntry(const KeyType& aKey) const throw(NotFoundException)
{
	BinaryNode<KeyType, ItemType>* foundPtr = findNode(rootPtr, aKey);
	if (!foundPtr)
		throw NotFoundException("key not found");
	else
		return foundPtr->getItem();
}

template<typename KeyType, typename ItemType>
bool BinarySearchTree<KeyType, ItemType>::contains(const KeyType& aKey) const {
	if (findNode(rootPtr, aKey))
		return true;
	else
		return false;
}

//Traversal Methods - use associated helper methods
template<typename KeyType, typename ItemType>
void BinarySearchTree<KeyType, ItemType>::preorderTraverse(void visit(ItemType&)) const
{
	preorderHelper(visit, rootPtr);
}

template<typename KeyType, typename ItemType>
void BinarySearchTree<KeyType, ItemType>::inorderTraverse(void visit(ItemType&)) const
{
	inorderHelper(visit, rootPtr);
}

template<typename KeyType, typename ItemType>
void BinarySearchTree<KeyType, ItemType>::postorderTraverse(void visit(ItemType&)) const
{
	postorderHelper(visit, rootPtr);
}


template<typename KeyType, typename ItemType>
void BinarySearchTree<KeyType, ItemType>::breadthFirstTraverse(void visitB(ItemType&)) const
{
	int h = this->getHeight();
	int i;
	for (i = 1; i <= h; i++)
	{
		breadthFirstHelper(visitB, rootPtr, i);
	}
}





//Protected Utility Methods
//Recurse over BST, for each node found, add 1. Return when branches all terminate to base case, node has no children
template<typename KeyType, typename ItemType>
int BinarySearchTree<KeyType, ItemType>::getNumberOfNodesHelper(BinaryNode<KeyType, ItemType>* subTreePtr) const
{
	if (!subTreePtr)
		return 0;
	else
		return 1 + getNumberOfNodesHelper(subTreePtr->getLeftChildPtr()) + getNumberOfNodesHelper(subTreePtr->getRightChildPtr());
}


//Recursivly find node associated with KeyType target. Have helper methods handle special removal cases.
// Return to remove a pointer to the BST without the removed node. Modify success code throughout.
template<typename KeyType, typename ItemType>
BinaryNode<KeyType, ItemType>* BinarySearchTree<KeyType, ItemType>::removeValue(BinaryNode<KeyType, ItemType>* subTreePtr, const KeyType target, bool& success)
{
	//Special case, tree is empty, node never found, return false
	if (subTreePtr == nullptr)
	{
		success = false;
		return nullptr;
	}
	//Current node contains target
	else if (subTreePtr->getKey() == target)
	{
		//Remove node, return tree without node
		subTreePtr = removeNode(subTreePtr);
		success = true;
		return subTreePtr;
	}
	//Current node greater than target, recurse to nodes left child
	else if (subTreePtr->getKey() > target)
	{
		BinaryNode<KeyType, ItemType>* tempPtr = removeValue(subTreePtr->getLeftChildPtr(), target, success);
		subTreePtr->setLeftChildPtr(tempPtr);
		return subTreePtr;
	}
	//Current node less than target, recurse to nodes right child
	else
	{
		BinaryNode<KeyType, ItemType>* tempPtr = removeValue(subTreePtr->getRightChildPtr(), target, success);
		subTreePtr->setRightChildPtr(tempPtr);
		return subTreePtr;
	}
}

/*
Handle special cases
1. Node is leaf
2. Node has only one child
3. Node has two children
*/
template<typename KeyType, typename ItemType>
BinaryNode<KeyType, ItemType>* BinarySearchTree<KeyType, ItemType>::removeNode(BinaryNode<KeyType, ItemType>* nodeToDeletePtr)
{
	//Node is leaf - delete it, return null to subTreePtr
	if (nodeToDeletePtr->isLeaf() == true)
	{
		delete nodeToDeletePtr;
		nodeToDeletePtr = nullptr;
		return nodeToDeletePtr;
	}
	//Node has only one child 
	else if ((nodeToDeletePtr->getLeftChildPtr() == nullptr && nodeToDeletePtr->getRightChildPtr() != nullptr) || (nodeToDeletePtr->getRightChildPtr() == nullptr && nodeToDeletePtr->getLeftChildPtr() != nullptr))
	{
		BinaryNode<KeyType, ItemType>* nodeToConnectPtr;
		//Get node's child
		if (nodeToDeletePtr->getLeftChildPtr() != nullptr)
			nodeToConnectPtr = nodeToDeletePtr->getLeftChildPtr();

		else
			nodeToConnectPtr = nodeToDeletePtr->getRightChildPtr();

		//Delete node
		delete nodeToDeletePtr;
		nodeToDeletePtr = nullptr;
		//Return node's child to parent
		return nodeToConnectPtr;
	}
	//Node has two children
	else
	{
		ItemType inorderSuccessorValue;
		KeyType inorderSuccessorKey;
		//Find Inorder Successor node, return its entry to temporary pointer, delete original Inorder Successor node
		BinaryNode<KeyType, ItemType>* tempPtr = removeLeftmostNode(nodeToDeletePtr->getRightChildPtr(), inorderSuccessorKey, inorderSuccessorValue);
		nodeToDeletePtr->setRightChildPtr(tempPtr);
		//Change node's Item to Inorder Successor's Item
		nodeToDeletePtr->setKey(inorderSuccessorKey);
		nodeToDeletePtr->setItem(inorderSuccessorValue);
		return nodeToDeletePtr;
	}
}

//Find inorder successor node recursively. Copy its ItemType. Remove its node
template<typename KeyType, typename ItemType>
BinaryNode<KeyType, ItemType>* BinarySearchTree<KeyType, ItemType>::removeLeftmostNode(BinaryNode<KeyType, ItemType>* nodeToDeletePtr, KeyType& inorderSuccessorKey,ItemType& inorderSuccessorValue)
{
	//Inorder successor found
	if (nodeToDeletePtr->getLeftChildPtr() == nullptr)
	{
		inorderSuccessorKey= nodeToDeletePtr->getKey();
		inorderSuccessorValue = nodeToDeletePtr->getItem();
		return removeNode(nodeToDeletePtr);
	}
	//Inorder not found, recurse
	else
	{
		nodeToDeletePtr->setLeftChildPtr(removeLeftmostNode(nodeToDeletePtr->getLeftChildPtr(), inorderSuccessorKey, inorderSuccessorValue));
		return nodeToDeletePtr;

	}
}

template<typename KeyType, typename ItemType>
bool BinarySearchTree<KeyType, ItemType>::isLeaf(BinaryNode<KeyType, ItemType>* nodeToDeletePtr)
{
	return nodeToDeletePtr->isLeaf();
}

//Helper for inorder traverse - visit left subTree, root, right subTree recursively
template<typename KeyType, typename ItemType>
void BinarySearchTree<KeyType, ItemType>::inorderHelper(void visit(ItemType&), BinaryNode<KeyType, ItemType>* subTreePtr) const
{
	if (subTreePtr != nullptr)
	{
		inorderHelper(visit, subTreePtr->getLeftChildPtr());
		ItemType theItem = subTreePtr->getItem();
		visit(theItem);
		inorderHelper(visit, subTreePtr->getRightChildPtr());
	}
}

//Helper for preorder traverse - visit root, left subTree, right subTree recursively
template<typename KeyType, typename ItemType>
void BinarySearchTree<KeyType, ItemType>::preorderHelper(void visit(ItemType&), BinaryNode<KeyType, ItemType>* subTreePtr) const
{
	if (subTreePtr != nullptr)
	{
		ItemType theItem = subTreePtr->getItem();
		visit(theItem);
		preorderHelper(visit, subTreePtr->getLeftChildPtr());
		preorderHelper(visit, subTreePtr->getRightChildPtr());
	}
}

//Helper for postorder traverse - visit left subTree, right subTree, root recursively
template<typename KeyType, typename ItemType>
void BinarySearchTree<KeyType, ItemType>::postorderHelper(void visit(ItemType&), BinaryNode<KeyType, ItemType>* subTreePtr) const
{
	if (subTreePtr != nullptr)
	{

		postorderHelper(visit, subTreePtr->getLeftChildPtr());
		postorderHelper(visit, subTreePtr->getRightChildPtr());
		ItemType theItem = subTreePtr->getItem();
		visit(theItem);
	}
	
}

//Helper for breadth first traverse - visit level 1, both subTrees' level 1,recursively
template<typename KeyType, typename ItemType>
void BinarySearchTree<KeyType, ItemType>::breadthFirstHelper(void visitB(ItemType&), BinaryNode<KeyType, ItemType>* subTreePtr,  int level) const
{
	if (subTreePtr != nullptr)
	{
		
		if (level == 1)
		{
			ItemType theItem = subTreePtr->getItem();
			visitB(theItem);
		}
		else if (level > 1)
		{
			breadthFirstHelper(visitB, subTreePtr->getLeftChildPtr(), level - 1);			
			breadthFirstHelper(visitB, subTreePtr->getRightChildPtr(), level - 1);
		}

	}
}

//Helper method for add - recursively find correct placement
template<typename KeyType, typename ItemType>
BinaryNode<KeyType, ItemType>* BinarySearchTree<KeyType, ItemType>::inorderInsertion(BinaryNode<KeyType, ItemType>* subTreePtr, BinaryNode<KeyType, ItemType>* newNodePtr)
{
	//Tree empty or no child for previously compared node (base case)
	if (subTreePtr == nullptr)
	{
		return newNodePtr;
	}
	//New node greater than current node, recurse right
	else if (newNodePtr->getKey() > subTreePtr->getKey())
	{
		BinaryNode<KeyType, ItemType>* tempPtr = inorderInsertion(subTreePtr->getRightChildPtr(), newNodePtr);
		subTreePtr->setRightChildPtr(tempPtr);
	}
	//New node less than current node, recurse left
	else
	{
		BinaryNode<KeyType, ItemType>* tempPtr = inorderInsertion(subTreePtr->getLeftChildPtr(), newNodePtr);
		subTreePtr->setLeftChildPtr(tempPtr);
	}

	return subTreePtr;
}

//Recurse over each branch of tree, add 1 at each found node
template<typename KeyType, typename ItemType>
int BinarySearchTree<KeyType, ItemType>::getHeightHelper(BinaryNode<KeyType, ItemType>* subTreePtr) const
{
	//Base case, nodes children are null
	if (subTreePtr == nullptr)
		return 0;
	else
		return 1 + std::max(getHeightHelper(subTreePtr->getLeftChildPtr()), getHeightHelper(subTreePtr->getRightChildPtr()));
}
//Recurse over each branch, delete nodes
template<typename KeyType, typename ItemType>
void BinarySearchTree<KeyType, ItemType>::destroyTree(BinaryNode<KeyType, ItemType>* subTreePtr)
{
	if (subTreePtr != nullptr)
	{
		destroyTree(subTreePtr->getLeftChildPtr());
		destroyTree(subTreePtr->getRightChildPtr());
		delete subTreePtr;
	}
}

//Recursively find node with KeyType target by performing comparisons
template<typename KeyType, typename ItemType>
BinaryNode<KeyType, ItemType>* BinarySearchTree<KeyType, ItemType>::findNode(BinaryNode<KeyType, ItemType>* subTreePtr, const KeyType& target) const
{
	//Tree is empty, return null
	if (subTreePtr == nullptr)
		return nullptr;
	//Found node
	else if (subTreePtr->getKey() == target)
		return subTreePtr;
	//Current node greater than target, recurse left
	else if (subTreePtr->getKey() > target)
		return findNode(subTreePtr->getLeftChildPtr(), target);
	//Current node less than target, recurse right
	else
		return findNode(subTreePtr->getRightChildPtr(), target);
}

//Recursively copy each node of the tree
template<typename KeyType, typename ItemType>
BinaryNode<KeyType, ItemType>* BinarySearchTree<KeyType, ItemType>::copyTree(const BinaryNode<KeyType, ItemType>* treePtr) const
{
	BinaryNode<KeyType, ItemType>* newTreePtr = nullptr;

	if (treePtr != nullptr) 
	{
		//Create new tree node
		newTreePtr = new BinaryNode<KeyType, ItemType>(treePtr->getKey(),treePtr->getItem(), nullptr, nullptr);
		//Copy old tree's left and right children
		newTreePtr->setLeftChildPtr(copyTree(treePtr->getLeftChildPtr()));
		newTreePtr->setRightChildPtr(copyTree(treePtr->getRightChildPtr()));
	}

	return newTreePtr;
}



template<typename KeyType, typename ItemType>
 void BinarySearchTree<KeyType, ItemType>::graph()
{
	std::cout << "----------------------------------------\n";
	this->graphAux(rootPtr, 0);
	std::cout << "----------------------------------------\n";
}

 template<typename KeyType, typename ItemType>
void  BinarySearchTree<KeyType, ItemType>::graphAux(BinaryNode<KeyType, ItemType>*subtree, int a)
{
	if (subtree!=nullptr)
	{

		graphAux(subtree->getRightChildPtr(), a + 13);
		std::cout << std::setw(a) << " " << subtree->getItem() << std::endl;
		//cout << setw(a) << " " << subtree->key << " " << subtree->balanceFactor << endl;
		//                                                                                                                                                                                              cout << setw(a) << " " << subtree->key;
		//if (subtree->parent != 0)
		//	cout <<"("<<subtree->parent->key<<")"<< endl;
		graphAux(subtree->getLeftChildPtr(), a + 13);
	}
}

#endif