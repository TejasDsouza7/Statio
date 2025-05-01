#pragma once
#include <string>

class SatelliteTracker {
public:
    SatelliteTracker(const std::string& apiKey, double lat, double lon, double alt);
    void trackISS();
    void satellitesAbove();
    void trackByNorad(const std::string& noradId);

private:
    std::string apiKey;
    double latitude, longitude, altitude;
};
