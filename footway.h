/*footway.h*/

// 
// A footway in the Open Street Map
//
//
// Bella Fishman
// Northwestern University
// CS 211

#pragma once

#include <string>
#include <iostream>
#include <vector>

#include "node.h"
#include "nodes.h"

using namespace std;


//
// Building
//
// Defines a campus building with a name (e.g. "Mudd"), a street
// address (e.g. "2233 Tech Dr"), and the IDs of the nodes that
// define the position / outline of the building.
// 
// NOTE: the Name could be empty "", the HouseNumber could be
// empty, and the Street could be empty. Imperfect data.
//
class Footway
{
public:
  long long ID;
  vector<long long> NodeIDs;

  //
  // constructor
  //
  Footway(long long id);

  //
  // adds the given nodeid to the end of the vector.
  //
  void add(long long nodeid);

};
