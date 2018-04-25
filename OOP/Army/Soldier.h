#pragma once
class Soldier {
	char* name;
	unsigned int age;
	int skills;
	float price;

	void copyFrom(const Soldier&);
public:
	Soldier();
	Soldier(char* name, unsigned int age, int skills, float price);
	Soldier(const Soldier&);
	Soldier& operator=(const Soldier&);

	~Soldier();
};

