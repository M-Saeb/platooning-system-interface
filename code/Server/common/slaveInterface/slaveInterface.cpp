#include <iostream> 
#include <mutex> 
#include <windows.h>

#include "slaveInterface.h"

using namespace std;

SlaveInterface::~SlaveInterface() {
    // Destructor implementation
    // (If there are any resources to be released, this is the place to do it)
}

void SlaveInterface::slaveToMasterThread() {
    logger->info("Started slaveToMasterThread thread");

    Point currentMasterLocation = getMasterLocation();
    Point currentSlaveLocation = getSlaveLocation();

    while (isThreadRunning()) {
        if (getMasterLocation() != currentMasterLocation) {
            
            logger->info("Detected new master location");
            currentMasterLocation = getMasterLocation();
            addPointToPath(currentMasterLocation);
            logger->info("size is {}", getCurrentPathToMaster().size());
        }
        if (getSlaveLocation() != currentSlaveLocation) {
            logger->info("Detected slave location update");
            currentSlaveLocation = getSlaveLocation();
            popPointFromPath();
        }
    }

    logger->info("Ended slaveToMasterThread thread");
}


