#ifndef CP_H

#define CP_H

#include <iostream>
#include <string>

#include "../header/battery.hpp"

using namespace std;

class CP{
    private:
        bool charging;          // Indicates if the CP is charging the battery
        Battery * battery;
        bool batteryAttached;

    public:
        CP();

        void attachBattery(Battery * batteryToAttach);
        void detachBattery();
        void startCharge();
        void stopCharge();

        bool getCharging();
        string getChargingStr();
        bool hasBatteryAttached();
        Battery * getBattery();
};

#endif