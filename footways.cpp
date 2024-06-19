/*footways.cpp*/

// Bella Fishman
// Northwestern University
// CS 211

//
// Implements methods from footways.h
// Allows to search footways and find matching building ids and more
//

#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <algorithm>
#include <cassert>

#include "footways.h"
#include "tinyxml2.h"
#include "osm.h"

using namespace std;
using namespace tinyxml2;

    
// 
// readMapBuildings
//
// Given an XML document, reads through the document and 
// stores all the footways into the given vector
//
void Footways::readMapFootways(XMLDocument& xmldoc){
    // get first child
    XMLElement* osm = xmldoc.FirstChildElement("osm");
    assert(osm != nullptr);
    
    // begins traversal at first "way" - indicates buildings
    XMLElement* way = osm->FirstChildElement("way");
    while (way != nullptr){
        // if contains (key, val) pair (highway, footway), 
        // then add building to vector
        if (osmContainsKeyValue(way, "highway", "footway") || osmContainsKeyValue(way, "area:highway", "footway")){
            const XMLAttribute* attrID = way->FindAttribute("id");
            assert(attrID != nullptr);
            long long id = attrID->Int64Value();

            // create Footway object
            Footway F(id);

            // need to add vector of NodeIDs by looping through "nd"s
            XMLElement* nd = way->FirstChildElement("nd");
            while (nd != nullptr)
            {
                const XMLAttribute* ndref = nd->FindAttribute("ref");
                assert(ndref != nullptr);
                long long node_id = ndref->Int64Value();
                F.add(node_id);

                // advance to next node ref
                nd = nd->NextSiblingElement("nd");
            }

            // fully initialized and add to Buildings vector
            // use push_back to copy the vector B
            this->MapFootways.push_back(F);
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
// getNumMapFootways
// returns the # of footways in the MapFootways
int Footways::getNumMapFootways() const{
  return (int) this->MapFootways.size();
}

//
// given a Building, finds any intersecting footways
//
void Footways::printIntersect(Building B) const{
    // sort buildings node_ids                          /// O(nlogn)
    sort(B.NodeIDs.begin(), B.NodeIDs.end(), [](long long id1, long long id2)
        {if (id1 < id2) 
            return true;
        else
            return false;});

            
    vector<long long> Footway_List;
    bool yes;
    for (Footway F : MapFootways){ // loop through every footway
        // for each id in footway, perform binary search for build id
        yes = this->binary_Buildings(F, B);
        if (yes == true){ // if we found an intersect
            Footway_List.push_back(F.ID);
        }
    } // for
    // print in correct format with print function now
    this->print(Footway_List);
}

//
// loops through Footway ID vector and performs binary search on building NodeIDs
// returns true if it intersects with building and false otherwise
//
// binary_Buildings
//
bool Footways::binary_Buildings(const Footway& F, const Building& B) const{
    for (long long F_id : F.NodeIDs){
        bool result = this->binarySearch(F_id, B);
        // if true, move onto next footway, so only each footway is returned once
        if (result == true){
            return true;
        }
        // otherwise keep looping until done
    }
    return false;
}

// 
// Binary Searches through given inputs to find a matching input
// vector must be sorted!
//
// binarySearch
bool Footways::binarySearch(const long long& F_id, const Building& B) const{
    int low = 0;
    int high = (int) size(B.NodeIDs) - 1;
    
    while (low <= high) {
        int mid = low + ((high - low) / 2);
        long long nodeid = B.NodeIDs[mid];
        if (F_id == nodeid) { // found!
            // save to vector
            return true;
        }
        else if (F_id < nodeid){ // search left
            high  = mid - 1;
        }
        else { // search right
            low = mid + 1;
        }
    } //while
    //
    // if get here, not found:
    //
    return false;
}


//
// print
// sorts in ascending order and prints the intersecting footways with a building
// in the correct format
//
void Footways::print(vector<long long>& Footway_List) const{
    // sort in ascending order
    // int n = sizeof(Footway_List) / sizeof(Footway_List[0]);
    sort(Footway_List.begin(), Footway_List.end(), [](long long id1, long long id2)
        {if (id1 < id2) 
            return true;
        else
            return false;});
    
    int size = Footway_List.size();
    
    cout << "Footways that intersect: " << size << endl; 
    if (size > 0) {
        for (auto item : Footway_List){
            cout << "  Footway " << item << endl;
        } // for
    }
    else {
        cout << "  None" << endl;
    }

}
