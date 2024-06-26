/*busstop.h*/

//
// Bella Fishman
// Northwestern University
// CS 211
//
// A busstop imported from bus-stops.txt
// Contains stop id, bus route, stop name, direction, stop location, and position
// of a single bus
// 

#pragma once

#include <string>
#include <iostream>
#include <vector>

using namespace std;

class BusStop
{
public:
    long long StopID;
    int BusRoute;
    string StopName;
    string Direction;
    string StopLocation;
    pair<double, double> Position;

    //
    // constructor
    //
    BusStop(long long stopID, int busroute, string stopname, string direction, string stoplocation, pair<double, double> position);

    //
    // print
    // prints busstop information
    //
    void print() const;
};
