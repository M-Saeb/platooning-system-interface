#ifndef TRIP_H
#define TRIP_H

#include <iostream> 
#include <vector>
#include <thread>
#include <random>
#include <windows.h>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include "../vehicles/masterVechicle.h"
#include "../vehicles/slaveVehicle.h"
#include "../point.h"
#include "../abstract/abstractLogger.h"

enum class State{
    INIT,
    IN_PROGRESS,
    DONE
};

class Trip: AbstractLogger{
public:
    // Declare the destructor
    ~Trip();

    Trip(std::string number):
        number(number),
        master(NULL),
        AbstractLogger(number)
    {
        commonInit();
    }

    Trip(std::string number, MasterVehicle master):
        number(number),
        master(master),
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

    // Copy assignment operator
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

    void addSlave(SlaveVehicle &slave){
        logger->info("added slave numbered {}", slave.number);
        slaves.push_back(slave);
    }

    void startTrip(){
        state = State::IN_PROGRESS;
        std::thread locationThread(&Trip::theMasterLocationThread, this);
        getMasterLocationThread = std::move(locationThread);
        logger->info("Trip started !");
    }

    void endTrip(){
        state = State::DONE;
        getMasterLocationThread.join();
        logger->info("Trip ended.");
    }

    Point updateMasterLocation(){
        Point point(master.getMasterLocation());
        logger->info("got new location {}, {}", point.longitude, point.latitude);
        masterLocationHistory.push_back(point);
        return point;
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
    std::thread getMasterLocationThread;

    void commonInit(){
        state = State::INIT;
        logger->info("Initialized Trip {}", number);
    }

    static void theMasterLocationThread(Trip* trip){
        trip->logger->info("started runMasterLocationThread", trip->number);

        while(trip->state == State::IN_PROGRESS){
            trip->updateMasterLocation();
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
        trip->logger->info("ended runMasterLocationThread", trip->number);
    }

};

#endif