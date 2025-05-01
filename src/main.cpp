#include <iostream>
#include "tracker.hpp"
#include "location.hpp"

int main() {
    std::string apiKey = getenv("N2YO_API_KEY");
    if (apiKey.empty()) {
        std::cerr << "Please set N2YO_API_KEY in .env\n";
        return 1;
    }

    Location userLoc = getUserLocation();
    std::cout << "📍 You are at: " << userLoc.latitude << ", " << userLoc.longitude << "\n\n";

    SatelliteTracker tracker(apiKey, userLoc.latitude, userLoc.longitude, userLoc.altitude);

    tracker.trackISS();
    tracker.satellitesAbove();
    
    std::string noradId;
    std::cout << "\n🔍 Enter NORAD ID to track a satellite: ";
    std::cin >> noradId;
    tracker.trackByNorad(noradId);

    return 0;
}
