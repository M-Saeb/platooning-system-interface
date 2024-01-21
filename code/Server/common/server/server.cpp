#include <iostream> 
#include "server.h"
#include "../trip/trip.h"
#include "../point/point.h"
#include "../masterInterface/masterInterface.h"
#include "../slaveInterface/slaveInterface.h"

using namespace std;

Server::~Server() {
    // Destructor implementation
    // (If there are any resources to be released, this is the place to do it)
}

string Server::createTrip(string masterId){
    string tripNumber = "TRIP_" + generateNumber();
    shared_ptr<MasterInterface> master = make_shared<MasterInterface>(masterId);
    Trip newTrip(tripNumber, master);
    trips[tripNumber] = make_unique<Trip>(newTrip);
    logger->info("Linked master {} with trip {}", masterId, tripNumber);
    return tripNumber;
}

void Server::linkSlaveToTrip(string tripNumber, string slaveId){
    auto trip = trips[tripNumber].get();
    trip->addSlave(slaveId);
}

void Server::startTrip(string tripNumber){
    auto trip = trips[tripNumber].get();
    trip->startTrip();
}

void Server::endTrip(string tripNumber){
    auto trip = trips[tripNumber].get();
    trip->endTrip();
}

void Server::sendStopSignalToMaster(string tripNumber){
    auto trip = trips[tripNumber].get();
    logger->info("Received stop signal for trip {}", tripNumber);
    // trip->sendStopSignalToMaster();
}

void Server::receiveEndTripSignal(string tripNumber){
    logger->info("Received end trip signal for trip {}", tripNumber);
    auto trip = trips[tripNumber].get();
    trip->endTrip();
    logger->info("Trip {} ended", tripNumber);

}

void Server::updateMasterLocation(
    string tripNumber, string masterId, Point p
){
    auto trip = trips[tripNumber].get();
    trip->validateMasterId(masterId);
    auto& master = trip->getMaster();
    master.setLocation(p);
}

vector<Point> Server::getSlaveToMasterLocation(
    string tripNumber, string masterId, string slaveId
){
    auto trip = trips[tripNumber].get();
    trip->validateMasterId(masterId);
    return trip->getSlaveToMasterPath(slaveId);
}

void Server::turnOnEmergencySignalForTrip(string tripNumber){
    auto trip = trips[tripNumber].get();
    trip->turnOnEmergencySignal();
}

void Server::turnOffEmergencySignalForTrip(string tripNumber){
    auto trip = trips[tripNumber].get();
    trip->turnOffEmergencySignal();
}

bool Server::getEmergencySignalForTrip(string tripNumber){
    auto trip = trips[tripNumber].get();
    return trip->getEmergencySignal();
}
