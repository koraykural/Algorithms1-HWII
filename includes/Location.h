/**
 * This file contains Location class.
 * 
 * It has longtitude and latitudes attributes.
 * 
 * It can calculate distance between two locations.
 */

#ifndef LOCATION_H
#define LOCATION_H

class Location
{
private:
    double lng;
    double lat;

public:
    Location(double, double);
    static double calculate_distance(Location, Location);
    double calculate_distance(Location) const;
};

#endif
