#ifndef FACULTYTREE_H
#define FACULTYTREE_H

#include "faculty.h"
#include "treeNode.h"
#include "bst.h"
#include "studentTree.h"

#define MaxFacultyIDList 50

using namespace std;

class facultyTree
{
public:
	BST<faculty> facTree;
	facultyTree();
	~facultyTree();
	treeNode<faculty>* getRoot();
	treeNode<faculty>* getFacultyNode(int k);

	void addFaculty();
	void deleteFaculty(int k);
	int getNumAdvisees(int k);
	int* getFacultyAdvisees(int k);
	void addAdvisee(int k, int j);
	void removeAdvisee(int k, int j);
	void printFaculty(int k);
	void printFacultyInfo(int ID);
	void searchName(string name, treeNode<faculty>* n);
	void serializeFaculty();
	void loadFacultyTreeFromFile(string file);
	void printTree(treeNode<faculty> *n);
	void treeTraversal(treeNode<faculty> *n, ofstream& file);

	int assignNewAdvisor(string major);
	int* facultyIDList;
	int facultyIDListSize;
};


#endif