#ifndef FACULTY_H
#define FACULTY_H

#include "person.h"
#include <fstream>
using namespace std;

#define MaxAdviseeListSize 50

class faculty:public person
{
private:
	string department;

public:

	faculty();
	faculty(int ID, string name, string level, string department);

	~faculty();

	int* studentAdviseeList;
	int adviseeListSize;

	string getDepartment();
	void setDepartment(string department);

	int getAdviseeListSize();
	int* getAdvisees();
	void setAdvisee(int id);

	int getStudent(int n);
	void removeAdvisee(int id);

	void addStudent(int id);
	void removeStudent(int id);

	bool operator==(const faculty& other);
	bool operator<(const faculty& other);
	bool operator>(const faculty& other);
	bool operator!=(const faculty& other);

	void printFacInfo();

	void writeFacultyToFile(ofstream& file);

};

#endif