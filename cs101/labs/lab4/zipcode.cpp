#include <iostream>

#include "zipcode.h"

using namespace std;

/*
enum class CompareType {
    LessZip,
    LessCityState,
    LessStateCity,
    LessLatLonState,
    LessLonLatState
};
*/
// Complete this method by implementing the comparison logic
bool ZipCode::compare(ZipCode &rhs, ZipCode::CompareType t) {
	switch (t) {
		case CompareType::LessZip:
			return (this->getZip() < rhs.getZip());
		case CompareType::LessCityState:
			if (this->getCity() < rhs.getCity()) { return true; }
			if (this->getCity() > rhs.getCity()) { return false; }
			if (this->getState() < rhs.getState()) { return true; }
			if (this->getState() > rhs.getState()) { return false; }
			return false;
		case CompareType::LessStateCity:
			if (this->getState() < rhs.getState()) { return true; }
			if (this->getState() > rhs.getState()) { return false; }
			if (this->getCity() < rhs.getCity()) { return true; }
			if (this->getCity() > rhs.getCity()) { return false; }
			return false;
		case CompareType::LessLatLonState:
			if (this->getLat() < rhs.getLat()) { return true; }
			if (this->getLat() > rhs.getLat()) { return false; }
			if (this->getLon() < rhs.getLon()) { return true; }
			if (this->getLon() > rhs.getLon()) { return false; }
			if (this->getState() < rhs.getState()) { return true; }
			if (this->getState() > rhs.getState()) { return false; }
			return false;
		case CompareType::LessLonLatState:
			if (this->getLon() < rhs.getLon()) { return true; }
			if (this->getLon() > rhs.getLon()) { return false; }
			if (this->getLat() < rhs.getLat()) { return true; }
			if (this->getLat() > rhs.getLat()) { return false; }
			if (this->getState() < rhs.getState()) { return true; }
			if (this->getState() > rhs.getState()) { return false; }
			return false;
		default:
			return false;
	}
    return false;  
}

// Do not edit below this line

ZipCode::ZipCode(int zip, string city, string state, int lat, int lon) {
    this->zip = zip;
    this->city = city;
    this->state = state;
    this->lat = lat;
    this->lon = lon;
}

void ZipCode::print() {
    cout << zip << "\t" << city << "\t";
    if (city.length() < 8) cout << "\t";
    cout << state << "\t" << lat << "\t"<< lon;
}

int ZipCode::getZip() {
    return zip;
}

string ZipCode::getCity() {
    return city;
}

string ZipCode::getState() {
    return state;
}

int ZipCode::getLat() {
    return lat;
}

int ZipCode::getLon() {
    return lon;
}
