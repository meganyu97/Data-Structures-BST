#include "faculty.h"
#include <string>

string faculty::getDepartment()
{
	return department;
}

void faculty::setDepartment(string department)
{
	this->department = department;
}

int* faculty::getAdvisees()
{
	return studentAdviseeList;
}

int faculty::getAdviseeListSize()
{
	return adviseeListSize;
}

int faculty::getStudent(int n)
{
	return studentAdviseeList[n];
}

void faculty::setAdvisee(int id)
{
	if (adviseeListSize == MaxAdviseeListSize)
		cout << "Faculty not accepting students at this time" << endl;
	else
	{
		for (int i = 0; i < MaxAdviseeListSize; ++i)
		{
			if (studentAdviseeList[i] == 0)
			{
				adviseeListSize++;
				studentAdviseeList[i] = id;
				break;
			}
		}
	}
}

void faculty::removeAdvisee(int id)
{
	for (int i = 0; i < 50 ; ++i)
	{
		if (studentAdviseeList[i] == id)
		{
			studentAdviseeList[i] = 0;
			adviseeListSize--;
			cout << "Advisee removed from Faculty: " << this->getName() << "ID: " << this->getID() << "from dept: " << this->getDepartment() << endl;
			break;
		}
		else
			cout << "Advisee not found " << endl;
	}
}

faculty::faculty()
{
	department = "";
	studentAdviseeList = new int[MaxAdviseeListSize]();
	adviseeListSize = 0; //50;
}

faculty::faculty(int ID, string name, string level, string department) : person(ID, name, level)
{
	setDepartment(department);
	studentAdviseeList = new int[MaxAdviseeListSize]();
	adviseeListSize = 0; // 50;
}

faculty::~faculty()
{
	//delete[] studentAdviseeList;
}

void faculty::printFacInfo()
{
	cout<< "Faculty ID: "<<getID()<<endl;
	cout << "Name: " << getName() << endl;
	cout<< "Level: "<<getLevel()<<endl;
	cout<<"Department: "<< getDepartment() <<endl;
	cout << getAdviseeListSize() << endl;
	int adviseeSize = getAdviseeListSize();
	cout << "Advisee IDs:" << endl;
	for (int i = 0; i < adviseeSize; ++i)
		cout << getStudent(i) << endl;

}

bool faculty::operator==(const faculty& f)
{
	return this->getID() == f.getID();
}

bool faculty::operator!=(const faculty& f )
{
	return !(this->getID() == f.getID());
}

bool faculty::operator<(const faculty& f)
{
	return this->getID() < f.getID();
}

bool faculty::operator>(const faculty& f)
{
	return this->getID() > f.getID();
}

void faculty::writeFacultyToFile(std::ofstream& file) {
	file << this->getID() << endl;
	file << this->getName() << endl;
	file << this->getLevel() << endl;
	file << this->getDepartment() << endl;
	file << this->getAdviseeListSize() << endl;
	int adviseeSize = this->getAdviseeListSize();
	for (int i = 0; i < adviseeSize; ++i) 
		file << this->getStudent(i) << endl;
}

void faculty::addStudent(int id) {
	if (adviseeListSize >= MaxAdviseeListSize) 
		cout << "Cannot hold anymore students.\n";
	else {
		adviseeListSize++;
		for (int i = 0; i < MaxAdviseeListSize; ++i) {
			//if (studentAdviseeList[i] == 0) {
			  if (*(studentAdviseeList + i) == 0) {
				studentAdviseeList[i] = id;
				break;
			}
		}
	}
}

void faculty::removeStudent(int id) {
	int temp, check = 0;
	for (int i = 0; i < MaxAdviseeListSize; ++i) {
		temp = studentAdviseeList[i];
		if (temp == id) {
			studentAdviseeList[i] = 0;
			check = 1;
			adviseeListSize--;
		}
		if (check == 1) break;
	}
	if (check == 0) cout << "Student not found under this advisor.\n";
	else cout << "Student has been removed from advisor. \n";
}