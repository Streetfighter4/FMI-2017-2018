#include <iostream>
#include <string.h>

struct book{
	char name[31];
	char* author;
};

struct student{
	unsigned int fn;
	book* studentBook;
};

int main(){
	book b1;
	std::cin.getline(b1.name, 30);
	strcpy(b1.author, "Author Name");
	student s;
	s.fn = 12345;
	s.studentBook = &b1;
	student* studentList[30];
	studentList[0] = &s;
	std::cout << studentList[0]->studentBook->author << std::endl;

	return 0;
}
