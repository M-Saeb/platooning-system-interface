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
    server.linkSlaveToTrip(tripNumber, slaveId1);
    server.linkSlaveToTrip(tripNumber, slaveId2);
    server.startTrip(tripNumber);
    server.updateMasterLocation(
        tripNumber, masterId, Point(11.11, 22.22)
    );
    this_thread::sleep_for(chrono::seconds(1));

    server.updateMasterLocation(
        tripNumber, masterId, Point(33.33, 44.44)
    );
    vector<Point> path = server.getSlaveToMasterLocation(
        tripNumber, masterId, slaveId1
    );
    cout << "\n => " << path.size() << "\n";
    for (auto p: path){
        cout << "\n ===> " << p.toString() << "\n";
    }
    this_thread::sleep_for(chrono::seconds(1));
    server.endTrip(tripNumber);
    return 0; 
}
