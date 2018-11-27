#include "facultyTree.h"
#include <fstream>
#include <string>
#include "GenStack.h"

facultyTree::facultyTree()
{
	facultyIDList = new int[MaxFacultyIDList]();
	facultyIDListSize = 0; // 50;
}
facultyTree::~facultyTree()
{

	//created list of faculty ID so you are able to access each faculty
	// member without having to go through each node of the fac tree 
	//
	if((facultyIDList != NULL) && (facultyIDListSize != 0))
		delete[] facultyIDList; 
}

treeNode<faculty>* facultyTree::getRoot()
{
	treeNode<faculty>* facNode = facTree.getRoot();

	if (facNode != NULL)
	{
		return facNode;
	}
	else
	{
		return NULL;
	}
}

treeNode<faculty>* facultyTree::getFacultyNode(int k)
{
	treeNode<faculty>* facNode = facTree.getNode(k);
	if (facNode == NULL)
	{
		return NULL;
	}
	return facNode;
}

void facultyTree::addFaculty()
{
	int newFacID;
	string newFacName;
	string newFacLevel;
	string newFacDept;
	//faculty newFacNode;

	cout << "Enter new faculty ID: ";

	while (!(cin >> newFacID))
	{
		cin.clear();
		//while (cin.get() != '\n') continue;
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Invalid faculty ID ! " << endl;
	}
	cout << endl;
	cin.ignore();

	if (facTree.contains(newFacID))
	{
		cout << "Faculty ID already exists in this database." << endl;
	}
	//else
		//newFacNode.setID(newFacID);

	cout << "Enter new faculty name: ";
	getline(cin, newFacName);
	//newFacNode.setName(newFacName);
	cout << endl;
	cout << "Enter new faculty level: ";
	getline(cin, newFacLevel);
	//newFacNode.setLevel(newFacLevel);
	cout << endl;
	cout << "Enter new faculty department: ";
	getline(cin, newFacDept);
	//newFacNode.setDepartment(newFacDept);
	cout << endl;
	faculty newFacNode(newFacID, newFacName, newFacLevel, newFacDept);

	facTree.insert(newFacNode, newFacID);
	cout << endl;

}

void facultyTree::deleteFaculty(int k)
{
	facTree.deleteNode(k);
}

int facultyTree::getNumAdvisees(int k)
{
	treeNode<faculty>* facNode = getFacultyNode(k);
	if (facNode == NULL)
	{
		return 0;
	}
	return facNode->element.getAdviseeListSize();
}

int* facultyTree::getFacultyAdvisees(int k)
{
	treeNode<faculty>* facNode = getFacultyNode(k);
	if (facNode == NULL)
	{
		return NULL;
	}
	return facNode->element.getAdvisees();
}

void facultyTree::addAdvisee(int k, int j)
{
	treeNode<faculty>* facNode = getFacultyNode(k);
	if (facNode == NULL)
	{
		return;
	}
	facNode->element.addStudent(j);
}

void facultyTree::removeAdvisee(int k, int j)
{
	treeNode<faculty>* facNode = getFacultyNode(k);
	if (facNode == NULL)
	{
		return;
	}
	facNode->element.removeStudent(j);
}

void facultyTree::printFaculty(int k)
{
	treeNode<faculty>* facNode = getFacultyNode(k);
	if (facNode->element.getID() == -1) return;

	facNode->element.printFacInfo();
}

void facultyTree::printFacultyInfo(int ID)
{
	if (facTree.contains(ID))
	{
		treeNode<faculty>* facultyNode = facTree.getNode(ID);
		faculty facInfo = facultyNode->element;
		facInfo.printFacInfo(); 
	}
}

void facultyTree::searchName(string name, treeNode<faculty>* n)
{
	if (n != NULL)
	{
		searchName(name, n->left);
		if (n->element.getName() == name)
		{
			cout << "Faculty found." << endl;
			n->element.printFacInfo();
			return;
		}
		searchName(name, n->right);
	}
}

void facultyTree::serializeFaculty() 
{
	ofstream outFile("facultyTable.txt");
	outFile << facTree.getSize() << endl;

	treeTraversal(facTree.getRoot(), outFile);
}

void facultyTree::treeTraversal(treeNode<faculty> *n, ofstream& file)
{
	if (n != NULL)
	{
		n->element.writeFacultyToFile(file);
		treeTraversal(n->left, file);
		treeTraversal(n->right, file);
	}
}

void facultyTree::loadFacultyTreeFromFile(string file)
{

	ifstream inFile;
	inFile.open(file.c_str());
	int loop;	inFile >> loop;
	for (int i = 0; i < loop; ++i) {
		faculty node = faculty();
		int myId;	inFile >> myId;	node.setID(myId); inFile.get();
		string myName;	getline(inFile, myName); node.setName(myName);
		string myLevel;	inFile >> myLevel;	node.setLevel(myLevel);	inFile.get();
		string myDept;	getline(inFile, myDept);	node.setDepartment(myDept);
		int myNumAdvisees;	inFile >> myNumAdvisees;
		for (int i = 0; i < myNumAdvisees; ++i)
		{
			int myStu;	inFile >> myStu;	inFile.get();
			node.addStudent(myStu);
		}
		facTree.insert(node, myId);
	}
	inFile.close();
	//faculty newFacNode;

	//ifstream inFile(file, ios::binary);
	//if (!inFile)
	//{
	//	cout << "File not found !! Press any Key...";
	//	return;
	//}

	//while (1) // infinite while loop
	//{
	//	inFile.read((char *)&newFacNode, sizeof(faculty));
	//	if (inFile.eof())
	//		break;
	//	facTree.insert(newFacNode, newFacNode.getID());
	//}

	//inFile.close();
}

void facultyTree::printTree(treeNode<faculty> *n)
{
	if (n != NULL)
	{
		printTree(n->left);
		n->element.printFacInfo();
		printTree(n->right);
	}
}


int facultyTree::assignNewAdvisor(string major)
{

	for (int i = 0; i < MaxAdviseeListSize; ++i)
	{
		//get specific node from the faculty tree 
		treeNode<faculty>* facultyNode = facTree.getNode(facultyIDList[i]);

		//access info within the specific node (faculty)
		faculty facMember = facultyNode->element;
		//now able to use specific functions to get data within the treenode
		if (major == facMember.getDepartment())
		{
			//check the list of advisees 
			//if its open, return that advisor ID 
			for (int i = 0; i < facMember.adviseeListSize; i++)
			{
				if (facMember.studentAdviseeList[i] == 0)
					return facMember.getID();
			}
		}
		
	}
	return 0;
	//make method that does similar function as print but instead of printing, check data to see if 
	//major = department. if so, check list of advisees to see if there is space for new student
	//if space, return that faculty's ID 
}