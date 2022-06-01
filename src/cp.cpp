#include <iostream>
#include <string>

#include "../header/battery.hpp"
#include "../header/cp.hpp"
#include "../header/etb.hpp"

using namespace std;

CP::CP(){
    charging = false;
    batteryAttached = false;
}

void CP::attachBattery(Battery * batteryToAttach){
    battery = batteryToAttach;  // ETB will verify if CP and battery are available
    batteryAttached = true;
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

string CP::getChargingStr(){
    if(charging)
        return "YES";
    else
        return " NO";
}

bool CP::hasBatteryAttached(){
    return batteryAttached;
}

Battery * CP::getBattery(){
    return battery;
}
