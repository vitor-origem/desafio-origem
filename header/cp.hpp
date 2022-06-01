#ifndef CP_H

#define CP_H

#include <iostream>
#include <string>

#include "../header/battery.hpp"

using namespace std;

class CP{
    private:
        bool charging;
        Battery * battery;
        bool batteryAttached;

    public:
        CP();

        void attachBattery(Battery * batteryToAttach);
        void detachBattery();
        void startCharge();
        void stopCharge();

        string getCharging();
        bool hasBatteryAttached();
        Battery * getBattery();
};

#endif