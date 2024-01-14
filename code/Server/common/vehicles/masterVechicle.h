#ifndef MASTER_VEHICLE_H
#define MASTER_VEHICLE_H

#include <iostream> 
#include <random>
#include "vehicle.h"
#include "../point.h"

class MasterVehicle: public Vehicle{
public:
    MasterVehicle(std::string number): Vehicle(number){}
    ~MasterVehicle() override;

    Point getMasterLocation(){
        // Create a random number generator engine
        std::random_device rd;
        std::mt19937 gen(rd());
        
        // Define a distribution for floating-point numbers between 1 and 99
        std::uniform_real_distribution<float> dist(1.0f, 99.0f);

        // Generate a random float number
        float longitude = dist(gen);
        float latitude = dist(gen);
        
        Point point(longitude, latitude);
        return point;
    }
};

#endif
