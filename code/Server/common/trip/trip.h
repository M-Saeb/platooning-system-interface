#ifndef TRIP_H
#define TRIP_H

#include <iostream> 
#include <vector>
#include <spdlog/spdlog.h>
#include "../vehicles/masterVechicle.h"
#include "../vehicles/slaveVehicle.h"
#include "../point.h"

enum class State{
    INIT,
    IN_PROGRESS,
    DONE
};

class Trip{
public:
    // Declare the destructor
    ~Trip();

    Trip(std::string number):
        number(number),
        master(NULL)
    {
        commonInit();
    }

    Trip(std::string number, MasterVehicle master):
        number(number),
        master(master)
    {
        commonInit();
    }

    void addSlave(SlaveVehicle &slave){
        slaves.push_back(slave);
    }

    void startTrip(){
        state = State::IN_PROGRESS;
    }

    void endTrip(){
        state = State::DONE;
    }

    void updateMasterLocation(){
        Point point(master.getMasterLocation());
        masterLocationHistory.push_back(point);
    }

    std::vector<Point> getMasterPath(){
        return masterLocationHistory;
    }

private:
    State state;
    std::string number;
    MasterVehicle master;
    std::vector<SlaveVehicle> slaves;
    std::vector<Point> masterLocationHistory;
    void commonInit(){
        state = State::INIT;
        spdlog::info("Initialized trip numbered {}", number);
    }

};

#endif