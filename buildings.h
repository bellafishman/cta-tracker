/*buildings.h*/

//
// A collection of buildings in the Open Street Map
//
// Bella Fishman
// Northwestern University
// CS 211
//
// Original Author: Prof. Joe Hummel
//

#pragma once

#include <vector>
#include <iostream>
#include "building.h"
#include "tinyxml2.h"

#include "busstop.h"
#include "busstops.h"
#include "footway.h"
#include "footways.h"
#include "node.h"
#include "nodes.h"

#include "curl_util.h"



using namespace std;
using namespace tinyxml2;

//
// Keeps track of all the buildings in the map.
//
class Buildings
{
public:
    vector<Building> MapBuildings;

    // 
    // readMapBuildings
    //
    // Given an XML document, reads through the document and 
    // stores all the buildings into the given vector
    //
    void readMapBuildings(XMLDocument& xmldoc);

    //
    // accessors / getters
    //
    int getNumMapBuildings() const;

    // print
    // prints all of the Buildings in a given file in the correct format
    void print() const;

    //
    // findAndPrint
    //
    // finds and prints all of the buildings with a certain name or part of a name
    void findAndPrint(string& name, const Nodes& nodes, Footways& footways, BusStops& busstops, CURL* curl) const;
};
