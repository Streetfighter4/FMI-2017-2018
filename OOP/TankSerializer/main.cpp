#include <iostream>
#include "Tank.h"
int main() {
    Tank tank("TankaNaAli", 10.0, 100.0);
    std::cout << "1" << std::endl;
    ofstream outFile ("Tanks.bin", std::ios::binary);
    std::cout << "2" << std::endl;
    tank.serialize(outFile);

    std::cout << "8" << std::endl;
    Tank tank1;
    ifstream inFile ("Tanks.bin" , std::ios::binary);
    tank1.deserialize(inFile);
    tank1.tankInfo();
    return 0;
}