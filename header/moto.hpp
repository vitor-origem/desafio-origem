#ifndef MOTO_H

#define MOTO_H

#define MAX_SPEED 60    // Definition of the maximum speed of the motorcycle

#include <iostream>
#include <string>

#include "../header/host.hpp"
#include "../header/battery.hpp"

using namespace std;

class Moto : public Host{
    private:
        string plate;       // "Unique" id of the motorcycle
        float speed;
        Battery battery;

        string state;           // Indicates if the motorcycle is on or standby
        bool batteryAttached;   // Indicates if there is any battery attached to the motorcycle
        bool brakeOn;           // Indicates if the brakes are being pressed
        bool throttleOn;        // Indicates if the throttle is being pressed

    public:
        Moto(string plate);
        
        void turnOn();
        void turnOff();
        void attachBattery(Battery * batteryToAttach);
        void detachBattery();
        void throttle();
        void brake();
        void releaseBrake();

        string getState();
        string getPlate();
        float getSpeed();
        Battery * Moto::getBattery();
        bool getBatteryAttached();

        void increaseSpeed();
        void reduceSpeed();

        void updateSpeed();
};

#endif
