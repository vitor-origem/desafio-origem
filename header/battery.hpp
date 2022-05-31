#ifndef BATTERY_H

#define BATTERY_H

#include <iostream>
#include <string>

#include "../header/moto.hpp"
#include "../header/etb.hpp"

using namespace std;

union host_t{   // Host type (can either be a motorcycle or an ETB)
    Moto moto;
    ETB etb;
};

class Battery{
    private:
        long long int uid;
        float soc;
        host_t host;

        string hostAttached;    // Indicates if there is a host attached

    public:
        void attachMoto(Moto moto);
        void attachETB(ETB etb);
        void detachHost();

        long long int getUid();
        float getSoc();
        host_t * getHost();

        void updateSoc();

        void operator = (const Battery &B){
            uid = B.uid;
            soc = B.soc;
            host = B.host;
            hostAttached = B.hostAttached;
        }
};

#endif