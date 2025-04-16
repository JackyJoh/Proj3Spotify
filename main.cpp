#include <iostream>
#include <string>
#include <sstream>
#include "httplib.h"
#include "rapidcsv.h"
#include "backend.h"


using namespace std;



std::string get(int id) {
    // Hardcoded example song
    return "Song ID: " + std::to_string(id) +
           "\nTitle: Example Song"
           "\nArtist: Example Artist";
}

// int main() {
//     httplib::Server svr;
//
//     // Handle GET request
//     svr.Get("/song", [](const httplib::Request& req, httplib::Response& res) {
//         std::string song = getSong(100);
//         res.set_content(song, "text/plain");
//     });
//
//     std::cout << "Server starting on port 8080..." << std::endl;
//
//     // Add error handling for server start
//     if (!svr.listen("localhost", 8080)) {
//         std::cerr << "Failed to start server!" << std::endl;
//         return 1;
//     }
//
//     return 0;
//}
int main() {
    httplib::Server svr;


    svr.Get("/", [](const httplib::Request&, httplib::Response& res) {
        // Get song data
        std::string song_data = getSong(100000);

        // Set response headers and content
        res.set_header("Access-Control-Allow-Origin", "*");
        res.set_header("Content-Type", "application/json");
        res.set_content(song_data, "application/json");
    });

    std::cout << "Starting server on port 8080..." << std::endl;
    svr.listen("0.0.0.0", 8080);



}