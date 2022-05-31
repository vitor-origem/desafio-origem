#include <iostream>
#include <string>
#include <format>

#include "../header/battery.hpp"
#include "../header/moto.hpp"

using namespace std;

#define MAX_SPEED 60


void Moto::turnOn(){
    state = "On";
}

void Moto::turnOff(){
    state = "Standby";
}

void Moto::attachBattery(Battery batteryToAttach){
    battery = batteryToAttach;
    hasBattery = true;
}

void Moto::detachBattery(Battery batteryToDetach){
    hasBattery = false;
}

void Moto::throttle(){
    if(!brakeOn)
        throttleOn = true;
}

void Moto::brake(){
    throttleOn = false;
    brakeOn = true;
}

void Moto::freeBrake(){
    brakeOn = false;
}

string Moto::getPlate(){
    return plate;
}

float Moto::getSpeed(){
    return speed;
}

long long int Moto::getBattery(){
    return battery.getUid();
}

string Moto::getState(){
    return state;
}

void Moto::increaseSpeed(){
    speed += 0.2;

    if(speed > MAX_SPEED)
        speed = MAX_SPEED;
}

void Moto::reduceSpeed(){
    speed -= 2;

    if(speed < 0)
        speed = 0;
}

void Moto::iterTime(){
    if(brakeOn){
        reduceSpeed();
    }else if(throttleOn){
        increaseSpeed();
    }
}
