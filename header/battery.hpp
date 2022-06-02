#ifndef BATTERY_H

#define BATTERY_H

#include <iostream>
#include <string>

#include "../header/host.hpp"

using namespace std;


class Battery{
    private:
        long long int uid;
        float soc;              // State of charge
        Host * host;

        bool hostAttached;      // Indicates if there is a host attached

    public:
        Battery();
        Battery(long long int uid, float soc);

        void attachHost(Host * hostToAttach);
        void detachHost();

        long long int getUid();
        float getSoc();
        Host * getHost();
        bool hasHostAttached();

        void updateSoc();
};

#endif