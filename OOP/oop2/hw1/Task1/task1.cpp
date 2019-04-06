#include <iostream>
#include <string.h>
#include <fstream>

#define MAX_SIZE 1<<5
struct Car {
private:
	char brand[MAX_SIZE];
	char model[MAX_SIZE];
	unsigned int price;
public:
	void serialize(std::ofstream&) const;
	void deserialize(std::ifstream&);
	const char* getBrand() const;
	const char* getModel() const;
	unsigned int getPrice() const;
public:
	Car() = default;
	Car(const char*, const char*, unsigned int);
};


Car::Car(const char* new_brand, const char* new_model, unsigned int new_price) : price(new_price) {
	strcpy(brand, new_brand);
	strcpy(model, new_model);
}

void Car::serialize(std::ofstream& ofs) const {
	ofs.write((const char*)this, sizeof(Car));
}

void Car::deserialize(std::ifstream& ifs) {
	ifs.read((char*)this, sizeof(Car));
}

const char* Car::getBrand() const {
	return brand;
}

const char* Car::getModel() const {
	return model;
}

unsigned int Car::getPrice() const {
	return price;
}

void serializationCars(const char* fileName) {	
	Car c1("Hennessey", "Venom_GT", 2500500);
	Car c2("Bugatti", "Chiron", 3000000);
	Car c3("SCC", "Ultimate_Aero", 2000000);
	Car c4("Tesla", "Roadster", 2400000);
	Car c5("Saleen", "S7_Twin_Turbo", 2600000);	
	Car c6("Koenigsegg", "Agera_RS", 3100000);
	Car c7("Hennessey", "Venom_F5", 2800500);
	Car c8("Bugatti", "Veyron_Super_Sport", 3200000);
	Car c9("Koenigsegg", "CCR", 2300000);
	Car c10("MClaren", "F1", 2500000);

	size_t size = 10;
	std::ofstream ofs(fileName, std::ios::binary);
	if(ofs.is_open()) {
		ofs.write((const char*)&size, sizeof(size));
		c1.serialize(ofs);	
		c2.serialize(ofs);	
		c3.serialize(ofs);	
		c4.serialize(ofs);	
		c5.serialize(ofs);	
		c6.serialize(ofs);	
		c7.serialize(ofs);	
		c8.serialize(ofs);	
		c9.serialize(ofs);	
		c10.serialize(ofs);	
	}
	ofs.close();
}

void getOddCars(const char* binaryFileName, const char* textFileName) {
	std::ifstream ifs(binaryFileName, std::ios::binary);
	std::ofstream ofs(textFileName);	
	if(ifs.is_open() && ofs.is_open()) {
		Car buffer;
		
		size_t size;
		ifs.read((char*)&size, sizeof(size));
		ofs << size/2 << "\n";
		while(!ifs.eof()) {
			buffer.deserialize(ifs);
			if(ifs.eof()) {
				break;
			}	
			ofs << buffer.getBrand() << ' ' << buffer.getModel() << ' ' << buffer.getPrice() << "\n";
			ifs.seekg(sizeof(Car), std::ios::cur);
		}
	}
	ifs.close();
	ofs.close();
}

void sortingCarsByPrice(Car**& cars, size_t size) {
	int minIndex;
	for(int i = 0; i < size - 1; ++i) {
		minIndex = i;
		for(int j = i + 1; j < size; ++j) {
			if(cars[j]->getPrice() < cars[minIndex]->getPrice()) {
				minIndex = j;
			}
		}
		if(minIndex != i) {	
			std::swap(cars[minIndex], cars[i]);
		}
	}
}

void printModels(Car**& cars, size_t size) {
	for(int i = 0; i < size; ++i) {
		std::cout << cars[i]->getModel() << std::endl;
	}
}

void freeMemory(Car**& cars, size_t size) {	
	for(int i = 0; i < size; ++i) {
		delete cars[i];	
	}
	delete[] cars;
}

void getCarsFromFileAndSortThem(const char* fileName) {	
	Car** cars;
	size_t size;
	std::ifstream ifs(fileName);

	char brand[MAX_SIZE];
	char model[MAX_SIZE];
	unsigned int price;
	int index = 0;

	if(ifs.is_open()) {
		ifs >> size;
		cars = new Car*[size];	
		
		while(!ifs.eof()) {
			ifs >> brand >> model >> price;
			
			if(ifs.eof()) {
				break;
			}
			cars[index++] = new Car(brand, model, price);

			memset(brand, 0, MAX_SIZE);
			memset(model, 0, MAX_SIZE);
		}	

	}
	ifs.close();

	sortingCarsByPrice(cars, size);
	printModels(cars, size);
	freeMemory(cars, size);
}

int main() {
	const char* binaryFileName = "binaryFileCars.bin";
	const char* textFileName = "textFileCars.txt";
	serializationCars(binaryFileName);
	getOddCars(binaryFileName, textFileName);
	getCarsFromFileAndSortThem(textFileName);
	return 0;
}
