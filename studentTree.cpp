#include "studentTree.h"
#include <string>
#include <fstream>

studentTree::studentTree()
{

}
studentTree::~studentTree()
{

}

treeNode<student>* studentTree::getRoot()
{
	treeNode<student>* studentNode = stdTree.getRoot();
	if (studentNode != NULL)
		return studentNode;
	else
		return NULL;
}
int studentTree::getFacInfo(int ID) //OPTION #5
{
	if (stdTree.contains(ID))
	{
		treeNode<student>* studentNode = stdTree.getNode(ID);
		student stdInfo = studentNode->element; 
		return stdInfo.getAdvisorID();
	}
	else
	{
		cout<<"Student ID does not exist in this database.";
		return -1; 
	}
}

int studentTree::addNewStudent() //OPTION #7
{
	int newStdID;
	string newStdName;
	string newStdLevel;
	string newStdMajor;
	double newStdGPA;
	int newStdAdvisorID;
	//student newStdNode;

	cout << "Enter new student ID: ";

	while (!(cin >> newStdID))
	{
		cin.clear();
		while (cin.get() != '\n') continue;
		cout << "Invalid student ID ! " << endl;
	}

	if (stdTree.contains(newStdID))
	{
		cout << "ID already exists in this database.";
	}
	else
		//newStdNode.setID(newStdID);
	cout << endl;
	cin.ignore();

		cout<<"Enter new student name: ";
		getline(cin, newStdName);
		//newStdNode.setName(newStdName);
		cout<<endl;
		cout<<"Enter new student level: ";
		getline(cin,newStdLevel);
		//newStdNode.setLevel(newStdLevel);
		cout<<endl;
		cout<<"Enter new student major: ";
		getline(cin,newStdMajor);
		//newStdNode.setMajor(newStdMajor);
		cout<<endl;
		cout<<"Enter new student GPA: ";
		while (!(cin >> newStdGPA) || newStdGPA < 0 || newStdGPA > 4)
		{
			cin.clear();
			while (cin.get() != '\n') continue;
			cout << "Invalid student GPA ! " << endl;
		}
		//newStdNode.setGPA(newStdGPA);

		cout << "Enter Student's Advisor ID: ";

		while (!(cin >> newStdAdvisorID))
		{
			cin.clear();
			while (cin.get() != '\n') continue;
			cout << "Invalid Advisor ID ! " << endl;
		}
		student newStdNode(newStdID, newStdName, newStdLevel, newStdMajor, newStdGPA, newStdAdvisorID);
		stdTree.insert(newStdNode, newStdID);
		cout<<endl;

		return newStdID;
}

void studentTree::deleteStudent(int k)
{
	stdTree.deleteNode(k);
}


treeNode<student>* studentTree::getStudentNode(int k)
{
	treeNode<student>* stdNode = stdTree.getNode(k);
	if (stdNode == NULL)
	{
		return NULL;
	}
	return stdNode;
}

void studentTree::changeStudentAdvisor(int k, int j)
{
	treeNode<student>* stdNode = getStudentNode(k);
	if (stdNode == NULL)
	{
		return;
	}
	stdNode->element.setAdvisorID(j);
}

int studentTree::getStudentAdvisor(int k)
{
	treeNode<student>* stdNode = getStudentNode(k);
	if (stdNode == NULL)
	{
		return 0;
	}
	return stdNode->element.getAdvisorID();
}

void studentTree::printStudent(int k)
{
	treeNode<student>* stdNode = getStudentNode(k);
	stdNode->element.printStdInfo();
}

void studentTree::printTree(treeNode<student>* n)
{
	if (n != NULL)
	{
		printTree(n->left);
		n->element.printStdInfo();
		printTree(n->right);
	}
}

void studentTree::searchName(string name, treeNode<student>* n)
{
	if (n != NULL)
	{
		searchName(name, n->left);
		if (n->element.getName() == name)
		{
			cout << "Student found." << endl;
			n->element.printStdInfo();
			return;
		}
		searchName(name, n->right);
	}
}

void studentTree::serializeStudent()
{
	ofstream outFile("studentTable.txt");
	outFile << stdTree.getSize() << endl;

	treeTraversal(stdTree.getRoot(), outFile);
}

void studentTree::treeTraversal(treeNode<student> *n, ofstream& file)
{
	if (n != NULL)
	{
		n->element.writeStudentsToFile(file);
		treeTraversal(n->left, file);
		treeTraversal(n->right, file);
	}
}

void studentTree::loadStudentTreeFromFile(string file)
{
	ifstream inFile;
	inFile.open(file.c_str());
	int loop;	inFile >> loop;
	for (int i = 0; i < loop; ++i) {
		student node = student();
		int myId;	inFile >> myId;	node.setID(myId); inFile.get();
		string myName;	getline(inFile, myName); node.setName(myName);
		string myLevel;	inFile >> myLevel;	node.setLevel(myLevel);	inFile.get();
		string myMajor;	getline(inFile, myMajor);	node.setMajor(myMajor);
		double myGpa; inFile >> myGpa; node.setGPA(myGpa);
		int myAdv;	inFile >> myAdv;	node.setAdvisorID(myAdv);
		stdTree.insert(node, myId);
	}
	inFile.close();


/**
	student newStdNode;

	ifstream inFile(file, ios::binary);
	if (!inFile)
	{
		cout << "File not found !! Press any Key...";
		return;
	}

	while (1) // infinite while loop
	{
		inFile.read((char *)&newStdNode, sizeof(student));
		if (inFile.eof())
			break;
		stdTree.insert(newStdNode, newStdNode.getID());
	}

	inFile.close();

**/
}