#include <iostream>
#include <string>

#include "../header/battery.hpp"
#include "../header/moto.hpp"
#include "../header/cp.hpp"

using namespace std;

void CP::attachBaterry(Battery * batteryToAttach){
    if(!batteryAttached){
        battery = *batteryToAttach;
        batteryAttached = true;
    }
}

void CP::detachBattery(){
    batteryAttached = false;
}

void CP::startCharge(){
    charging = true;
}

void CP::stopCharge(){
    charging = false;
}

bool CP::getCharging(){
    return charging;
}

bool CP::getBatteryAttached(){
    return batteryAttached;
}

Battery * CP::getBattery(){
    return &battery;
}
