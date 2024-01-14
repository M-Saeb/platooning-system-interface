#ifndef SLAVE_VEHICLE_H
#define SLAVE_VEHICLE_H

#include <iostream> 
#include "vehicle.h"

class SlaveVehicle: public Vehicle{
public:
    SlaveVehicle(std::string number): Vehicle(number){}
    ~SlaveVehicle() override;

};

#endif
