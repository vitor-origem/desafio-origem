#include <iostream>
#include <string>

#include "../header/moto.hpp"
#include "../header/battery.hpp"

using namespace std;

Moto::Moto(string newPlate){
    type = "Motorcycle";
    plate = newPlate;
}

void Moto::turnOn(){    // Turn the motorcycle on
    state = "On";
}

void Moto::turnOff(){   // Turn the motorcycle off
    state = "Standby";
}

void Moto::attachBattery(Battery batteryToAttach){
    if(!batteryAttached){
        battery = batteryToAttach;
        batteryAttached = true;
    }
}

void Moto::detachBattery(){     // Detach the battery of the motorcycle
    batteryAttached = false;
    // TODO: alterar o estado da bateria para Idle
}

void Moto::throttle(){  // Turn on the motorcycle's throttle
    if(!brakeOn)
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

Battery * Moto::getBattery(){   // Get the attached battery's UID
    return &battery;
}

string Moto::getState(){    // Get the state of the motorcycle
    return state;
}

bool Moto::getBatteryAttached(){
    return batteryAttached;
}

void Moto::increaseSpeed(){     // Increase the motorcycle's speed
    speed += 0.2;

    if(speed > MAX_SPEED)
        speed = MAX_SPEED;
}

void Moto::reduceSpeed(){       // Decrease the motorcycle's speed
    speed -= 2;

    if(speed < 0)
        speed = 0;
}

void Moto::updateSpeed(){     // Iterate one second in the simulation
    if(brakeOn){
        reduceSpeed();
    }else if(throttleOn){
        increaseSpeed();
    }   // If neither brake or throttle are on, the speed stays the same
}
