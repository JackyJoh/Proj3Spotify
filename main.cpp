#include <iostream>
#include <string>
#include <sstream>
#include "httplib.h"
#include "rapidcsv.h"
#include "backend.h"


using namespace std;


//Pass in document to avoid loading multiple times
string getSong(vector<Song> song, rapidcsv::Document doc) {
    std::stringstream json;
    json << "{\n";

    for(int i = 0; i < 7; i++) {
        json << "    \"artist" << i+1 << "\": \"" << strip(escapeJSON(song[i].artist)) << "\",\n";
        json << "    \"album" << i+1 << "\": \"" << strip(escapeJSON(song[i].album_name)) << "\",\n";
        json << "    \"trackName" << i+1 << "\": \"" << strip(escapeJSON(song[i].track_name)) << "\",\n";
        json << "    \"score" << i+1 << "\": \"" << escapeJSON(to_string(randomNumber())) << "\",\n";
        json << "    \"genre" << i+1 << "\": \"" << strip(escapeJSON(song[i].genre)) << "\",\n";
        json << "    \"danceability" << i+1 << "\": \"" << strip(escapeJSON(to_string(song[i].danceability*100))) << "\",\n";
        json << "    \"energy" << i+1 << "\": \"" << strip(escapeJSON(to_string(100* song[i].energy))) << "\",\n";
        json << "    \"duration" << i+1 << "\": \"" << strip(escapeJSON(to_string(song[i].duration_ms /1000))) << "\",\n";
        json << "    \"tempo" << i+1 << "\": \"" << strip(escapeJSON(to_string(song[i].tempo))) << "\"";

        // Add comma if not the last song
        if(i < 6) {
            json << ",\n";
        } else {
            json << "\n";
        }
    }

    json << "}";
    return json.str();
}


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
            cout << getSong(arrExample, songs)  << endl;



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