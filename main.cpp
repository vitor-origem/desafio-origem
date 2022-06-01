#include <iostream>
#include <string>
#include <vector>
#include <cstdio>

#include "header/battery.hpp"
#include "header/cp.hpp"
#include "header/moto.hpp"
#include "header/etb.hpp"

// TODO: quando finalizar o carregamento de uma bateria deve-se automaticamente
// desligar o charging do CP e outras condições

using namespace std;

void setupSimulation();
void runSimulation(int timeInSeconds);
void printInformation();
void timestamp(int timeInSeconds);

// Create variables used in the simulation
Battery batMoto(1000, 85);
Battery bat1(1001, 100), bat2(1002, 100), bat3(1003, 100);
Battery bat4(1004, 70),  bat5(1005, 60),  bat6(1006, 50);

Moto motoboy("Motoboy123456");

ETB etb(123, 7);

int totalTimeInSeconds = 0;

int main(){
    setupSimulation();
    runSimulation(50);
    return 0;
}


void setupSimulation(){
    motoboy.attachBattery(&batMoto);
    motoboy.turnOn();
    motoboy.throttle();

    etb.attachBatteryToCp(&bat1, 1);
    etb.attachBatteryToCp(&bat2, 2);
    etb.attachBatteryToCp(&bat3, 3);
    etb.attachBatteryToCp(&bat4, 4);
    etb.attachBatteryToCp(&bat5, 5);
    etb.attachBatteryToCp(&bat6, 6);
}

void runSimulation(int timeInSeconds){
    for(int i = 0; i < timeInSeconds; i++){
        if(totalTimeInSeconds % 10 == 0)
            printInformation();

        motoboy.update();
        etb.update();

        totalTimeInSeconds++;
    }
}

void timestamp(int timeInSeconds){
    int minutes = timeInSeconds / 60;
    int seconds = timeInSeconds - minutes*60;
    printf("%02d:%02d", minutes, seconds);
}

void printInformation(){
    cout.precision(2);
    cout << fixed;

    cout << "\n--------------------------\n\n";

    cout << "Time: "; timestamp(totalTimeInSeconds); cout << "\n\n";
    
    cout << "Motorcycle plate: " << motoboy.getPlate() << "\n";

    cout << "Speed: " << motoboy.getSpeed() << "\n";

    if(motoboy.hasBatteryAttached()){
        cout << "Attached battery UID: " << motoboy.getBattery()->getUid() << "\n";
        cout << "Motorcycle battery SoC: " << motoboy.getBattery()->getSoc() << "%\n\n";
    }else{
        cout << "Attached battery UID: None\n";
        cout << "Motorcycle battery SoC: None\n\n";
    }

    cout << "ETB ID: " << etb.getUid();
    cout << " | Num Batteries: " << etb.getNumBatteries();
    cout << " | Num Charging: " << etb.getNumCharging() << "\n";

    int cp_idx = 0;

    for(auto cp = etb.getCps().begin(); cp != etb.getCps().end(); ++cp){
        cp_idx++;

        if((*cp).hasBatteryAttached()){
            cout << "CP " << cp_idx;
            cout << ": [Battery UID: " << (*cp).getBattery()->getUid();
            cout << " | Battery SoC: " << (*cp).getBattery()->getSoc();
            cout << " | Charging: " << (*cp).getCharging();
            cout << " | ETC: "; timestamp(etb.timeLeftCharging(cp_idx)); cout << "]\n";
        }else{
            cout << "CP " << cp_idx;
            cout << ": [Battery UID: NONE | Battery SoC: NONE | Charging: " <<  (*cp).getCharging();
            cout << " | ETC: NONE]\n";
        }
    }
}
