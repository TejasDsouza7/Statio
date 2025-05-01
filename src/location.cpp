#include "location.hpp"
#include "json.hpp"
#include "utils.hpp"

using json = nlohmann::json;

Location getUserLocation() {
    std::string url = "http://ip-api.com/json";
    std::string response = fetchURL(url);
    json data = json::parse(response);

    Location loc;
    loc.latitude = data["lat"];
    loc.longitude = data["lon"];
    loc.altitude = 0; 
    return loc;
}
