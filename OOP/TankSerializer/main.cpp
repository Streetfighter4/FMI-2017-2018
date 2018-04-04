#include <iostream>
#include "Tank.h"
int main() {
    Tank tank("TankaNaAliiiiii", 10.0, 100.0);
    ofstream outFile ("Tanks.bin", std::ios::binary);
    tank.serialize(outFile);
    outFile.close();
    Tank tank1;
    ifstream inFile ("Tanks.bin" , std::ios::binary);
    tank1.deserialize(inFile);
    tank1.tankInfo();
    return 0;
}