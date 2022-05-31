#include <iostream>
#include <string>

#include "../header/battery.hpp"
#include "../header/moto.hpp"
#include "../header/cp.hpp"

using namespace std;

CP::CP(){
    charging = false;
    batteryAttached = false;
}

CP::CP(Battery * newBattery){
    attachBattery(newBattery);
    charging = false;
    batteryAttached = false;
}

void CP::attachBattery(Battery * batteryToAttach){
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

string CP::getCharging(){
    if(charging)
        return "YES";
    else
        return "NO";
}

bool CP::getBatteryAttached(){
    return batteryAttached;
}

Battery * CP::getBattery(){
    return &battery;
}
