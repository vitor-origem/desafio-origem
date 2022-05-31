#include <iostream>
#include <string>
#include <vector>

#include "../header/moto.hpp"
#include "../header/etb.hpp"
#include "../header/cp.hpp"
#include "../header/etb.hpp"

using namespace std;

int ETB::getNumBatteries(){
    int numBatteries = 0;

    for(auto cp = cps.begin(); cp != cps.end(); ++cp){
        if((*cp).getBatteryAttached())
            numBatteries++;
    }
}

int ETB::getNumCharging(){
    int numCharging = 0;

    for(auto cp = cps.begin(); cp != cps.end(); ++cp){
        if((*cp).getCharging())
            numCharging++;
    }
}

void ETB::attachBatteryToCp(Battery * battery, int numCp){
    cps.at(numCp).attachBaterry(battery);
}

void ETB::startChargeCp(int numCp){
    if(this->getNumCharging() < MAX_CPS_CHARGING)
        cps.at(numCp).startCharge();
}

void ETB::stopChargeCp(int numCp){
    cps.at(numCp).stopCharge();
}

void ETB::detachBatteryFromCp(int numCp){
    cps.at(numCp).detachBattery();
}

int ETB::timeLeftCharging(int numCp){
    if(cps.at(numCp).getBatteryAttached()){
        float batterySoc = cps.at(numCp).getBattery()->getSoc();
        return (100 - batterySoc)/0.05;  // time in seconds needed to complete the charge of the battery
    }else{
        return 0;   // no battery attached to the corresponding CP
    }
}


long int ETB::getUid(){
    return uid;
}

vector<CP> ETB::getCps(){
    return cps;
}
