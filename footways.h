/*footways.h*/

//
// A collection of footways in the Open Street Map
//
// Bella Fishman
// Northwestern University
// CS 211
//
//

#pragma once

#include <vector>
#include <iostream>

#include "footway.h"
#include "tinyxml2.h"

#include "node.h"
#include "nodes.h"
#include "building.h"


using namespace std;
using namespace tinyxml2;

//
// Keeps track of all the footways in the map.
//
class Footways
{
public:
    vector<Footway> MapFootways;
    
    // 
    // readMapBuildings
    //
    // Given an XML document, reads through the document and 
    // stores all the buildings into the given vector
    //
    void readMapFootways(XMLDocument& xmldoc);


    //
    // accessors / getters
    //
    // getNumMapFootways
    // returns the # of footways in the MapFootways
    int getNumMapFootways() const;
    
    //
    // print
    // prints the intersecting footways with a building
    // in the correct format
    //
    void print(vector<long long>& Footway_List) const;

    //
    // given a Building, finds any intersecting footways
    //
    void printIntersect(Building B) const;

    // 
    // Binary Searches through given inputs to find a matching input
    // vector must be sorted!
    //
    bool binarySearch(const long long& F_id, const Building& B) const;


    //
    // loops through Footway ID vector and performs binary search on building NodeIDs
    // returns true if it intersects with building and false otherwise
    //
    // binary_Buildings
    //
    bool binary_Buildings(const Footway& F, const Building& B) const;
    //
    // Loops through All footways to recurse through their individual nodes
    //
    // findFootways(const long long& buildid, vector<long long>& Footway_List);
};
