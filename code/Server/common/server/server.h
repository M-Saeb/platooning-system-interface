#ifndef SERVER_H
#define SERVER_H

#include <iostream> 
#include <vector>
#include "../trip/trip.h"

class Server{
public:
    Server(){}

    // Declare the destructor
    ~Server();

    void addTrip(Trip trip){
        trips.push_back(trip);
    }

private:
    std::vector<Trip> trips;
};

#endif