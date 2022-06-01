#include <iostream>
#include <string>
#include <vector>

#include "../header/cp.hpp"
#include "../header/etb.hpp"

using namespace std;

ETB::ETB(long int newUid, int numCps){
    type = "ETB";
    
    uid = newUid;
    
    for(int i = 0; i < numCps; i++)
        cps.push_back(CP());
}

int ETB::getNumBatteries(){
    int numBatteries = 0;

    for(auto cp = cps.begin(); cp != cps.end(); ++cp){
        if((*cp).hasBatteryAttached())
            numBatteries++;
    }

    return numBatteries;
}

int ETB::getNumCharging(){
    int numCharging = 0;

    for(auto cp = cps.begin(); cp != cps.end(); ++cp){
        if((*cp).getCharging() == "YES")
            numCharging++;
    }

    return numCharging;
}

void ETB::attachBatteryToCp(Battery * battery, int numCp){
    if(!battery->hasHostAttached() && !cps.at(numCp-1).hasBatteryAttached()){
        cps.at(numCp-1).attachBattery(battery);
        battery->attachHost(this);
    }
}

void ETB::startChargeCp(int numCp){
    if(this->getNumCharging() < MAX_CPS_CHARGING)
        cps.at(numCp-1).startCharge();
}

void ETB::stopChargeCp(int numCp){
    cps.at(numCp-1).stopCharge();
}

void ETB::detachBatteryFromCp(int numCp){
    cps.at(numCp-1).getBattery()->detachHost();
    cps.at(numCp-1).detachBattery();
}

int ETB::timeLeftCharging(int numCp){
    if(cps.at(numCp-1).hasBatteryAttached()){
        float batterySoc = cps.at(numCp-1).getBattery()->getSoc();
        return (100 - batterySoc)*20;  // time in seconds needed to complete the charge of the battery
    }else{
        return 0;   // no battery attached to the corresponding CP
    }
}


long int ETB::getUid(){
    return uid;
}

vector<CP> & ETB::getCps(){
    return cps;
}


void ETB::update(){
    //automaticChargeControl();

    for(auto cp = cps.begin(); cp != cps.end(); ++cp){
        if((*cp).hasBatteryAttached() && (*cp).getCharging() == "YES")
            (*cp).getBattery()->updateSoc();
    }
}

void ETB::automaticChargeControl(){
    int cp_idx = 0;
    for(auto cp = cps.begin(); cp != cps.end(); ++cp){
        cp_idx++;

        if((*cp).hasBatteryAttached() && (*cp).getCharging() == "NO"){
            if((*cp).getBattery()->getSoc() < 100 && this->getNumCharging() < MAX_CPS_CHARGING)
                startChargeCp(cp_idx);
        }
    }

    cp_idx = 0;
    for(auto cp = cps.begin(); cp != cps.end(); ++cp){
        cp_idx++;

        if((*cp).hasBatteryAttached() && (*cp).getCharging() == "YES"){
            if((*cp).getBattery()->getSoc() == 100)
                stopChargeCp(cp_idx);
        }
    }
}
