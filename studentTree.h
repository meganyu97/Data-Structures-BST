#ifndef STUDENTTREE_H
#define STUDENTTREE_H

#include "student.h"
#include "treeNode.h"
#include "bst.h"
#include "facultyTree.h"

using namespace std;

class studentTree
{
public:
	BST<student> stdTree;
	studentTree();
	~studentTree();
	treeNode<student>* getRoot();
	treeNode<student>* getStudentNode(int k);
	void changeStudentAdvisor(int k, int j);
	int getStudentAdvisor(int k);
	void printStudent(int k);
	void printTree(treeNode<student>* n);
	void searchName(string name, treeNode<student>* n);
	void serializeStudent();
	void treeTraversal(treeNode<student> *n, ofstream& file);
	int getFacInfo(int ID); //need user input in master class

	int addNewStudent();
	void deleteStudent(int k);
	void loadStudentTreeFromFile(string file);
	
};



#endif