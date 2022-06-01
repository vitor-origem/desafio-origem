#include <iostream>
#include <string>
#include <vector>
#include <cstdio>

#include "header/battery.hpp"
#include "header/cp.hpp"
#include "header/moto.hpp"
#include "header/etb.hpp"

#define PRINT_INTERVAL 10

using namespace std;

void setupSimulation();
void runSimulation(int timeInSeconds);
void printInformation();
void timestamp(int timeInSeconds);

// Create variables used in the simulation
Battery batMoto(1000, 85);
Battery bat1(1001, 100), bat2(1002, 100), bat3(1003, 100);
Battery bat4(1004, 70),  bat5(1005, 60),  bat6(1006, 50);

Moto motoboy("ABC1234");

ETB etb(123, 7);

int totalTimeInSeconds = 0;

int main(){
    setupSimulation();

    motoboy.turnOn();

    for(int cycle = 0; cycle < 6; cycle++){
        motoboy.releaseBrake();
        motoboy.throttle();
        runSimulation(180);
        motoboy.brake();
        runSimulation(10);
    }

    for(int cycle = 0; cycle < 4; cycle++){
        motoboy.releaseBrake();
        motoboy.throttle();
        runSimulation(120);
        motoboy.brake();
        runSimulation(12);
    }

    motoboy.releaseBrake();
    motoboy.throttle();
    runSimulation(100);
    motoboy.brake();
    runSimulation(32);    

    motoboy.turnOff();
    motoboy.detachBattery();
    etb.attachBatteryToCp(&batMoto, 7);

    runSimulation(10);

    etb.detachBatteryFromCp(1);
    motoboy.attachBattery(&bat1);

    runSimulation(30);

    return 0;
}


void setupSimulation(){
    motoboy.attachBattery(&batMoto);

    etb.attachBatteryToCp(&bat1, 1);
    etb.attachBatteryToCp(&bat2, 2);
    etb.attachBatteryToCp(&bat3, 3);
    etb.attachBatteryToCp(&bat4, 4);
    etb.attachBatteryToCp(&bat5, 5);
    etb.attachBatteryToCp(&bat6, 6);
}

void runSimulation(int timeInSeconds){
    for(int i = 0; i < timeInSeconds; i++){
        etb.automaticChargeControl();

        if(totalTimeInSeconds % PRINT_INTERVAL == 0)
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

    cout << "\n----------------------------------------------------------------------------\n\n";

    cout << "Time: "; timestamp(totalTimeInSeconds); cout << "\n\n";
    
    cout << "Motorcycle plate: " << motoboy.getPlate() << "\n";

    cout << "Speed: " << motoboy.getSpeed() << " km/h\n";

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
            cout << " | Battery SoC: "; printf("%6.2f", (*cp).getBattery()->getSoc());
            cout << " | Charging: " << (*cp).getChargingStr();
            cout << " | ETC: "; timestamp(etb.timeLeftCharging(cp_idx)); cout << "]\n";
        }else{
            cout << "CP " << cp_idx;
            cout << ": [Battery UID: NONE | Battery SoC:   NONE | Charging: " <<  (*cp).getChargingStr();
            cout << " | ETC:  NONE]\n";
        }
    }
}
