#include <iostream> 
#include <spdlog/spdlog.h>
#include <windows.h>
#include <thread>

#include "common/vehicles/masterVechicle.h"
#include "common/vehicles/slaveVehicle.h"
#include "common/server/server.h"

using namespace std;


int main() { 
    Server server;
    MasterVehicle master("MSTR_001");
    SlaveVehicle slave1("SLVE_001"), slave2("SLVE_002");
    Trip trip("TRIP_001", master);
    trip.addSlave(slave1);
    trip.addSlave(slave2);
    trip.startTrip();
    std::this_thread::sleep_for(std::chrono::seconds(5));
    trip.endTrip();


    return 0; 
}
