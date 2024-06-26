/*busstop.cpp*/

//
// A busstop in the busstop.txt file
// 
// Bella Fishman
// Northwestern University
// CS 211
// 

#include "busstop.h"

using namespace std;

BusStop::BusStop(long long stopID, int busroute, string stopname, string direction, string stoplocation, pair<double, double> position)
  : StopID(stopID), BusRoute(busroute), StopName(stopname), Direction(direction), StopLocation(stoplocation), Position(position)
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
// print
// prints busstop information
//
void BusStop::print() const{
  cout << this->StopID << ": bus " << this->BusRoute << ", " << this->StopName << ", " <<
      this->Direction << ", " << this->StopLocation << ", location (" << this->Position.first << 
      ", " << this->Position.second << ")" << endl;
}
