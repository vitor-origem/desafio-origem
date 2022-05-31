#ifndef BATTERY_H

#define BATTERY_H

#include <iostream>
#include <string>

#include "../header/moto.hpp"
#include "../header/etb.hpp"

using namespace std;

union host_t{
    Moto moto;
    ETB etb;
};

class Battery{
    long long int uid;
    float soc;
    host_t host;

    public:
        long long int getUid();
};

#endif