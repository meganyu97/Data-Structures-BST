#ifndef PERSON_H
#define PERSON_H

#include <iostream>
using namespace std;

class person
{
private:
	int ID;
	string name;
	string level;
public:
	person();
	person(int ID, string name, string level);

	int getID() const;
	string getName();
	string getLevel();

	void setID(int ID);
	void setName(string name);
	void setLevel(string level);

};

#endif
