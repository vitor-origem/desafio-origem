#ifndef MOTO_H

#define MOTO_H

#include <iostream>
#include <string>

#include "../header/battery.hpp"

using namespace std;

class Moto{
    private:
        string plate;
        float speed;
        Battery battery;

        string state;
        bool hasBattery;
        bool brakeOn;
        bool throttleOn;

    public:
        void turnOn();
        void turnOff();
        void attachBattery(Battery batteryToAttach);
        void detachBattery(Battery batteryToDetach);
        void throttle();
        void brake();
        void freeBrake();

        string getState();
        string getPlate();
        float getSpeed();
        long long int Moto::getBattery();

        void increaseSpeed();
        void reduceSpeed();

        void iterTime();
};

#endif
