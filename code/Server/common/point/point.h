#ifndef POINT_H
#define POINT_H

#include <iostream>
#include <string>

using namespace std;

class Point{
public:
    Point():
        longitude(0.0),
        latitude(0.0)
    {}

    Point(float longitude, float latitude):
        longitude(longitude),
        latitude(latitude)
    {}

    // Declare the destructor
    ~Point();

   bool operator==(const Point& other) const {
        return (longitude == other.longitude &&
                latitude == other.latitude);
    }

   bool operator!=(const Point& other) const {
        return (longitude != other.longitude ||
                latitude != other.latitude);
    }

    string toString(){
        string result = to_string(longitude) + "," + to_string(latitude);

    }

    float longitude;
    float latitude;
};

#endif