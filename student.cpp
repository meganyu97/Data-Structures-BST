#include "student.h"
#include <string>

student::student()
{
	major = "";
	GPA = 0.0;
	advisorID = 0;
}

student::student(int ID, string name, string level, string major, double GPA, int advisorID) : person(ID, name, level)
{
	setMajor(major);
	setGPA(GPA);
	setAdvisorID(advisorID);
}

string student::getMajor()
{
	return major;
}

double student::getGPA()
{
	return GPA;
}

int student::getAdvisorID()
{
	return advisorID;
}

void student::setMajor(string major)
{
	this->major = major;
}

void student::setGPA(double GPA)
{
	this->GPA = GPA;
}

void student::setAdvisorID(int advisorID)
{
	this->advisorID = advisorID;
}

bool student::operator==(const student& f)
{
	return this->getID() == f.getID();
}

bool student::operator!=(const student& f)
{
	return !(this->getID() == f.getID());
}

bool student::operator<(const student& f)
{
	return this->getID() < f.getID();
}

bool student::operator>(const student& f)
{
	return this->getID() > f.getID();
}

void student::printStdInfo()
{
	cout << "ID: " << getID() << endl;
	cout << "Name: " << getName() << endl;
	cout << "Level: " << getLevel() << endl;
	cout << "Major: " << getMajor() << endl;
	cout << "GPA: " << getGPA() << endl;
	cout << "Advisor ID: " << getAdvisorID() << endl;
}

void student::writeStudentsToFile(ofstream& file) {	
	file << this->getID() << endl;				
	file << this->getName() << endl;
	file << this->getLevel() << endl;
	file << this->getMajor() << endl;
	file << this->getGPA() << endl;
	file << this->getAdvisorID() << endl;
}