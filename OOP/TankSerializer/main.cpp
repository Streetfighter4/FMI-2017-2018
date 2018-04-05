#include <iostream>
#include <fstream>
#include "Tank.h"
#include "Army.h"

using std::ofstream;
using std::cout;
using std::endl;

int main() {

    Tank tank1("TankaNaAli", 50.0, 100.0);
    ofstream oFile ("Tanks.bin", std::ios::binary | std::ios::app);
    tank1.serialize(oFile);
    oFile.close();

    Tank tank2("TankaNaAlii", 30.0, 100.0);
    Tank tank3("TankaNaAliii", 60.0, 100.0);
    Tank tank4("TankaNaAliiii", 55.5, 100.0);
    Tank tank5("TankaNaAliiiii", 10.0, 100.0);
    Army alisArmy(5);

    alisArmy.addTank(tank1);
    alisArmy.addTank(tank2);
    alisArmy.addTank(tank3);
    alisArmy.addTank(tank4);
    alisArmy.addTank(tank5);
    ofstream outFile ("AlisArmy.bin", std::ios::binary | std::ios::app);
    cout << "1" << endl;
    alisArmy.serializeArmy(outFile);
    cout << "5" << endl;
    oFile.close();

    Tank tank6("TankaNaYasen", 40.0, 100.0);
    Tank tank7("TankaNaYasenn", 80.0, 100.0);
    Tank tank8("TankaNaYasennn", 12.3, 100.0);
    Tank tank9("TankaNaYasennnn", 31.4, 100.0);
    Tank tank10("TankaNaYasennnnn", 60.0, 100.0);

    Army yasensArmy(5);

    yasensArmy.addTank(tank6);
    yasensArmy.addTank(tank7);
    yasensArmy.addTank(tank8);
    yasensArmy.addTank(tank9);
    yasensArmy.addTank(tank10);


    alisArmy.attack(tank7);

    return 0;
}