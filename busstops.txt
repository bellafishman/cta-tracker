/*busstops.cpp*/

// Bella Fishman
// Northwestern University
// CS 211

//
// Implements methods from busstops.h
//

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cassert>
#include <fstream>
#include <sstream>
#include <queue>
#include <stdexcept>

#include "busstops.h"
#include "tinyxml2.h"
#include "osm.h"

#include "json.hpp"
using json = nlohmann::json;



using namespace std;
using namespace tinyxml2;



//
// readBusStops
//
// Given an txt document, reads through the document and 
// stores all the busstops into the given vector. Each busstop
// contains a stop ID, bus route, stop name, direction, and location of stop and
// location in lat and long
//
void BusStops::readBusStops(string filename){
    ifstream input;
    input.open(filename);


    while (!input.eof()){
        string line;
        getline(input, line);

        if (input.fail())
            break;
        
        stringstream parser(line);
        string stopID, busroute, stopname, direction, stoplocation, positionlat, positionlong;
        // parse data that is separated by commas
        getline(parser, stopID, ',');
        getline(parser, busroute, ',');
        getline(parser, stopname, ',');
        getline(parser, direction, ',');
        getline(parser, stoplocation, ',');
        getline(parser, positionlat, ',');
        getline(parser, positionlong, ',');

        // build new BusStop object and add to vector
        BusStop B(stoll(stopID), stoi(busroute), stopname, direction, stoplocation, make_pair(stod(positionlat), stod(positionlong)) );
        // add to bus stop map
        this->MapBusStops.push_back(B);
    } // while 

    // sort busstops stopIDs                          /// O(nlogn)
    sort(this->MapBusStops.begin(), this->MapBusStops.end(), [](const BusStop& lhs, const BusStop& rhs) {
      return lhs.StopID < rhs.StopID;
    });
}

//
// accessors / getters
//
// returns number of bus stops in map
int BusStops::getNumBusStops() const{
    return (int) this->MapBusStops.size();
}

// print
// prints all of the BusStops in a given file in the ascending order of stop ids
void BusStops::print() const {
    for (const BusStop& B : MapBusStops) {
        B.print();
    }
}

// 
// findNearest
// find the nearest bus stop - Northbound AND Southbound to a given building
void BusStops::findNearest(Building& building, pair<double, double> b_location, CURL* curl) {
    // Custom comparator for the priority queue
    priority_queue<pair<double, BusStop>, vector<pair<double, BusStop>>, ComparePairs> pq;

    // calculate location btwn building and each busstop
    for (const BusStop& bus : MapBusStops){
        // calc distance w/ dist.h
        double dist = distBetween2Points(b_location.first, b_location.second, bus.Position.first, bus.Position.second);
        pq.push(make_pair(dist, bus));
    }

    // Go through top elements of Priority Queue to find closest south and north bound
    BusStop south = MapBusStops[1];
    BusStop north = MapBusStops[1];
    double northval = 0;
    double southval = 0;
    while (northval == 0 or southval == 0){
        if (!pq.empty()) {
            pair<double, BusStop> top = pq.top();
            pq.pop();

            if ((top.second.Direction == "Northbound") && (northval == 0)) {
                north = top.second;
                northval = top.first;
            }
            else if ((top.second.Direction == "Southbound") && (southval == 0)) {
                south = top.second;
                southval = top.first;
            }
        }
    }
    // closest southbound bus
    cout << "Closest southbound bus stop:" << endl;
    cout << "  " << south.StopID << ": " << south.StopName << ", bus #" << south.BusRoute << ", " << south.StopLocation << ", " << southval << " miles" << endl;
    // use API to find vehicle num, route num, direction, and mins away
    string key = "6NNgwWpprVKvSDyVJZQT2yFzB";
    printBusPredictions(south, key, curl);

    // closest northbound bus
    cout << "Closest northbound bus stop:" << endl;
    cout << "  " << north.StopID << ": " << north.StopName << ", bus #" << north.BusRoute << ", " << north.StopLocation << ", " << northval << " miles" << endl;
    // use API to find vehicle num, route num, direction, and mins away
    printBusPredictions(north, key, curl);
}


// 
// finds API for a bus stop and prints relevant data 
// handles exceptions in handling
//
int BusStops::printBusPredictions(BusStop& bus, string& key, CURL* curl){
    // API Key: 6NNgwWpprVKvSDyVJZQT2yFzB
    string API = "https://ctabustracker.com/bustime/api/v2/getpredictions?key=" + key + "&rt=" + to_string(bus.BusRoute) + "&stpid=" + to_string(bus.StopID) + "&format=json";
    string response;
    bool success = callWebServer(curl, API, response);
    if (!success){ // returned false, error in message or curl or API
        cout << "  <<bus predictions unavailable, call failed>>" << endl;
        return 0;
    }
    else { // extract and print predictions
        auto jsondata = json::parse(response);
        if (jsondata.empty()) {
            cout << "  <<no predictions available>>" << endl;
            return 0; 
        }
        // extract key val from "bustime-response" // val bus_response is another map
        auto bus_response = jsondata["bustime-response"];
        // open map with key "prd"
        auto predictions = bus_response["prd"];
        if (predictions.empty()) {
            cout << "  <<no predictions available>>" << endl;
            return 0; 
        }
        // for each prediction (a map) in the list:
        // WARNING: many errors can occur here -> need exception handling
        for (auto& M : predictions) {
            try {
                string s = M["rtdir"];
                s.erase(remove( s.begin(), s.end(), '\"' ),s.end());
                cout << "  vehicle #" << stoi(M["vid"].get_ref<std::string&>()) << " on route " << stoi(M["rt"].get_ref<std::string&>()) << " travelling " <<
                s << " to arrive in " << stoi(M["prdctdn"].get_ref<std::string&>()) << " mins" << endl;
            }
            // check if any keys missing from map or value is empty/invalid
            catch (exception& e){
                cout << "  error" << endl;
                cout << " malformed CTA response, prediction unavailable"
                << " (error: " << e.what() << ")" << endl;
            }
        }
        return 0;
    }
    return 0;
}

