/*building.cpp*/

//
// A building in the Open Street Map.
// 
// Prof. Joe Hummel
// Northwestern University
// CS 211
// Bella Fishman


// 
#include <utility>

#include "building.h"

using namespace std;

//
// constructor
//
Building::Building(long long id, string name, string streetAddr)
  : ID(id), Name(name), StreetAddress(streetAddr)
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
// adds the given nodeid to the end of the vector.
//
void Building::add(long long nodeid)
{
  this->NodeIDs.push_back(nodeid);
}

//
// print
//
// prints all of the nodes contained in the given Building
void Building::print(const Nodes& nodes) const
{
  //vector<long long> Footway_List;

  cout << this->Name << endl;
  cout << "Address: " << this->StreetAddress << endl;
  cout << "Building ID: " << this->ID << endl;
  //cout << "Nodes: " << this->NodeIDs.size() << endl;

  pair<double, double> location = this->getLocation(nodes);

  cout << "# perimeter nodes: " << this->NodeIDs.size() << endl;
  cout << "Location: (" << location.first << ", " << location.second << ")" << endl;
  /*
  for (long long nodeid : this->NodeIDs)
  {
    cout << " " << nodeid << ": ";

    double lat = 0.0;
    double lon = 0.0;
    bool entrance = false;

    bool found = nodes.find(nodeid, lat, lon, entrance);

    if (found) {
      cout << "(" << lat << ", " << lon << ")";

      if (entrance)
        cout << ", is entrance";

      cout << endl;
    }
    else {
      cout << "**NOT FOUND**" << endl;
    }
    

    // loop through footways
    // need to append new list to old list
    //vector<long long> new_list = footways.findFootways(nodeid, Footway_List);
    //Footway_List.insert(Footway_List.begin(), new_list.begin(), new_list.end()); 

  } // for
  */

  // after printing all of the nodes, print footway information
  //footways.print(Footway_List);
}

//
// gets the center (lat, lon) of the building based
// on the nodes that form the perimeter
//
pair<double, double> Building::getLocation(const Nodes& nodes) const{
    // building's location is the average latitutde and longitude of the nodes that
    // form the perimeter
    double sumLat = 0.0;
    int nLat = this->NodeIDs.size();
    double sumLon = 0.0;
    int nLon = nLat;

    for (long long nodeid : this->NodeIDs){
      double lat = 0.0;
      double lon = 0.0;
      bool entrance = false;
      bool found = nodes.find(nodeid, lat, lon, entrance);

      if (found) {
        sumLat += lat;
        sumLon += lon;
      }
    }

    double avgLat = (double)(sumLat / nLat);
    double avgLon = (double)(sumLon / nLon);

    return make_pair(avgLat, avgLon);
}
