/*buildings.cpp*/

//
// Bella Fishman
//

//
// Implements methods from buildings.h including 
// readMapBuildings and getNumMapBuildings
//

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cassert>

#include "buildings.h"

#include "tinyxml2.h"
#include "osm.h"

using namespace std;
using namespace tinyxml2;



//
// readMapBuildings()
//
// Given an XML document, reads through the document and 
// stores all the buildings into the given vector. Each building
// is a point on the map, with a unique id along with 
// street address and name. 
//
void Buildings::readMapBuildings(XMLDocument& xmldoc){
    // get first child
    XMLElement* osm = xmldoc.FirstChildElement("osm");
    assert(osm != nullptr);
    
    // begins traversal at first "way" - indicates buildings
    XMLElement* way = osm->FirstChildElement("way");
    while (way != nullptr){
        // if contains (key, val) pair (building, university), 
        // then add building to vector
        if (osmContainsKeyValue(way, "building", "university")){
            // grab way ID
            const XMLAttribute* attrID = way->FindAttribute("id");
            assert(attrID != nullptr);
            long long id = attrID->Int64Value();
            // grab building name and street address
            string name = osmGetKeyValue(way, "name");
            string streetAddr = osmGetKeyValue(way, "addr:housenumber")
                + " "
                + osmGetKeyValue(way, "addr:street");
            
            // create Building object
            Building B(id, name, streetAddr);
            
            // need to add vector of NodeIDs by looping through "nd"s
            XMLElement* nd = way->FirstChildElement("nd");
            while (nd != nullptr)
            {
                const XMLAttribute* ndref = nd->FindAttribute("ref");
                assert(ndref != nullptr);
                long long node_id = ndref->Int64Value();
                B.add(node_id);

                // advance to next node ref
                nd = nd->NextSiblingElement("nd");
            }

            // fully initialized and add to Buildings vector
            // use push_back to copy the vector B
            this->MapBuildings.push_back(B);
        }
        //
        // move on to next building in XML doc
        //
        way = way->NextSiblingElement("way");
    }
}

//
// accessors / getters
//
int Buildings::getNumMapBuildings() const {
  return (int) this->MapBuildings.size();
}

//
// print
//
// prints all of the Buildings in the given file in the correct format
void Buildings::print() const{
    for (const Building& B : MapBuildings) {
        cout << B.ID << ": " << B.Name << ", " << B.StreetAddress << endl;
    }
}

//
// findAndPrint
//
// finds and prints all of the buildings with a certain name or part of a name
void Buildings::findAndPrint(string& name, const Nodes& nodes, Footways& footways, BusStops& busstops, CURL* curl) const{
    // 
    // find every building that contains this name:
    //
    bool found = false;

    for (Building B : MapBuildings)
    {
        if (B.Name.find(name) != string::npos) {  // contains name:
            found = true;
            B.print(nodes); // print all of the nodes
            pair<double, double> B_location = B.getLocation(nodes);
            busstops.findNearest(B, B_location, curl);
            // checks 
            //footways.printIntersect(B); // find all intersecting footways
        }
    }


    if (!found)
        cout << "No such building" << endl;
}

