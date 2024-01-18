#include <iostream> 
#include "server.h"
#include "../trip/trip.h"
#include "../masterInterface/masterInterface.h"
#include "../slaveInterface/slaveInterface.h"

using namespace std;

Server::~Server() {
    // Destructor implementation
    // (If there are any resources to be released, this is the place to do it)
}

string Server::createTrip(string masterId){
    string tripNumber = "TRIP_" + generateNumber();
    MasterInterface master(masterId);
    Trip newTrip(tripNumber, master);
    trips[tripNumber] = newTrip;
    logger->info("Added trip {} with master {}", tripNumber, masterId);
    return tripNumber;
}

void Server::linkSlaveToTrip(string tripNumber, string slaveId){
    Trip &trip = trips[tripNumber];
    trip.addSlave(slaveId);
    logger->info("Linked slave {} to trip number {}", slaveId, tripNumber);
}

void Server::startTrip(string tripNumber){
    Trip &trip = trips[tripNumber];
    trip.startTrip();
}

void Server::endTrip(string tripNumber){
    Trip &trip = trips[tripNumber];
    trip.endTrip();
}

void Server::sendStopSignalToMaster(string tripNumber){
    Trip& trip = trips[tripNumber];
    logger->info("Received stop signal for trip {}", tripNumber);
    // trip.sendStopSignalToMaster();
}

void Server::receiveEndTripSignal(string tripNumber){
    logger->info("Received end trip signal for trip {}", tripNumber);
    Trip& trip = trips[tripNumber];
    trip.endTrip();
    logger->info("Trip {} ended", tripNumber);

}