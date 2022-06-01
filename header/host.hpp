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

        // Just declaring some methods to use in battery class
        string getState(){return "";}
        float getSpeed(){return 0;}
};

#endif