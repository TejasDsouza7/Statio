#pragma once
#include <string>

struct Location {
    double latitude;
    double longitude;
    double altitude;
};

Location getUserLocation();
