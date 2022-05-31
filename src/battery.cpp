#include <iostream>
#include <string>
#include <cmath>

#include "../header/battery.hpp"
#include "../header/moto.hpp"

using namespace std;


void Battery::attachMoto(Moto moto){    // Attach a motorcycle as the battery's host
    hostAttached = "Moto";
    host.moto = moto;
}

void Battery::attachETB(ETB etb){       // Attach an ETB as the battery's host
    hostAttached = "ETB";
    host.etb = etb;
}

void Battery::detachHost(){     // Detach the host of the battery
    hostAttached = "None";
}

long long int Battery::getUid(){    // Get the battery's UID
    return uid;
}

float Battery::getSoc(){    // Get the battery's state of charge
    return soc;
}

host_t * Battery::getHost(){    // Returns a pointer to the battery's host
    if(hostAttached == "Moto")
        return (host_t *) &(host.moto);
    else if(hostAttached == "ETB")
        return (host_t *) &(host.etb);
}

void Battery::updateSoc(){      // Iterate one second in the simulation
    if(hostAttached == "Moto"){
        if(host.moto.getState() == "Standby"){
            soc -= 0.01;
        }else{
            soc -= (0.01 + 0.05*pow(host.moto.getSpeed()/MAX_SPEED, 2));
        }
    }else if(hostAttached == "ETB"){    // Add verification if the CP is actually charging the battery
        soc += 0.05;
    }
}
