#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <omp.h>  // Include OpenMP header if using OpenMP
#include <unistd.h>

// Enumeration for slave states
typedef enum {
    COUPLED,
    DECOUPLED
} SlaveState;

// Struct representing a server
typedef struct Server{
    double** pointsHistory;
    int pointsCount;
} Server;

// Struct representing a master vehicle
typedef struct MasterVehicle{
    struct SlaveVehicle** slaves;
    struct Server* server;
    bool showStopSign;
} MasterVehicle;

// Struct representing a slave vehicle
typedef struct SlaveVehicle{
    char* number;
    SlaveState state;
    double timeDelay;
    double minDistance;
    struct Server* server;
    struct MasterVehicle* master;
    bool testPingState;
} SlaveVehicle;


// Function declarations for master
void addSlaveVehicle(MasterVehicle* master, SlaveVehicle* slave);
void updateLocation(MasterVehicle* master);
void setShowStopSignal(MasterVehicle* master, bool newValue);
void accelerate(MasterVehicle* master, double speed);
void steer(MasterVehicle* master, double steeringAngle);
void getBreakPressure(MasterVehicle* master, double breakPressure);
void pingAllSlaves(MasterVehicle* master);
void decoupleSlave(MasterVehicle* master, struct SlaveVehicle* slave);

// Function declarations for slaves
void accelerateSlave(SlaveVehicle* slave, double speed);
void steerSlave(SlaveVehicle* slave, double degree);
void pressBreak(SlaveVehicle* slave, double pressure);
void sensorBreak(SlaveVehicle* slave);
void sendDecoupledSignal(SlaveVehicle* slave);
void autoDrive(SlaveVehicle* slave);



void addNewLocation(Server* server, double location[2]) {
    // Add new location to the server
    server->pointsHistory = realloc(server->pointsHistory, (server->pointsCount + 1) * sizeof(double*));
    server->pointsHistory[server->pointsCount] = malloc(2 * sizeof(double));
    server->pointsHistory[server->pointsCount][0] = location[0];
    server->pointsHistory[server->pointsCount][1] = location[1];
    server->pointsCount++;

    printf("Updated current location of master to server: %.2f, %.2f\n", location[0], location[1]);
}

void freeServer(Server* server) {
    // Check if pointsHistory is not NULL before attempting to free it
    if (server->pointsHistory != NULL) {
        // Assuming pointsHistory is a 2D array of doubles, you need to free each row first
        for (int i = 0; i < server->pointsCount; ++i) {
            free(server->pointsHistory[i]);
        }

        // Finally, free the array of pointers
        free(server->pointsHistory);
    }

    // Optionally, you can reset other members of the Server structure to a default state
    server->pointsHistory = NULL;
    server->pointsCount = 0;
}
double getLongitude() {
    return rand() / (double)RAND_MAX;
}

double getLatitude() {
    return rand() / (double)RAND_MAX;
}

void addSlaveVehicle(MasterVehicle* master, SlaveVehicle* slave) {
    master->slaves = realloc(master->slaves, (sizeof(struct SlaveVehicle*) * (sizeof(master->slaves) / sizeof(master->slaves[0]) + 1)));
    master->slaves[sizeof(master->slaves) / sizeof(master->slaves[0]) - 1] = slave;
    printf("Added slave numbered %s to master\n", slave->number);
}


void updateLocation(MasterVehicle* master) {
    // Send the current location to the server
    double longitude = getLongitude();
    double latitude = getLatitude();
    double currentLocation[] = {longitude, latitude};
    addNewLocation(master->server, currentLocation);
}

void setShowStopSignal(MasterVehicle* master, bool newValue) {
    if (newValue) {
        printf("Show the stop sign for master !!\n");
    } else {
        printf("This is the current location of the Slave\n");
    }
    master->showStopSign = newValue;
}

void accelerate(MasterVehicle* master, double speed) {
    printf("The master accelerated by %.2f\n", speed);
    for (int i = 0; i < sizeof(master->slaves) / sizeof(master->slaves[0]); ++i) {
        accelerateSlave(master->slaves[i], speed);
    }
}

void steer(MasterVehicle* master, double steeringAngle) {
    printf("The master Steered by angle %.2f\n", steeringAngle);
    for (int i = 0; i < sizeof(master->slaves) / sizeof(master->slaves[0]); ++i) {
        steerSlave(master->slaves[i], steeringAngle);
    }
}

void getBreakPressure(MasterVehicle* master, double breakPressure) {
    printf("The master break pressure %.2f\n", breakPressure);
    for (int i = 0; i < sizeof(master->slaves) / sizeof(master->slaves[0]); ++i) {
        pressBreak(master->slaves[i], breakPressure);
    }
}

void pingAllSlaves(MasterVehicle* master) {
    int numSlaves = sizeof(master->slaves) / sizeof(master->slaves[0]);

    for (int i = 0; i < numSlaves; ++i) {
        master->slaves[i]->state = COUPLED;
    }

    setShowStopSignal(master, false);
}

void decoupleSlave(MasterVehicle* master,  SlaveVehicle* slave) {
    slave->state = DECOUPLED;
    setShowStopSignal(master, true);
}

void accelerateSlave(SlaveVehicle* slave, double speed) {
    printf("The slave with number %s Accelerated By %.2f\n", slave->number, speed);
}

void steerSlave(SlaveVehicle* slave, double degree) {
    printf("The slave with number %s Steered at degree of %.2f\n", slave->number, degree);
}

void pressBreak(SlaveVehicle* slave, double pressure) {
    printf("The slave with number %s Pressed brakes on the vehicle with pressure of %.2f\n", slave->number, pressure);
}

void sensorBreak(SlaveVehicle* slave) {
    printf("The slave with number %s Pressed sensor brakes on the vehicle\n", slave->number);
    sendDecoupledSignal(slave);
}

void sendDecoupledSignal(SlaveVehicle* slave) {
    printf("The slave with number %s decoupled\n", slave->number);
    slave->state = DECOUPLED;
    decoupleSlave(slave->master, slave);
}

void autoDrive(SlaveVehicle* slave) {
    slave->server->pointsHistory;
    printf("Auto drive is ON for slave %s\n", slave->number);
}


int main() {
    // Initialize server, master, and slaves
    Server server = {NULL, 0};
    MasterVehicle master = {NULL, &server, false};
    SlaveVehicle slave01 = {"A01", false, 0.5, 5.0, &server, &master, true};
    SlaveVehicle slave02 = {"B02", false, 1.0, 5.0, &server, &master, true};
    SlaveVehicle slave03 = {"C03", false, 1.5, 5.0, &server, &master, true};

    // Add slaves to master
    addSlaveVehicle(&master, &slave01);
    addSlaveVehicle(&master, &slave02);
    addSlaveVehicle(&master, &slave03);

    // Start a thread for sending signals from the slave to the server
    #pragma omp parallel num_threads(1)
    {
        #pragma omp single
        {
            // Send signals from the slave to the server
            while (1) {
                #pragma omp parallel sections
                {
                    #pragma omp section
                    {
                        // Send signal to server
                        pingAllSlaves(&master);
                    }
                    #pragma omp section
                    {
                        // Print current timestamp
                        #pragma omp critical
                        {
                            time_t t = time(NULL);
                            struct tm* tm_info = localtime(&t);
                            char time_str[9];
                            strftime(time_str, sizeof(time_str), "%H:%M:%S", tm_info);
                            printf("Current timestamp: %s\n", time_str);
                        }
                    }
                }

                // Sleep for 1 second
                #pragma omp critical
                {
                    sleep(1);
                }
            }
        }
    }

    // Simulation
    printf("=== Second 1 ===\n");
    updateLocation(&master);
    pingAllSlaves(&master);
    accelerate(&master, 20.0);

    printf("=== Second 2 ===\n");
    updateLocation(&master);
    pingAllSlaves(&master);
    steer(&master, 30.0);
    // Add your simulation steps here

    // Free allocated memory
    freeServer(&server);

    return 0;
}
