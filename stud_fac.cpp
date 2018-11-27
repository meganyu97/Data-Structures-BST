// stud_fac.cpp : Defines the entry point for the console application.
//
#include "treeNode.h"
#include "bst.h"
#include "student.h"
#include "faculty.h"
#include "studentTree.h"
#include "facultyTree.h"
#include "GenStack.h"
#include <string>
#include <fstream>

facultyTree masterFaculty;
studentTree masterStudent;

GenStack<studentTree> studentStack(5);
GenStack<facultyTree> facultyStack(5);

void printMenu();
void case1_printStud();
void case2_printFac();
void case3_displayStudInfo();
void case4_displayFacInfo();
void case5_studFacInfo();
void case6_facAdvInfo();
void case7_addStud();
void case8_delStud();
void case9_addNewFac();
void case10_delFac();
void case11_studNewFac();
void case12_remAdvFromFac();
void case13_rollback();

int main()
{

	ifstream iSt("studentTable.txt");
	if (iSt.is_open())
	{
		masterStudent.loadStudentTreeFromFile("studentTable.txt");
		iSt.close();
	}

	ifstream iFac("facultyTable.txt");
	if (iFac.is_open())
	{
		masterFaculty.loadFacultyTreeFromFile("facultyTable.txt");
		iFac.close();
	}

	bool inMenu = true;
	while (inMenu)
	{
		int userChoice;
		printMenu();

		cin >> userChoice;

		switch (userChoice)
		{
		case 1: {
			// create object of bst of type student and in the instance of that object call on inOrderPrint by key
			case1_printStud();
			break;
		}

		case 2: {
			// create object of bst of type faculty and in the instance of that object call on inOrderPrint by key
			case2_printFac();
			break;
		}

		case 3: {
			// similar input as case 5 but print everything in the element instead of just facID
			case3_displayStudInfo();
			break;
		}

		case 4: {
			case4_displayFacInfo();
			break;
		}

		case 5: {
			case5_studFacInfo();
			break;
		}

		case 6: {
			// given fac ID, print list and info of all their advisees
			// make sure facID exists
			// access list of advisee's ID's similar to accessing the list of faculty IDs in case 7
			// for each advisee ID, create an object of type student that can access the node element in the tree
			// once in the element, print out all the details
			case6_facAdvInfo();
			break;
		}

		case 7: {
			//add a new student
			//take in new student's ID, major, level, etc.
			//make sure the ID entered doesnt already belong to a student
			// go into faculty tree to find an advisor who's department = new student's major
			// check faculty nodes in same dept to see if advisee list still has room for more students
			// if so, return that faculty's ID and go back to student tree and make that the advisor ID 
			// do we need to balance the tree after adding new person?? 
			case7_addStud();
			break;
		}

		case 8: {
			// delete student given ID
			case8_delStud();
			break;
		}

		case 9: {
			//add new faculty member
			// check to make sure that facID doesnt already belong to someone
			// ADD NEW FACULTY ID TO LIST OF ID NUMBERS 
			// take in rest of info for new fac
			// use object of bst.h (facTree?) to call on insert function
			// balance tree?
			case9_addNewFac();
			break;
		}

		case 10: {
			//delete faculty member given ID 
			case10_delFac();
			break;
		}

		case 11: {
			//change student's advisor given ID and new facID
			// check student ID inputted to make sure student exists 
			case11_studNewFac();
			break;
		}

		case 12: {
			// remove an advisee from a faculty given the ids
			case12_remAdvFromFac();
			break;
		}

		case 13: {
			//rollback
			case13_rollback();
			break;
		}

		case 14: {
			inMenu = false;
			break;
		}

		default: {
			cout << "Incorrect input.\n";
			cin.clear();
			while (cin.get() != '\n') continue;
			break;
		}

		}

		masterStudent.serializeStudent();
		masterFaculty.serializeFaculty();
	}
}



void printMenu()
{
	cout << endl << endl;
	cout << "1. Print all students and information." << endl
		<< "2. Print all faculty and information." << endl
		<< "3. Find and display specific student." << endl
		<< "4. Find and display specific faculty." << endl
		<< "5. Find and display student's advisor information." << endl
		<< "6. Find and display faculty's advisees information." << endl
		<< "7. Add a new student." << endl
		<< "8. Delete a student." << endl
		<< "9. Add a new faculty member." << endl
		<< "10. Delete a faculty member." << endl
		<< "11. Change a student's advisor." << endl
		<< "12. Remove a faculty's advisee." << endl
		<< "13. Rollback changes." << endl
		<< "14. Exit." << endl << endl
		 << endl;
}

void case1_printStud()
{
	masterStudent.printTree(masterStudent.getRoot());
}

void case2_printFac()
{
	masterFaculty.printTree(masterFaculty.getRoot());
}

void case3_displayStudInfo()
{
	int studentID;
	cout << "Enter the student ID you wish to display: " << endl;
	while (!(cin >> studentID))
	{
		cin.clear();
		while (cin.get() != '\n') continue;
		cout << "Invalid student ID, Please enter a valid ID: " << endl;
	}

	cout << endl;
	//cin.ignore();

	if (masterStudent.getStudentNode(studentID) == NULL)
	{
		cout << "The student ID does not exist." << endl;
		return;
	}

	masterStudent.printStudent(studentID);
}

void case4_displayFacInfo()
{
	int facultyID;
	cout << "Enter the faculty ID you wish to display: " << endl;
	while (!(cin >> facultyID))
	{
		cin.clear();
		while (cin.get() != '\n') continue;
		cout << "Invalid faculty ID, Please enter a valid ID: " << endl;
	}

	cout << endl;
	//cin.ignore();
	if (masterFaculty.getFacultyNode(facultyID) == NULL)
	{
		cout << "The faculty ID does not exist." << endl;
		return;
	}
	masterFaculty.printFaculty(facultyID);

}

void case5_studFacInfo()
{
	int studentID;
	cout << "Enter the student ID you wish to find the advisor of: ";
	while (!(cin >> studentID))
	{
		cin.clear();
		while (cin.get() != '\n') continue;
		cout << "Invalid student ID, Please enter a valid ID: " << endl;
	}
	cout << endl;
	//cin.ignore();

	if (masterStudent.getStudentNode(studentID) == NULL)
	{
		cout << "student ID does not exist - look up failed! ." << endl;
		return;
	}

	int facultyID = masterStudent.getStudentAdvisor(studentID);
	cout << "Advisor information for student " << studentID << ": " << endl;
	masterFaculty.printFaculty(facultyID);

}

void case6_facAdvInfo()
{
	int facultyID;
	cout << "Enter the faculty ID to look up advisee(s): ";
	while (!(cin >> facultyID))
	{
		cin.clear();
		while (cin.get() != '\n') continue;
		cout << "Invalid faculty ID, Please enter a valid ID: " << endl;
	}
	cout << endl;
	//cin.ignore();

	if (masterFaculty.getFacultyNode(facultyID) == NULL)
	{
		cout << "The faculty ID does not exist - look up failed!" << endl;
		return;
	}

	int* facultyAdvisees = masterFaculty.getFacultyAdvisees(facultyID);

	cout << "Advisees' information for this faculty " << facultyID << ": " << endl;

	int numAdvisees = masterFaculty.getNumAdvisees(facultyID);
	for (int i = 0; i < numAdvisees; ++i)
	{
		if (facultyAdvisees[i] != 0)
		{
			if (masterStudent.getStudentNode(facultyAdvisees[i]) == NULL) continue;
			masterStudent.printStudent(facultyAdvisees[i]);
		}
	}

}

void case7_addStud()
{
	studentStack.push(masterStudent);
	facultyStack.push(masterFaculty);

	if (masterFaculty.getRoot() == NULL)
	{
		cout << "No advisors available. Unable to add new student." << endl;
		return;
	}

	int studentID = masterStudent.addNewStudent();

	if (masterFaculty.getFacultyNode(masterStudent.getStudentAdvisor(studentID)) == NULL)
	{
		cout << "The advisor does not exist, redo the entry." << endl;
		masterStudent.deleteStudent(studentID);
		return;
	}
	masterFaculty.addAdvisee(masterStudent.getStudentAdvisor(studentID), studentID);
	cout << "Student has been assigned an advisor." << endl;
	cout << "Student added." << endl;

}

void case8_delStud()
{
	studentStack.push(masterStudent);
	facultyStack.push(masterFaculty);

	int studentID;
	cout << "Enter the student ID to be deleted: ";
	while (!(cin >> studentID))
	{
		cin.clear();
		while (cin.get() != '\n') continue;
		cout << "Invalid student ID, Please enter a valid ID: " << endl;
	}
	cout << endl;
	//cin.ignore();

	if (masterStudent.getStudentNode(studentID) == NULL)
	{
		cout << "The student ID does not exist - look up failed!" << endl;
		return;
	}

	masterFaculty.removeAdvisee(masterStudent.getStudentAdvisor(studentID), studentID);
	masterStudent.deleteStudent(studentID);
	cout << "Student removed" << endl;

}

void case9_addNewFac()
{
	studentStack.push(masterStudent);
	facultyStack.push(masterFaculty);

	masterFaculty.addFaculty();

}

void case10_delFac()
{
	studentStack.push(masterStudent);
	facultyStack.push(masterFaculty);

	int facultyID;
	cout << "Enter the faculty ID to be deleted: ";
	while (!(cin >> facultyID))
	{
		cin.clear();
		while (cin.get() != '\n') continue;
		cout << "Invalid faculty ID, Please enter a valid ID: " << endl;
	}
	cout << endl;
	//cin.ignore();

	if (masterFaculty.getFacultyNode(facultyID) == NULL)
	{
		cout << "The faculty ID does not exist." << endl;
		return;
	}

	int* facultyAdvisees = masterFaculty.getFacultyAdvisees(facultyID);

	masterFaculty.deleteFaculty(facultyID);
	cout << "Faculty deleted." << endl;

	int numAdvisees = masterFaculty.getNumAdvisees(facultyID);

	for (int i = 0; i < numAdvisees; ++i)
	{
		if (facultyAdvisees == NULL) return;
		else if (facultyAdvisees[i] != 0)
		{
			masterStudent.changeStudentAdvisor(facultyAdvisees[i], masterFaculty.getRoot()->element.getID());
			masterFaculty.addAdvisee(masterFaculty.getRoot()->element.getID(), facultyAdvisees[i]);
		}
	}
	cout << "Advisees have been assigned another advisor." << endl;

}

void case11_studNewFac()
{
	studentStack.push(masterStudent);
	facultyStack.push(masterFaculty);

	int studentID, facultyID;
	cout << "Enter the student whose advisor is being changed: ";
	while (!(cin >> studentID))
	{
		cin.clear();
		while (cin.get() != '\n') continue;
		cout << "Invalid student ID, Please enter a valid ID: " << endl;
	}

	if (masterStudent.getStudentNode(studentID) == NULL)
	{
		cout << "The student ID does not exist, look up failed." << endl;
		return;
	}

	cout << "Enter the new advisor ID: ";
	while (!(cin >> facultyID))
	{
		cin.clear();
		while (cin.get() != '\n') continue;
		cout << "Invalid faculty ID, Please enter a valid ID: " << endl;
	}
	cout << endl;
	//cin.ignore();

	if (masterFaculty.getFacultyNode(facultyID) == NULL)
	{
		cout << "The faculty ID does not exist in this tree." << endl;
		return;
	}

	masterFaculty.removeAdvisee(masterStudent.getStudentAdvisor(studentID), studentID);
	masterStudent.changeStudentAdvisor(studentID, facultyID);
	masterFaculty.addAdvisee(facultyID, studentID);

	cout << "Student assigned to a new Advisor." << endl;

}

void case12_remAdvFromFac()
{
	studentStack.push(masterStudent);
	facultyStack.push(masterFaculty);

	int facultyID, studentID;
	cout << "To remove student, enter the faculty ID for the adivsor: ";
	while (!(cin >> facultyID))
	{
		cin.clear();
		while (cin.get() != '\n') continue;
		cout << "Invalid faculty ID, Please enter a valid ID: " << endl;
	}
	cout << endl;
	//cin.ignore();

	if (masterFaculty.getFacultyNode(facultyID) == NULL)
	{
		cout << "The faculty ID does not exist in this tree." << endl;
		return;
	}

	cout << "Enter the student you are removing: ";
	while (!(cin >> studentID))
	{
		cin.clear();
		while (cin.get() != '\n') continue;
		cout << "Invalid student ID, Please enter a valid ID: " << endl;
	}
	cout << endl;
	//cin.ignore();

	if (masterStudent.getStudentNode(studentID) == NULL)
	{
		cout << "The student ID does not exist, look up failed!." << endl;
		return;
	}

	masterStudent.changeStudentAdvisor(studentID, masterFaculty.getRoot()->element.getID());
	masterFaculty.removeAdvisee(facultyID, studentID);

	cout << "Student removed from advisor's list of students." << endl;

}

void case13_rollback()
{
	masterStudent = studentStack.pop();
	masterFaculty = facultyStack.pop();

}


