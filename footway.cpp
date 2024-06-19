/*footway.cpp*/

//
// A footway in the Open Street Map.
// 
// Bella Fishman
// Northwestern University
// CS 211

#include "footway.h"

using namespace std;

//
// constructor
//
Footway::Footway(long long id)
  : ID(id)
{
  //
  // the proper technique is to use member initialization list above,
  // in the same order as the data members are declared:
  //
  //this->ID = id;
  //this->Name = name;
  //this->StreetAddress = streetAddr;

  // vector is default initialized by its constructor
}

//
// adds the given nodeid to the end of the map.
//
void Footway::add(long long nodeid)
{
  // only 1 copy made using emplace as opposed to 2 copes from insert and make pair
  this->NodeIDs.push_back(nodeid);
}
