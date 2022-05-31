#include <iostream>
#include <string>
#include <vector>

#include "header/moto.hpp"
#include "header/battery.hpp"
#include "header/cp.hpp"
#include "header/etb.hpp"

// TODO: quando finalizar o carregamento de uma bateria deve-se automaticamente
// desligar o charging do CP e outras condições

using namespace std;

void setupSimulation();
void runSimulation(int timeInSeconds);
void printInformation();

// Create variables used in the simulation
Battery batMoto(1000, 85);
Battery bat1(1001, 100), bat2(1002, 100), bat3(1003, 100);
Battery bat4(1004, 70),  bat5(1005, 60),  bat6(1006, 50);

Moto motoboy("Motoboy123456");

ETB etb(123, 7);


void setupSimulation(){
    etb.attachBatteryToCp(&bat1, 1);
    etb.attachBatteryToCp(&bat2, 2);
    etb.attachBatteryToCp(&bat3, 3);
    etb.attachBatteryToCp(&bat4, 4);
    etb.attachBatteryToCp(&bat5, 5);
    etb.attachBatteryToCp(&bat6, 6);
}

void printInformation(){
    cout.precision(2);

    cout << "Motorcycle plate: " << motoboy.getPlate() << "\n";
    cout << "Speed: " << motoboy.getSpeed() << "\n";

    if(motoboy.getBatteryAttached()){
        cout << "Attached battery UID: " << motoboy.getBattery()->getUid() << "\n";
        cout << "Motorcycle battery SoC: " << motoboy.getBattery()->getSoc() << "%\n\n";
    }else{
        cout << "Attached battery UID: None\n";
        cout << "Motorcycle battery SoC: None\n\n";
    }

    cout << "ETB ID: " << etb.getUid() << "\n";

    int cp_idx = 1;
    for(auto cp = etb.getCps().begin(); cp != etb.getCps().end(); ++cp){
        cp_idx++;

        if((*cp).getBatteryAttached()){
            cout << "CP " << cp_idx << ": [" << (*cp).getBattery()->getUid() << " | " << (*cp).getBattery()->getSoc() << " | " << (*cp).getCharging() << "]\n";
        }else{
            cout << "CP " << cp_idx << ": [ NONE | NONE | " <<  (*cp).getCharging() << "]\n";
        }
    }
}
