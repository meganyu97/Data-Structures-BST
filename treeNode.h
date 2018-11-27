#ifndef TREENODE_H
#define TREENODE_H

#include <iostream> 
using namespace std;

template <class T>

class treeNode
{
	public:
	treeNode();
	treeNode(T data, int k);
	virtual ~treeNode();

	int key;
	T element;

	treeNode* left;
	treeNode* right;
};

template<class T>
treeNode<T>::treeNode()
{
	left = NULL;
	right = NULL;
}

template<class T>
treeNode<T>::treeNode(T data, int k)
{
	left = NULL;
	right = NULL;

	element = data;
	key = k;
}

template<class T>
treeNode<T>::~treeNode()
{
	
}
#endif
