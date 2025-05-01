#include "tracker.hpp"
#include "spacetrack.hpp"
#include "json.hpp"
#include "utils.hpp"
#include <iostream>
#include <curl/curl.h>
#include <thread>
#include <chrono>

using json = nlohmann::json;
using namespace std::chrono_literals;

SatelliteTracker::SatelliteTracker(const std::string& key, double lat, double lon, double alt)
    : apiKey(key), latitude(lat), longitude(lon), altitude(alt) {}

void SatelliteTracker::trackISS() {
    std::string url = "https://api.n2yo.com/rest/v1/satellite/positions/25544/" +
                      std::to_string(latitude) + "/" +
                      std::to_string(longitude) + "/" +
                      std::to_string(altitude) + "/1/&apiKey=" + apiKey;

    std::string response = fetchURL(url);
    json data = json::parse(response);
    auto pos = data["positions"][0];
    
    std::cout << "🛰️ ISS Location:\n"
              << "Latitude: " << pos["satlatitude"] << "\n"
              << "Longitude: " << pos["satlongitude"] << "\n"
              << "Altitude: " << pos["sataltitude"] << " km\n";
}

void SatelliteTracker::satellitesAbove() {
    std::string url = "https://api.n2yo.com/rest/v1/satellite/above/" +
                      std::to_string(latitude) + "/" +
                      std::to_string(longitude) + "/" +
                      std::to_string(altitude) +
                      "/90/18/&apiKey=" + apiKey;

    std::string response = fetchURL(url);
    json data = json::parse(response);

    std::cout << "\n🔭 Satellites Above You:\n";

    std::string user = std::getenv("SPACETRACK_USER");
    std::string pass = std::getenv("SPACETRACK_PASS");
    SpaceTrackClient client(user, pass);

    for (const auto& sat : data["above"]) {
        std::string norad = std::to_string(sat["satid"].get<int>());
        SatelliteMeta meta = client.getMetadata(norad);

        std::cout << "\n📡 " << meta.name << " (NORAD ID: " << norad << ")\n"
                  << "🏳️ Country: " << meta.country << "\n"
                  << "🎯 Purpose: " << meta.objectType << "\n"
                  << "📅 Launch Date: " << meta.launch << "\n";
    }
}

void SatelliteTracker::trackByNorad(const std::string& noradId) {
    std::string url = "https://api.n2yo.com/rest/v1/satellite/positions/" + 
                      noradId + "/" +
                      std::to_string(latitude) + "/" +
                      std::to_string(longitude) + "/" +
                      std::to_string(altitude) + "/1/&apiKey=" + apiKey;

    std::string response = fetchURL(url);
    json data = json::parse(response);
    auto pos = data["positions"][0];

    std::cout << "📡 Satellite Location:\n"
              << "Latitude: " << pos["satlatitude"] << "\n"
              << "Longitude: " << pos["satlongitude"] << "\n"
              << "Altitude: " << pos["sataltitude"] << " km\n";
}

 