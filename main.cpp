#include <iostream>
#include <string>
#include <sstream>
#include "httplib.h"
#include "rapidcsv.h"
#include "backend.h"


using namespace std;




int main() {
    httplib::Server svr;
    rapidcsv::Document songs("data/dataset.csv"); //sets the doc to read from


    svr.Options(".*", [](const auto& req, auto& res) {
        //res.set_header("Access-Control-Allow-Origin", "http://127.0.0.1:5500");
        res.set_header("Access-Control-Allow-Origin", "http://localhost:63342");
        res.set_header("Access-Control-Allow-Methods", "GET, POST, OPTIONS");
        res.set_header("Access-Control-Allow-Headers", "Content-Type");
        return res.set_content("", "text/plain");
    });

    svr.Post("/updateSong", [songs](const httplib::Request &req, httplib::Response &res) {
        try {
            res.set_header("Access-Control-Allow-Origin", "http://localhost:63342");

            string body = req.body;
            // size_t msgStart = body.find("\"message\"");
            // size_t colonPos = body.find(":", msgStart);
            // size_t startQuote = body.find("\"", colonPos);
            // size_t endQuote = body.find("\"", startQuote + 1);
            string recieved = body;


            //TODO: place names of functions below
            //TODO: FOR WHEN BACKEND IS DONE
            //Song input = trieFunction(recieved) //takes the input and finds the closest name, returns a song struct
            //vector<Song> closestSongs = maxHeapFunction(input) //gets the 7 closest songs
            //response << getSong(closestSongs, songs) //creates the Json with proper data

            //cout << "Received song name: " << receivedSong << endl;


            //Create JSON response with song details
            int songIndex = stoi(recieved);
            vector<Song> arrExample;
            for (int i =0; i < 64; i++)
            {
                arrExample.push_back(Song(songs.GetRow<string>(songIndex+i)));
            }

            stringstream response;

            //pass in vector of 7 songs
            response << getSong(arrExample, songs);


            res.set_content(response.str(), "application/json");
        } catch (const exception& e) {
            stringstream error_response;
            error_response << "{\"status\": \"error\", \"message\": \"" << e.what() << "\"}";
            res.set_content(error_response.str(), "application/json");
        }
    });

    cout << "Server started on port 8080..." << endl;
    svr.listen("localhost", 8080);
    return 0;
}