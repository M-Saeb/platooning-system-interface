#include <iostream> 
#include <spdlog/spdlog.h>
#include <windows.h>

#include "common/server/server.h"

using namespace std;

int main() { 
    string masterId = "MSTR_001";
    string slaveId1 = "SLVE_001";
    string slaveId2 = "SLVE_002";
    Server server;
    string tripNumber = server.createTrip(masterId);
    return 0;
    server.linkSlaveToTrip(tripNumber, slaveId1);
    server.linkSlaveToTrip(tripNumber, slaveId2);
    server.startTrip(tripNumber);
    this_thread::sleep_for(chrono::seconds(2));
    server.endTrip(tripNumber);
    // Server server_1();
    // Server server_2(); 
    // vector<Server> lines;
    // lines.push_back(server_1);
    // lines.push_back(server_2);

    return 0; 
}
