#ifndef SLAVE_INTERFACE_H
#define SLAVE_INTERFACE_H

#include <iostream> 
#include <memory>
#include <thread> 
#include "../point/point.h"
#include "../abstract/abstractLogger.h"

using namespace std;

class SlaveInterface: AbstractLogger{
public:
    SlaveInterface(
        string number
    ):
        number(number),
        AbstractLogger(number)
        {}

    SlaveInterface(
        string number,
        Point initMasterLocation,
        Point initSlaveLocation
    ):
        number(number),
        masterLocation(initMasterLocation),
        slaveLocation(initSlaveLocation),
        AbstractLogger(number)
        {}

    SlaveInterface(const SlaveInterface& other) :
        SlaveInterface(
            other.number,
            other.masterLocation,
            other.slaveLocation
        ){
    }

    SlaveInterface& operator=(const SlaveInterface& other) {
        if (this != &other) {
            // Custom copy assignment logic here
            number = other.number;
            masterLocation = other.masterLocation;
            slaveLocation = other.slaveLocation;
            pathToMaster = other.pathToMaster;
            runThreadFlag = false;
        }
        return *this;
    }

    virtual ~SlaveInterface();

    void updateMasterLocation(Point newLocation){
        masterLocation = newLocation;
    }

    void updateSlaveLocation(Point newLocation){
        slaveLocation = newLocation;
    }

    void startThread(){
        runThreadFlag = true;
        thread newThread(
            &SlaveInterface::slaveToMasterThread, this
        );
        instanceThread = make_unique<thread>(move(newThread));
    }

    void endThread(){
        runThreadFlag = false;
        if (instanceThread && instanceThread->joinable()) {
            instanceThread->join();
        }
    }

    vector<Point> getCurrentPathToMaster(){
        return pathToMaster;
    }

    string getNumber(){
        return number;
    }

private:
    string number;
    Point masterLocation;
    Point slaveLocation;
    vector<Point> pathToMaster;
    bool runThreadFlag = false;
    unique_ptr<thread> instanceThread;

    void addPointToPath(Point p){
        pathToMaster.push_back(p);
    }

    void popPointFromPath(){
        pathToMaster.erase(pathToMaster.begin());
    }

    static void slaveToMasterThread(SlaveInterface* s){
        s->logger->info("Started thread");
        Point currentMasterLocation = s->masterLocation;
        Point currentSlaveLocation = s->slaveLocation;
        while(s->runThreadFlag){
            if (s->masterLocation != currentMasterLocation){
                currentMasterLocation = s->masterLocation;
                s->addPointToPath(currentMasterLocation);
            }
            if (s->slaveLocation != currentSlaveLocation){
                currentMasterLocation = s->slaveLocation;
                s->popPointFromPath();
            }
        }
        s->logger->info("Ended thread");
    }

};

#endif
