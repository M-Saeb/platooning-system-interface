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

    ~Trip();

    Trip(string n, shared_ptr<MasterInterface> masterInt):
        number(n),
        master(masterInt),
        AbstractLogger(n)
        {
            commonInit();
        }

    Trip(const Trip& other) :
        state(other.state),
        number(other.number),
        master(other.master),
        slaves(other.slaves),
        masterLocationHistory(other.masterLocationHistory),
        AbstractLogger(other.number){
        }

    Trip& operator=(const Trip& other) {
        state = other.state;
        number = other.number;
        master = other.master;
        slaves = other.slaves;
        masterLocationHistory = other.masterLocationHistory;
        return *this;
    }

    string getNumber(){
        return number;
    }

    MasterInterface getMaster(){
        return *master;
    }

    void validateMasterId(string masterId){
        if (masterId != master->getNumber()){
            logger->error("The masterId {} does not match the existing one {}", masterId, master->getNumber());
        }
    }

    void validateSlaveId(string slaveId){
        for (auto slave: slaves){
            if (slave.getNumber() == slaveId){
                return;
            }
        }
        logger->error("The slave ID {} is not valid", slaveId);
    }

    void addSlave(string slaveId){
        SlaveInterface slave(slaveId, master);
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

    vector<Point> getFullMasterPath(){
        return masterLocationHistory;
    }

    vector<SlaveInterface>& getSlaves(){
        return slaves;
    }

    vector<Point> getSlaveToMasterPath(string slaveId){
        validateSlaveId(slaveId);
        for (auto slave: slaves){
            return slave.getCurrentPathToMaster();
        }
        logger->error("No slave id {} was found", slaveId);
    }

private:
    State state;
    string number;
    shared_ptr<MasterInterface> master;
    vector<SlaveInterface> slaves;
    vector<Point> masterLocationHistory;
    thread getMasterLocationThread;

    void commonInit(){
        state = State::INIT;
        logger->info("Initialized Trip {}", number);
    }

};

#endif