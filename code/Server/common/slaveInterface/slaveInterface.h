#ifndef SLAVE_INTERFACE_H
#define SLAVE_INTERFACE_H

#include <iostream> 
#include <memory>
#include <thread> 
#include <mutex> 
#include <atomic>
#include <windows.h>

#include "../point/point.h"
#include "../abstract/abstractLogger.h"

using namespace std;

class SlaveInterface: AbstractLogger{
public:
    SlaveInterface(
        string number
    ):
        number(number),
        masterLocation(make_shared<Point>()),
        slaveLocation(make_shared<Point>()),
        pathToMaster(make_shared<vector<Point>>()),
        AbstractLogger(number)
        {
            commmonInit();
        }

    SlaveInterface(
        string number,
        Point initMasterLocation,
        Point initSlaveLocation
    ):
        number(number),
        masterLocation(make_shared<Point>(initMasterLocation)),
        slaveLocation(make_shared<Point>(initSlaveLocation)),
        pathToMaster(make_shared<vector<Point>>()),
        AbstractLogger(number)
        {
            commmonInit();
        }

    SlaveInterface(const SlaveInterface& other) :
        number(other.number),
        masterLocation(make_shared<Point>(other.getMasterLocation())),
        slaveLocation(make_shared<Point>(other.getSlaveLocation())),
        pathToMaster(make_shared<vector<Point>>(other.getCurrentPathToMaster())),
        runThreadFlag(other.runThreadFlag.load()),
        AbstractLogger(other.number)
        {}

    SlaveInterface& operator=(const SlaveInterface& other) {
        if (this != &other) {
            // Custom copy assignment logic here
            number = other.number;
            masterLocation = make_shared<Point>(other.getMasterLocation());
            slaveLocation = make_shared<Point>(other.getSlaveLocation());
            pathToMaster = make_shared<vector<Point>>(other.getCurrentPathToMaster());
            runThreadFlag.store(other.runThreadFlag.load());
        }
        return *this;
    }

    virtual ~SlaveInterface();

    void updateMasterLocation(Point newLocation){
        Point currentLocation = *masterLocation;
        logger->info("Updated master location");
        *masterLocation = newLocation;
    }

    void updateSlaveLocation(Point newLocation){
        Point currentLocation = *slaveLocation;
        logger->info(
            "updated slave location from {} to {}",
            currentLocation.toString(),
            newLocation.toString()
        );
        *slaveLocation = newLocation;

    }

    void startThread(){
        {
            lock_guard<mutex> lock(mutex_);
            runThreadFlag.store(true, memory_order_relaxed);
            // runThreadFlag = true;
        } // lock_guard goes out of scope and releases the lock before starting the thread
        auto threafFunc = [this](){
            this->slaveToMasterThread();
        };
        thread newThread(threafFunc);
        instanceThread = make_unique<thread>(move(newThread));
    }

    void endThread(){
        {
            lock_guard<mutex> lock(mutex_);
            runThreadFlag.store(false, memory_order_relaxed);
            // runThreadFlag = false;
        } // lock_guard goes out of scope and releases the lock before joining the thread
        if (instanceThread && instanceThread->joinable()) {
            instanceThread->join();
        }
    }

    string getNumber(){
        return number;
    }

    Point getMasterLocation() const {
        return *masterLocation;
    }

    Point getSlaveLocation() const {
        return *slaveLocation;
    }

    vector<Point> getCurrentPathToMaster() const{
        return *pathToMaster;
    }

private:
    string number;
    shared_ptr<Point> masterLocation;
    shared_ptr<Point> slaveLocation;
    shared_ptr<vector<Point>> pathToMaster;
    atomic<bool> runThreadFlag = false;
    unique_ptr<thread> instanceThread;
    mutable mutex mutex_;


    void commmonInit(){
        logger->info("Initialized Slave Interface {}", number);
    }

    void addPointToPath(const Point& p){
        vector<Point> currentVector = *pathToMaster;
        currentVector.push_back(p);
        pathToMaster = make_shared<vector<Point>>(currentVector);
    }

    void popPointFromPath(){
        vector<Point> currentVector = *pathToMaster;
        currentVector.erase(currentVector.begin());
        pathToMaster = make_shared<vector<Point>>(currentVector);
    }

    bool isThreadRunning() const {
        return runThreadFlag.load(std::memory_order_relaxed);
    }

    void slaveToMasterThread();

};

#endif
