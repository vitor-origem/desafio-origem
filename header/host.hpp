#ifndef HOST_H

#define HOST_H

#include <iostream>
#include <string>
#include <vector>

#include "../header/moto.hpp"
#include "../header/battery.hpp"
#include "../header/cp.hpp"
#include "../header/etb.hpp"

// TODO: quando finalizar o carregamento de uma bateria deve-se automaticamente
// desligar o charging do CP e outras condições

using namespace std;

class Host{
    protected:
        string type;

    public:
        string getType(){return type;}

        // Just declaring some methods to use in battery class
        string getState();
        float getSpeed();
};

#endif