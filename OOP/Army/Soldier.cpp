#include "Soldier.h"
#include <string.h>


void Soldier::copyFrom(const Soldier& other)
{
	name = new char[strlen(other.name) + 1];
	strcpy(this->name, other.name);
	age = other.age;
	skills = other.skills;
	price = other.price;
}

Soldier::Soldier() : name(nullptr), age(0), skills(0), price(0) {}

Soldier::Soldier(char* name, unsigned int age, int skills, float price) : age(age), skills(skills), price(price) {
	this->name = new char[strlen(name) + 1];
	strcpy(this->name, name);
}

Soldier::Soldier(const Soldier& other) {
	copyFrom(other);
}

Soldier& Soldier::operator=(const Soldier& other)
{
	if (this != &other) {
		delete[] name;
		copyFrom(other);
	}
	return *this;
}


Soldier::~Soldier()
{
	delete[] name;
}
