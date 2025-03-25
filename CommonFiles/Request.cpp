//
//

#include <iostream>
#include "Request.hpp"
#include <iomanip>

Request::Request(double rTime, int rTrack, int rSector) : _time(rTime), _track(rTrack), _sector(rSector) {}

int Request::track() { return _track; }

int Request::sector() { return _sector; }

double Request::time() { return _time; }

void Request::print() {
    std::cout << std::setw(8) << time() << "      " << std::setw(5) << track() << "     " << std::setw(5) << sector() << std::endl;
}
