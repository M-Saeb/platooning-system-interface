#ifndef MASTER_INTERFACE_H
#define MASTER_INTERFACE_H

#include <iostream> 
#include <thread> 
#include "../abstract/abstractLogger.h"
#include "../point/point.h"

using namespace std;

class MasterInterface: AbstractLogger{
public:
    MasterInterface(): number(""), AbstractLogger("NO_NUMBER"){}


    MasterInterface(string number):
        number(number),
        masterLocation(0.0, 0.0),
        AbstractLogger(number)
        {}

    virtual ~MasterInterface();

    string getNumber(){
        return number;
    }

    Point getLocation(){
        return masterLocation;
    }

    void setLocation(Point p){
        masterLocation = p;
    }

private:
    string number;
    Point masterLocation;

};

#endif
