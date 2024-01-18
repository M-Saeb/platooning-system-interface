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

class MasterInterface;
class SlaveInterface;

class Server: public AbstractLogger{
public:
    Server(): AbstractLogger("_SERVER_"){}

    ~Server();

    string createTrip(string masterId);
    void linkSlaveToTrip(string tripNumber, string slaveId);
    void startTrip(string tripNumber);
    void endTrip(string tripNumber);
    void sendStopSignalToMaster(string tripNumber);    
    void receiveEndTripSignal(string tripNumber);

private:
    unordered_map<string, Trip> trips;

};

#endif