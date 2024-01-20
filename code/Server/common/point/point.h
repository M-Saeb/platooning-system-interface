#ifndef POINT_H
#define POINT_H

#include <iostream>
#include <string>

using namespace std;

class Point {
public:
    Point();
    // Point() : longitude(0.0), latitude(0.0) {}

    Point(float longitude, float latitude) : longitude(longitude), latitude(latitude) {}

    Point(double longitude, double latitude) : longitude(static_cast<float>(longitude)), latitude(static_cast<float>(latitude)) {}

    Point(const Point& p) : longitude(p.longitude), latitude(p.latitude) {}

    // Remove the destructor

    bool operator==(const Point& other) const {
        return (longitude == other.longitude && latitude == other.latitude);
    }

    bool operator!=(const Point& other) const {
        return (longitude != other.longitude || latitude != other.latitude);
    }

    string toString() const {
        string result = to_string(longitude) + "," + to_string(latitude);
        return result;
    }

    float longitude;
    float latitude;
};

#endif
