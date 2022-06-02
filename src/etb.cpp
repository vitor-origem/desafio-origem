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

int ETB::getNumBatteries(){     // Returns the number of batteries in the ETB
    int numBatteries = 0;

    for(auto cp = cps.begin(); cp != cps.end(); ++cp){
        if((*cp).hasBatteryAttached())
            numBatteries++;
    }

    return numBatteries;
}

int ETB::getNumCharging(){      // Returns the number of batteries being charged in the ETB
    int numCharging = 0;

    for(auto cp = cps.begin(); cp != cps.end(); ++cp){
        if((*cp).getCharging())
            numCharging++;
    }

    return numCharging;
}

void ETB::attachBatteryToCp(Battery * battery, int numCp){  // Attach a battery to the CP
    if(!battery->hasHostAttached() && !cps.at(numCp-1).hasBatteryAttached()){
        cps.at(numCp-1).attachBattery(battery);
        battery->attachHost(this);
    }
}

void ETB::startChargeCp(int numCp){     // Begin charging battery at CP
    if(this->getNumCharging() < MAX_CPS_CHARGING)
        cps.at(numCp-1).startCharge();
}

void ETB::stopChargeCp(int numCp){      // Stop charging battery at CP
    cps.at(numCp-1).stopCharge();
}

void ETB::detachBatteryFromCp(int numCp){       // Detach a battery to the CP
    cps.at(numCp-1).getBattery()->detachHost();
    cps.at(numCp-1).detachBattery();
}

int ETB::timeLeftCharging(int numCp){       // Returns the time in seconds left to complete charge
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
    for(auto cp = cps.begin(); cp != cps.end(); ++cp){
        if((*cp).hasBatteryAttached() && (*cp).getCharging())
            (*cp).getBattery()->updateSoc();
    }
}

void ETB::automaticChargeControl(){     // Automatically start and stop the charge of the batteries
    int cp_idx = 0;
    for(auto cp = cps.begin(); cp != cps.end(); ++cp){
        cp_idx++;

        if((*cp).hasBatteryAttached() && !(*cp).getCharging()){
            if((*cp).getBattery()->getSoc() < 100 && this->getNumCharging() < MAX_CPS_CHARGING)
                startChargeCp(cp_idx);
        }
    }

    cp_idx = 0;
    for(auto cp = cps.begin(); cp != cps.end(); ++cp){
        cp_idx++;

        if((*cp).hasBatteryAttached() && (*cp).getCharging()){
            if((*cp).getBattery()->getSoc() == 100)
                stopChargeCp(cp_idx);
        }
    }
}
