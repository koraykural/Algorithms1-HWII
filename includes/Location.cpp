/**
 * This file contains implementation of the Location class
 */

#include "Location.h"
#include <cmath>

using namespace std;

Location::Location(double longtitude, double latitude)
{
    lng = longtitude;
    lat = latitude;
}

/**
 * Returns the euclidian distance between two locations.
 */
double Location::calculate_distance(Location val) const
{
    return sqrt(pow(abs(lng - val.lng), 2) + pow(abs(lat - val.lat), 2));
}

/**
 * Returns the euclidian distance between two locations.
 * 
 * Static method.
 */
double Location::calculate_distance(Location first, Location second)
{
    return sqrt(pow(abs(first.lng - second.lng), 2) + pow(abs(first.lat - second.lat), 2));
}
