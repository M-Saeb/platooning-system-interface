#ifndef MASTER_INTERFACE_H
#define MASTER_INTERFACE_H

#include <iostream> 
#include <thread> 
#include "../abstract/abstractLogger.h"
#include "../point/point.h"

using namespace std;

class MasterInterface: AbstractLogger{
public:
    // MasterInterface():
    //     number(""),
    //     AbstractLogger("NO_NUMBER")
    //     {
    //         commonInit();
    //     }


    MasterInterface(string number):
        number(number),
        masterLocation(0.0, 0.0),
        AbstractLogger(number)
        {
            commonInit();
        }

    virtual ~MasterInterface();


    MasterInterface& operator=(const MasterInterface& other) {
        number = other.number;
        masterLocation = other.masterLocation;
        return *this;
    }


    string getNumber(){
        return number;
    }

    Point getLocation(){
        return masterLocation;
    }

    void setLocation(Point p){
        logger->info(
            "Updated location from {} to {}",
            masterLocation.toString(),
            p.toString()
        );
        masterLocation = p;
    }

private:
    string number;
    Point masterLocation;

    void commonInit(){
        logger->info("Initialized Master Interface {}", number);
    }

};

#endif
