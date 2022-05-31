#ifndef ETB_H

#define ETB_H

#include <iostream>
#include <string>
#include <vector>

#include "../header/moto.hpp"
#include "../header/etb.hpp"
#include "../header/cp.hpp"

using namespace std;

#define MAX_CPS_CHARGING 6

class ETB{
    private:
        long int uid;
        vector<CP> cps;
    public:
        void attachBatteryToCp(Battery * battery, int numCp);
        void startChargeCp(int numCp);
        void stopChargeCp(int numCp);
        void detachBatteryFromCp(int numCp);
        int getNumBatteries();
        int getNumCharging();
        int timeLeftCharging(int numCp);
        
        long int getUid();
        vector<CP> getCps();
};

#endif