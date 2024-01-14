#include <iostream> 
#include <spdlog/spdlog.h>
#include <pthread.h>
#include "common/vehicles/masterVechicle.h"
#include "common/vehicles/slaveVehicle.h"
#include "common/server/server.h"

using namespace std;

/* 
void *test_process(void *args){
    int i = 0;
    for (int j=0; j < 1000; j++){
        cout << "T" << i << "\n";
        i ++;
    }
}

void *run_process(void *args){
    int i = 0;
    for (int j=0; j < 1000; j++){
        cout << "R" << i << "\n";
        i ++;
    }
}
*/

int main() { 
    // pthread_t thread_1, thread_2;
    // pthread_create(&thread_1, NULL, test_process, NULL);
    // pthread_create(&thread_2, NULL, run_process, NULL);
    // pthread_join(thread_1, NULL);
    // pthread_join(thread_2, NULL);

    Server server();
    MasterVehicle master("M01");
    SlaveVehicle slave1("SL001"), slave2("SL002");
    Trip trip("TRIP_001", master);


    spdlog::info("New welcome to spdlog! ");

    return 0; 
}
