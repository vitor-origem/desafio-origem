#ifndef CP_H

#define CP_H

#include <iostream>
#include <string>

#include "../header/moto.hpp"
#include "../header/etb.hpp"

using namespace std;

class CP{
    private:
        bool charging;
        Battery battery;
        bool batteryAttached;

    public:
        CP();
        CP(Battery * newBattery);

        void attachBattery(Battery * batteryToAttach);
        void detachBattery();
        void startCharge();
        void stopCharge();

        string getCharging();
        bool getBatteryAttached();
        Battery * getBattery();
};

#endif