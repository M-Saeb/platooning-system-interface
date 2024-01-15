#ifndef SLAVE_VEHICLE_H
#define SLAVE_VEHICLE_H

#include <iostream> 
#include <spdlog/spdlog.h>
#include "vehicle.h"

class SlaveVehicle: public Vehicle{
public:
    SlaveVehicle(std::string number): Vehicle(number){
        commonInit();
    }
    ~SlaveVehicle() override;

private:
    void commonInit(){
        logger->info("Initialized slave vehicle numbered {}", number);
    }

};

#endif
