#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <string.h>

using namespace std;

typedef unsigned int u_int;

const char* exclamations[] = {"SHOK", "SKANDAL", "Nechuvana naglost", "Udivitelno", 
								"Nqma da povqrvate", "Ujas po sofiiskite ulici"};
const u_int exclamationsCount = 6;
const char* objects[] = {"Rqpa ", "Baba ", "Kmet ", "Bager ", "Sklad ", 
						 "Sarma ", "Skitnik ", "Magazin ", "Kartina ", "Pokriv ",
						 "Skior ", "Kashon ", "Qke ", "Ohrana ", "Kontakt "};
const u_int objectsCount = 15;
const char* subjects[] = {"rqpa.", "baba.", "kmet.", "bager ", "elha ",
						  "kosachka ", "komputar ", "kaska ", "odealo ", "kotka ",
						  "kofa za bokluk", "durvo ", "Jumbo ", "shapka ", "benzinostanciq "};
const u_int subjectsCount = 15;
const char* actions[] = {"sgazi ", "zadiga ", "namiga na ", "precakva ", "tirashi ",
						 "obezglavqva ", "zamerq ", "si lqga s ", "narqzva ", "vzima nazaem "};
const u_int actionsCount = 10;

const char* generateExclamation() {
	u_int index = rand()%exclamationsCount;
	return exclamations[index];
}

const char* generateObject() {
	u_int index = rand()%objectsCount;
	return objects[index];
}

const char* generateSubject() {
	u_int index = rand()%subjectsCount;
	return subjects[index];
}

const char* generateAction() {
	u_int index = rand()%actionsCount;
	return actions[index];
}

int main() {
	srand(time(NULL));
	u_int headingsCount;
	cout << "Enter the number of headings: ";
	cin >> headingsCount;
	for (u_int j = 0; j < headingsCount; j++) {
		const char* exclamation = generateExclamation();	
		const char* object = generateObject();
		const char* subject = generateSubject();
		const char* action = generateAction();
		u_int numExc = rand()%7 + 3;
		char* headings = new(nothrow) char[strlen(exclamation) + strlen(object) + strlen(subject) + strlen(action) + numExc];
		if(headings) {	
			strcpy(headings, exclamation);
			for(u_int i = 0; i < numExc; i++) {
				strcat(headings, "!");
			}
			strcat(headings, object);
			strcat(headings, action);
			strcat(headings, subject);
			cout << headings << endl;
		} else {
			cout << "No memory for allock!" << endl;
		}
		delete[] headings;
	}
	return 0;
}
