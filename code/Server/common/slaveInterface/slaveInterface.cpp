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
    Point currentMasterLocation = getMasterLocation();
    Point currentSlaveLocation = getSlaveLocation();
    logger->info("Started slaveToMasterThread thread");
    while (isThreadRunning()) {
        if (getMasterLocation() != currentMasterLocation) {
            
            logger->info("--> Detected new master location <--");
            currentMasterLocation = getMasterLocation();
            addPointToPath(currentMasterLocation);
        }
        if (getSlaveLocation() != currentSlaveLocation) {
            logger->info("--> Detected new slave location <--");
            currentSlaveLocation = getSlaveLocation();
            popPointFromPath();
        }
    }

    logger->info("Ended slaveToMasterThread thread");
}


