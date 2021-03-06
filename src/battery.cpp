#include <iostream>
#include <string>
#include <cmath>

#include "../header/battery.hpp"
#include "../header/host.hpp"
#include "../header/moto.hpp"

using namespace std;

Battery::Battery(){
    uid = 0;
    soc = 0;
    hostAttached = false;
}

Battery::Battery(long long int newUid, float newSoc){
    uid = newUid;
    soc = newSoc;
    hostAttached = false;
}

bool Battery::hasHostAttached(){
    return hostAttached;
}

void Battery::attachHost(Host * hostToAttach){    // Attach a motorcycle as the battery's host
    if(!hostAttached){
        hostAttached = true;
        host = hostToAttach;
    }
}

void Battery::detachHost(){     // Detach the host of the battery
    hostAttached = false;
}

long long int Battery::getUid(){    // Get the battery's UID
    return uid;
}

float Battery::getSoc(){    // Get the battery's state of charge
    return soc;
}

Host * Battery::getHost(){    // Returns a pointer to the battery's host
    return host;
}

void Battery::updateSoc(){      // Iterate one second in the simulation

    if(host->getType() == "Moto"){
        if(host->getState() == "Standby"){      // Motorcycle is off (standby mode)
            soc -= 0.01;
        }else{                                  // Motorcycle is on (additional spent of charge)
            float socDiff = 0.05*pow(host->getSpeed()/(float) MAX_SPEED, 2);
            soc -= (0.01 + socDiff);
        }
    }else if(host->getType() == "ETB"){    // Verification if the CP is charging -> done in ETB::update()
        soc += 0.05;
    }

    // Limits of the battery's charge
    if(soc > 100)
        soc = 100;
    else if(soc < 0)
        soc = 0;
}
