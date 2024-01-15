#ifndef SERVER_H
#define SERVER_H

#include <iostream> 
#include <vector>
#include "../trip/trip.h"
#include "../abstract/abstractLogger.h"

class Server: public AbstractLogger{
public:
    Server(): AbstractLogger("Server"){}

    // Declare the destructor
    ~Server();

    void addTrip(Trip trip){
        trips.push_back(trip);
    }

private:
    std::vector<Trip> trips;
};

#endif