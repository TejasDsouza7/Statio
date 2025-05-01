#pragma once
#include <string>

struct SatelliteMeta {
    std::string name;
    std::string country;
    std::string objectType;
    std::string launch;
};

class SpaceTrackClient {
public:
    SpaceTrackClient(const std::string& user, const std::string& pass);
    SatelliteMeta getMetadata(const std::string& noradId);

private:
    std::string cookieFile;
    std::string username;
    std::string password;
    bool login();
};
