#ifndef HOST_H

#define HOST_H

#include <iostream>
#include <string>

using namespace std;

class Host{
    protected:
        string type;

    public:
        string getType(){return type;}

        // Declaring some methods to use in battery class
        virtual string getState(){return "";}
        virtual float getSpeed(){return 0;}
};

#endif