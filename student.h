#ifndef STUDENT_H
#define STUDENT_H

#include <fstream>
#include "person.h"
using namespace std;

class student:public person
{
private:
	string major;
	double GPA;
	int advisorID;
public:
	student();
	student(int ID, string name, string level, string major, double GPA, int advisorID);

	string getMajor();
	double getGPA();
	int getAdvisorID();

	void setMajor(string major);
	void setGPA(double GPA);
	void setAdvisorID(int advisorID);

	bool operator==(const student& other);
	bool operator<(const student& other);
	bool operator>(const student& other);
	bool operator!=(const student& other);

	void printStdInfo();

	void writeStudentsToFile(ofstream& file);
};

#endif 