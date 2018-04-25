#pragma once
#include "Soldier.h"

class Commander : public Soldier {
	Soldier* army;
	size_t sizeArmy;
	size_t capArmy;
	char* moto;
public:
	Commander();
	Commander(size_t capArmy);
	~Commander();
};

