#ifndef TRIP_H
#define TRIP_H

#include <iostream> 
#include <vector>
#include <thread>
#include <random>
#include <iomanip>
#include <sstream>
#include <unordered_map>
#include <windows.h>
#include "../abstract/abstractLogger.h"
#include "../slaveInterface/slaveInterface.h"
#include "../masterInterface/masterInterface.h"
#include "../point/point.h"
#include "../util/utils.h"

using namespace std;

enum class State{
    INIT,
    IN_PROGRESS,
    DONE
};



class Trip: AbstractLogger{
public:
    // Declare the destructor
    Trip():
        number("NOVALUE"),
        AbstractLogger("NULL_TRIP")
        {
            commonInit();
        }

    ~Trip();

    Trip(string number, MasterInterface masterInt):
        number(number),
        master(masterInt),
        AbstractLogger(number)
        {
            commonInit();
        }

    Trip(const Trip& other) :
        state(other.state),
        number(other.number),
        master(other.master),
        slaves(other.slaves),
        masterLocationHistory(other.masterLocationHistory),
        AbstractLogger(number){
        commonInit(); // You may need to adjust this based on your specific needs
    }

    static Trip createTrip(string masterId);

    Trip& operator=(const Trip& other) {
        if (this != &other) {
            // Release resources if needed
            // ...

            // Copy member variables
            state = other.state;
            number = other.number;
            master = other.master;
            slaves = other.slaves;
            masterLocationHistory = other.masterLocationHistory;

            commonInit(); // You may need to adjust this based on your specific needs
        }
        return *this;
    }

    string getNumber(){
        return number;
    }

    void addSlave(string slaveId){
        SlaveInterface slave(slaveId);
        slaves.push_back(slave);
        logger->info("added slave numbered {}", slave.getNumber());
    }

    void startTrip(){
        state = State::IN_PROGRESS;
        logger->info("Trip started !");
        for(SlaveInterface& slave: slaves){
            slave.startThread();
        }
    }

    void endTrip(){
        state = State::DONE;
        logger->info("Trip ended.");
        for(SlaveInterface& slave: slaves){
            slave.endThread();
        }
    }

    Point updateMasterLocation(){
        Point point(master.getLocation());
        logger->info("got new location {}, {}", point.longitude, point.latitude);
        masterLocationHistory.push_back(point);
        return point;
    }

    vector<Point> getMasterPath(){
        return masterLocationHistory;
    }

private:
    State state;
    string number;
    MasterInterface master;
    vector<SlaveInterface> slaves;
    vector<Point> masterLocationHistory;
    unordered_map<
        string,
        vector<Point>
    > trips;

    thread getMasterLocationThread;

    void commonInit(){
        state = State::INIT;
        logger->info("Initialized Trip {}", number);
    }

    // static void theMasterLocationThread(Trip* trip){
    //     trip->logger->info("started runMasterLocationThread", trip->number);

    //     while(trip->state == State::IN_PROGRESS){
    //         trip->updateMasterLocation();
    //         this_thread::sleep_for(chrono::seconds(1));
    //     }
    //     trip->logger->info("ended runMasterLocationThread", trip->number);
    // }

};

#endif