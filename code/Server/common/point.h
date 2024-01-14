#ifndef POINT_H
#define POINT_H

#include <iostream> 

class Point{
public:
    Point(float longitude, float latitude):
        longitude(longitude),
        latitude(latitude)
    {}

    // Declare the destructor
    ~Point();

    float longitude;
    float latitude;
};

#endif