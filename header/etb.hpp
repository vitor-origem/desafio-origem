#ifndef ETB_H

#define ETB_H

#include <iostream>
#include <string>
#include <vector>

#include "../header/host.hpp"
#include "../header/cp.hpp"
#include "../header/battery.hpp"

using namespace std;

#define MAX_CPS_CHARGING 6

class ETB : public Host{
    private:
        long int uid;
        vector<CP> cps;
    public:
        ETB(long int newUid, int numCps);

        void attachBatteryToCp(Battery * battery, int numCp);
        void startChargeCp(int numCp);
        void stopChargeCp(int numCp);
        void detachBatteryFromCp(int numCp);
        int getNumBatteries();
        int getNumCharging();
        int timeLeftCharging(int numCp);
        
        long int getUid();
        vector<CP> & getCps();

        void update();
        void automaticChargeControl();
};

#endif