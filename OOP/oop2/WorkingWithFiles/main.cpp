#include <iostream>
#include <fstream>
#include <cstring>


struct Student {
    unsigned int fn;
    char* name;
    char* family;
    double mark;
    Student(unsigned int, const char*, const char*, double);
    ~Student();
};

Student::Student(unsigned int fn, const char* name, const char* family, double mark) : fn(fn), mark(mark){

    this->name = new char[strlen(name) + 1];
    this->family = new char[strlen(family) + 1];

    strcpy(this->name, name);
    strcpy(this->family, family);
}

Student::~Student() {
    delete[] name;
    delete[] family;
}

int main () {
    /*
     *task1
    std::ifstream ifs("text.txt");


    ifs.seekg(7, std::ios::beg);
    std::cout << (char)ifs.get() << std::endl;

    ifs.seekg(-6, std::ios::end);
    std::cout << (char)ifs.get() << std::endl;

    ifs.seekg(3, std::ios::cur);
    std::cout << (char)ifs.get() << std::endl;
    ifs.seekg(0, std::ios::end);
    std::cout << ifs.tellg() << std::endl;

    ifs.close();
   */

    const int max_students = 4;
    Student yasen(45460, "Yasen", "Alexiev", 6.00);
    Student sian(45325, "Sian", "Donchev", 5.90);
    Student gabi(45389, "Gabriela", "Velcheva", 5.80);
    Student ali(45432, "Alexandra", "Stoyanova", 2.00);
    Student* students[max_students] = {&yasen, &sian, &gabi, &ali};

    std::ofstream ofs("students.bin", std::ios::binary);
    for(int i = 0; i < max_students; ++i) {
        ofs.write((const char*)students[i], sizeof(Student));
    }
    ofs.close();
    std::ifstream ifs("students.bin", std::ios::binary);
    ofs.open("students.txt", std::ios::trunc);
    for(int i = 0; i < max_students; ++i) {
        ifs.read((char*)students[i], sizeof(Student));
    }
    int minIndex;
    for (int j = 0; j < max_students-1; ++j) {
        minIndex = j;
        for (int i = j+1; i < max_students; ++i) {
            if(students[i]->mark < students[minIndex]->mark) {
                minIndex = i;
            }
        }
        std::swap(students[j], students[minIndex]);
    }

    for (int i = 0; i < max_students; ++i) {
        ofs << students[i]->fn << ' ' << students[i]->name << ' ' << students[i]->family << ' ' << students[i]->mark << std::endl;
    }

    ifs.close();
    ofs.close();


    return 0;
}
