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

void CP::detachBattery(){       // Detach the battery
    batteryAttached = false;
}

void CP::startCharge(){         // Start charging the associated battery
    charging = true;
}

void CP::stopCharge(){          // Stop charging the associated battery
    charging = false;
}

bool CP::getCharging(){         // Returns if the CP is charging
    return charging;
}

string CP::getChargingStr(){    // Returns if the CP is charging for print purposes
    if(charging)
        return "YES";
    else
        return " NO";
}

bool CP::hasBatteryAttached(){  // Returns if the CP has battery attached
    return batteryAttached;
}

Battery * CP::getBattery(){
    return battery;
}
