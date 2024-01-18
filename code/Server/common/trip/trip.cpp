#include <iostream> 
#include "trip.h"
#include "../util/utils.h"

using namespace std;

Trip::~Trip() {
    // Destructor implementation
    // (If there are any resources to be released, this is the place to do it)
}

Trip Trip::createTrip(string masterId){
    string tripNumber = "TRIP_" + generateNumber();
    MasterInterface master(masterId);
    Trip newTrip(tripNumber, master);
    cout << newTrip.master.getNumber() << " - " << newTrip.number;
    return newTrip;
}
