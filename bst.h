#ifndef BST_H
#define BST_H

#include <iostream>
#include "treeNode.h"
#include "student.h"
#include "faculty.h"

using namespace std;

template <class T>
class BST
{
public:
	BST();
	virtual ~BST();
	int size;

	void insert (T data, int k);
	treeNode<T>* getNode(int k);
	bool deleteNode (int k);

	bool contains(int value);
	bool isEmpty();
	T getMin();
	T getMax();

	void printInOrder (treeNode<T> *n);
	void printPostOrder (treeNode<T> *n);
	void printPreOrder (treeNode<T> *n);

	treeNode<T>* getSuccessor (treeNode<T> *d);
	treeNode<T>* getRoot();
	int getSize();
	//void printTree(treeNode *node);

private:
	treeNode<T> *root;
};

template<class T>
BST<T>::BST()
{
	root = NULL;
	size = 0;
}

template<class T>
BST<T>::~BST()
{
	//iterate through and delete all nodes
}

template<class T>
T BST<T>::getMin()
{
	treeNode<T> *current = root;
	if (root  == NULL)
	{
		return NULL;
	}
	while (current->left != NULL)
	{
		current = current->left;
	}
	return current;
}

template<class T>
T BST<T>::getMax()
{
	treeNode<T> *current = root;
	if (root  == NULL)
	{
		return NULL;
	}
	while (current->right != NULL)
	{
		current = current->right;
	}
	return current;
}

template<class T>
void BST<T>::insert(T data, int k)
{
	treeNode<T> *newNode = new treeNode<T>(data, k);

	if (root == NULL)
		{
			root = newNode;
		}
	else //not an empty tree
	{
		treeNode<T> *current = root;
		treeNode<T> *parent = NULL; //empty node

		while (true)
		{
			parent = current;

			if (k < current->key) //go left
			{
				current = current->left;

				if (current == NULL)
				{
					parent->left = newNode;
					break;
				}
			}
			else if (k > current->key)
			{
				current = current->right;

				if (current == NULL)
				{
					parent->right = newNode;
					break;
				}
			}
			else
			{
				cout<< "Node already occupied, cannot add.";
			}
		}
	}
	size++;
}

template<class T>
bool BST<T>::contains(int value)
//not sure how to turn this into template
{
	if (root == NULL)
	{
		return false;
	}
	else
	{
		treeNode<T> *current = root;
		while (current->key != value)
		{
			if (value < current->key)
			{
				current = current->left;
			}
			else
			{
				current = current->right;
			}

			if (current == NULL)
				return false;
		}
	}
	return true;
}

template<class T>
treeNode<T>* BST<T>::getNode(int value)
{
	if(root == NULL)
	{
		return NULL;
		//return false;
	}
	else
	{
		treeNode<T> *current = root;
		while (current->key!= value)
		{
			if(value < current->key)
			{
				current = current->left;
			}
			else
			{
				current = current->right;
			}

			if (current == NULL)
				return NULL;
				//return false;
		}
		return current;
	}
	//return true;
}

template<class T>
bool BST<T>::deleteNode(int k)
{
	if(root == NULL)
	{
		return false;
	}

	treeNode<T> *current = root;
	treeNode<T> *parent = root;
	bool isLeft = true;

	while (current->key !=k)
	{
		parent = current;

		if(k < current->key)
		{
			isLeft = true;
			current = current->left;
		}
		else if (k > current->key)
		{
			isLeft = false;
			current = current->right;
		}

		if(current == NULL)
		{
			return false; //no such data in tree to delete
		}
	}
	//when loop exits we have found what we want to delete

	//case for no children:

	if (current->left == NULL && current->right == NULL) //it's a leaf node
	{
		//check if it's the root
		if (current == root)
		{
			root = NULL;
		}
		else if (isLeft)
		{
			//if its the left child of a parent that youre deleting, set the left pointer to null
			parent->left = NULL;
		}
		else
		{
			parent->right = NULL;
		}
	}

	else if (current->right == NULL) //node has one child on the left but no right child
	{
		if (current == root)
		{
			root = current->left;
		}
		else if (isLeft)
		{
			parent->left = current->left;
		}
		else
		{
			parent->right = current->left;
		}
	}

	else if (current->left == NULL) //no left child
	{
		if (current == root)
		{
			root = current->right;
		}
		else if (isLeft)
		{
			parent->left = current->right;
		}
		else
		{
			parent->right = current->right;
		}
	}
	else if (current->left != NULL && current->right != NULL) //if node has two children
	{
		treeNode<T> *successor = getSuccessor(current);
		if (current == root)
		{
			root = successor;
		}
		else if (isLeft)
		{
			parent->left = successor;
		}
		else
		{
			parent->right = successor;
		}

		successor->left = current->left;
	}
	size--;
	return true;
}

template<class T>
treeNode<T>*BST<T>::getSuccessor(treeNode<T> *d) //d represents the node we are going to delete
{
	treeNode<T> *sp = d; //sp= successor parent
	treeNode<T> *successor = d;
	treeNode<T> *current = d->right;

	while (current != NULL)
	{
		sp = successor;
		successor = current;
		current = current->left;
	}

	if (successor !=d->right)
	{
		sp->left = successor->right;
		successor->right = d->right;
	}
	return successor;
}

template<class T>
void BST<T>::printInOrder(treeNode<T> *n)	//Should use getRoot as argument.
{
	if(n != NULL)
	{
		printInOrder(n->left);
		cout << n->key << endl;
		printInOrder(n->right);
	}
}

template<class T>
void BST<T>::printPostOrder(treeNode<T> *n)	//Should use getRoot as argument.
{
	if(n != NULL)
	{
		printPostOrder(n->left);
		printPostOrder(n->right);

		cout << n->key << endl;
	}
}

template<class T>
void BST<T>::printPreOrder(treeNode<T> *n)	//Should use getRoot as argument.
{
	if(n != NULL)
	{
		cout << n->key << endl;

		printPreOrder(n->left);
		printPreOrder(n->right);
	}
}

template<class T>
treeNode<T>* BST<T>::getRoot()
{
	if(root != NULL)
	{
		return root;
	}
	else
	{
		return NULL;
	}
}

template<class T>
int BST<T>::getSize()		//To be used with getRoot() method.
{
	return size;
}

#endif