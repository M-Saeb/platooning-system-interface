#ifndef MASTER_INTERFACE_H
#define MASTER_INTERFACE_H

#include <iostream> 
#include <memory>
#include <thread> 
#include "../abstract/abstractLogger.h"
#include "../point/point.h"

using namespace std;

class MasterInterface: AbstractLogger{
public:
    MasterInterface():
        number(""),
        _isNull(true),
        AbstractLogger("NULL_MASTER")
        {
            commonInit();
        }


    MasterInterface(string number):
        number(number),
        masterLocation( make_shared<Point>(0.0, 0.0)),
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
        return *masterLocation;
    }

    void setLocation(Point p){
        Point oldLocation = *masterLocation;
        logger->info(
            "Updated location from {} to {}",
            oldLocation.toString(),
            p.toString()
        );
        *masterLocation = p;
    }

private:
    string number;
    shared_ptr<Point> masterLocation;
    bool _isNull = false;

    void commonInit(){
        logger->info("Initialized Master Interface {}", number);
    }

};

#endif
