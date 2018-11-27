#include "person.h"

person::person()
{
	ID = 0;
	name = "";
	level = "";
}

person::person(int ID, string name, string level)
{
	setID(ID);
	setName(name);
	setLevel(level);
}

int person::getID() const
{
	return ID;
}

string person::getName()
{
	return name;
}

string person::getLevel()
{
	return level;
}

void person::setID(int ID)
{
	this->ID = ID;
}

void person::setName(string name)
{
	this->name = name;
}

void person::setLevel(string level)
{
	this->level = level;
}