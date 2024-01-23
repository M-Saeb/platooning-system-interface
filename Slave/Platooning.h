
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#ifndef PLATOONING_H
#define PLATOONING_H
#define bool _Bool
typedef enum {
    COUPLED,
    DECOUPLED
} SlaveState;



// Forward declarations
typedef struct Server Server;
typedef struct MasterVehicle MasterVehicle;
typedef struct SlaveVehicle SlaveVehicle;

// Actual structure definitions
struct Server{
    double** pointsHistory;
    int pointsCount;
};

struct MasterVehicle {
    SlaveVehicle** slaves;
    Server* server;
    bool showStopSign;
};

struct SlaveVehicle {
    char* number;
    SlaveState state;
    double timeDelay;
    double minDistance;
    Server* server;
    MasterVehicle* master;
    bool testPingState;
};

// Forward declarations
typedef struct Server Server;
typedef struct MasterVehicle MasterVehicle;
typedef struct SlaveVehicle SlaveVehicle;
typedef struct SlaveNotReachableException SlaveNotReachableException;

// Master
void updateLocation(MasterVehicle* master);
void setShowStopSignal(MasterVehicle* master, bool newValue);
void accelerate(MasterVehicle* master, double speed);
void steer(MasterVehicle* master, double steeringAngle);
void getBreakPressure(MasterVehicle* master, double breakPressure);
void pingAllSlaves(MasterVehicle* master);
void decoupleSlave(MasterVehicle* master, SlaveVehicle* slave);

// Slave
// Platooning.h
void addSlaveVehicle(MasterVehicle* master, SlaveVehicle* slave);
void accelerateSlave(SlaveVehicle* slave, double speed);
void steerSlave(SlaveVehicle* slave, double degree);
void pressBreak(SlaveVehicle* slave, double pressure);
void sensorBreak(SlaveVehicle* slave);
void sendDecoupledSignal(SlaveVehicle* slave);
void autoDrive(SlaveVehicle* slave);
void throwSlaveNotReachableException(const char* message);
void catchSlaveNotReachableException(SlaveNotReachableException* exception);
void pingSlave(SlaveVehicle* slave);

#endif // PLATOONING_H