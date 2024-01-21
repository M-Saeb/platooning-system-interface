#ifndef SERVER_H
#define SERVER_H

#include <iostream> 
#include <random>
#include <iomanip>
#include <sstream>
#include <vector>
#include <unordered_map>

#include "../trip/trip.h"
#include "../abstract/abstractLogger.h"

using namespace std;

class Point;
class MasterInterface;
class SlaveInterface;

class Server: public AbstractLogger{
public:
    Server(): AbstractLogger("_SERVER_"){
        commmonInit();
    }

    ~Server();

    string createTrip(string masterId);
    void linkSlaveToTrip(string tripNumber, string slaveId);
    void startTrip(string tripNumber);
    void endTrip(string tripNumber);
    void updateMasterLocation(string tripNumber, string masterId, Point p);
    void updateSlaveLocation(string tripNumber, string slaveId, Point p);
    vector<Point> getSlaveToMasterLocation(string tripNumber, string slaveId);
    void turnOnEmergencySignalForTrip(string tripNumber);
    void turnOffEmergencySignalForTrip(string tripNumber);
    bool getEmergencySignalForTrip(string tripNumber);

private:
    unordered_map<string, unique_ptr<Trip>> trips;

    void commmonInit(){
        logger->info("Initialized Server Interface");
    }


};

#endif