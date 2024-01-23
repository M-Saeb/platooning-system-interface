#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef enum {
    COUPLED,
    DECOUPLED
} SlaveState;

typedef struct{

    char* number;
    SlaveState state;
    double timeDelay;
    double minDistance;
    struct Server* server;
    struct MasterVehicle* master;
    bool testPingState;

}SlaveVehicle;

typedef struct {
    const char* message;
} SlaveNotReachableException;

typedef struct{

    struct SlaveVehicle** slaves;
    struct Server* server;
    bool showStopSign;

}MasterVehicle;

typedef struct {
    double** pointsHistory;
    int pointsCount;
}Server;

// Master

void addSlaveVehicle(MasterVehicle* master, SlaveVehicle* slave);

void updateLocation(MasterVehicle* master);

void setShowStopSignal(MasterVehicle* master, bool newValue);

void accelerate(MasterVehicle* master, double speed);

void steer(MasterVehicle* master, double steeringAngle);

void getBreakPressure(MasterVehicle* master, double breakPressure);

void pingAllSlaves(MasterVehicle* master);

void decoupleSlave(MasterVehicle* master, struct SlaveVehicle* slave);

// Slave

void accelerateSlave(SlaveVehicle* slave, double speed);

void steerSlave(SlaveVehicle* slave, double degree);

void pressBreak(SlaveVehicle* slave, double pressure);

void sensorBreak(SlaveVehicle* slave);

void sendDecoupledSignal(SlaveVehicle* slave);

void autoDrive(SlaveVehicle* slave);

void throwSlaveNotReachableException(const char* message);

void catchSlaveNotReachableException(SlaveNotReachableException* exception);

void pingSlave(SlaveVehicle* slave);
