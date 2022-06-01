#include <iostream>
#include <string>

#include "../header/moto.hpp"
#include "../header/battery.hpp"

using namespace std;

Moto::Moto(string newPlate){
    type = "Moto";
    plate = newPlate;
}

void Moto::turnOn(){    // Turn the motorcycle on
    if(batteryAttached && battery->getSoc() > 0)
        state = "On";
}

void Moto::turnOff(){   // Turn the motorcycle off
    if(speed == 0)      // Motorcycle must be stopped to turn off
        state = "Standby";
}

void Moto::attachBattery(Battery * batteryToAttach){
    if(!batteryAttached && !batteryToAttach->hasHostAttached()){
        battery = batteryToAttach;
        batteryAttached = true;
        battery->attachHost(this);
    }
}

void Moto::detachBattery(){     // Detach the battery of the motorcycle
    batteryAttached = false;
    battery->detachHost();
    // TODO: alterar o estado da bateria para Idle
}

void Moto::throttle(){  // Turn on the motorcycle's throttle
    if(!brakeOn && state == "On")
        throttleOn = true;
}

void Moto::brake(){         // Turn on the motorcycle's brakes
    throttleOn = false;     // Turning the brakes on blocks the throttle
    brakeOn = true;
}

void Moto::releaseBrake(){  // Release the motorcycle's brakes
    brakeOn = false;
}

string Moto::getPlate(){    // Get the plate number of the motorcycle
    return plate;
}

float Moto::getSpeed(){     // Get the speed of the motorcycle
    return speed;
}

Battery * Moto::getBattery(){   // Get the attached battery
    return battery;
}

string Moto::getState(){    // Get the state of the motorcycle
    return state;
}

bool Moto::hasBatteryAttached(){
    return batteryAttached;
}

void Moto::increaseSpeed(){     // Increase the motorcycle's speed
    if(battery->getSoc() > 0)
        speed += 0.2;

    if(speed > MAX_SPEED)
        speed = MAX_SPEED;
}

void Moto::reduceSpeed(){       // Decrease the motorcycle's speed
    speed -= 2;

    if(speed < 0)
        speed = 0;
}

void Moto::update(){     // Iterate one second in the simulation
    if(brakeOn){
        reduceSpeed();
    }else if(throttleOn){
        increaseSpeed();
    }   // If neither brake or throttle are on, the speed stays the same

    if(batteryAttached)
        battery->updateSoc();
}
