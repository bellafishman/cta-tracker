/*busstops.h*/

//
// A collection of busstops from the bus-stops.txt
//
// Bella Fishman
// Northwestern University
// CS 211
//

#pragma once

#include <vector>
#include <iostream>
#include <queue>
#include "busstop.h"
#include "tinyxml2.h"

#include "building.h"
#include "dist.h"

#include "curl_util.h"


using namespace std;
using namespace tinyxml2;

// ComparePairs
// to build min priority queue
struct ComparePairs {
    bool operator()(const std::pair<double, BusStop>& lhs, const std::pair<double, BusStop>& rhs) const {
        return lhs.first > rhs.first;  // Comparing based on the first element (distance)
    };
};


class BusStops
{
private:
    vector<BusStop> MapBusStops;

public:
  //
  // readBusStops
  //
  // Given an txt document, reads through the document and 
  // stores all the busstops into the given vector. Each busstop
  // contains a stop ID, bus route, stop name, direction, and location of stop and
  // location in lat and long
  //
  void readBusStops(string filename);

  //
  // accessors / getters
  //
  // returns number of bus stops in map
  int getNumBusStops() const;

  // print
  // prints all of the BusStops in a given file in the correct format
  void print() const;

  // 
  // findNearest
  // find the nearest bus stop - Northbound AND Southbound to a given building
  void findNearest(Building& building, pair<double, double> b_location, CURL* curl);
  
  //
  // read_and_print_API
  // calls curl to read an API and print extracted information
  // handles exceptions in handling
  //
  int printBusPredictions(BusStop& bus, string& key, CURL* curl);

};
