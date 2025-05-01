#include "spacetrack.hpp"
#include "utils.hpp"
#include "json.hpp"
#include <iostream>
#include <fstream>
#include <curl/curl.h>

using json = nlohmann::json;

SpaceTrackClient::SpaceTrackClient(const std::string& user, const std::string& pass)
    : username(user), password(pass), cookieFile("/tmp/spacetrack_cookies.txt") {
    login();
}

bool SpaceTrackClient::login() {
    CURL* curl = curl_easy_init();
    if (!curl) return false;

    std::string postData = "identity=" + username + "&password=" + password;
    curl_easy_setopt(curl, CURLOPT_URL, "https://www.space-track.org/ajaxauth/login");
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postData.c_str());
    curl_easy_setopt(curl, CURLOPT_COOKIEJAR, cookieFile.c_str());
    curl_easy_setopt(curl, CURLOPT_COOKIEFILE, cookieFile.c_str());
    curl_easy_setopt(curl, CURLOPT_USERAGENT, "StatioBot/1.0");
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, [](char* ptr, size_t size, size_t nmemb, void*) {
        return size * nmemb;
    });

    CURLcode res = curl_easy_perform(curl);
    curl_easy_cleanup(curl);

    return res == CURLE_OK;
}

SatelliteMeta SpaceTrackClient::getMetadata(const std::string& noradId) {
    SatelliteMeta meta = { "Unknown", "Unknown", "Unknown", "Unknown" };

    CURL* curl = curl_easy_init();
    if (!curl) return meta;

    std::string url = "https://www.space-track.org/basicspacedata/query/class/satcat/NORAD_CAT_ID/"
                      + noradId + "/format/json";

    std::string response;
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_COOKIEFILE, cookieFile.c_str());
    curl_easy_setopt(curl, CURLOPT_USERAGENT, "StatioBot/1.0");
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, +[](void* ptr, size_t size, size_t nmemb, void* data) -> size_t {
        ((std::string*)data)->append((char*)ptr, size * nmemb);
        return size * nmemb;
    });
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

    CURLcode res = curl_easy_perform(curl);
    curl_easy_cleanup(curl);

    if (res != CURLE_OK || response.empty()) return meta;

    try {
        json arr = json::parse(response);
        if (!arr.empty()) {
            auto& sat = arr[0];
            meta.name = sat["SATNAME"].get<std::string>();
            meta.country = sat["COUNTRY"].get<std::string>();
            meta.objectType = sat["OBJECT_TYPE"].get<std::string>();
            meta.launch = sat["LAUNCH"].get<std::string>();
        }
    } catch (...) {}

    return meta;
}
