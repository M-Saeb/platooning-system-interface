#ifndef VEHICLE_H
#define VEHICLE_H

#include <iostream> 
#include <string>

class Vehicle {
public:
    std::string number;

    // Constructor
    Vehicle(std::string number): number(number){}

    // Virtual destructor (important for polymorphism)
    virtual ~Vehicle();

    // Pure virtual function for getting the type of vehicle

    std::string getNumber() const{
        return number;
    };
};

#endif // VEHICLE_H
