#include <iostream>
#include <string>
#include <sstream>
#include "httplib.h"
#include "rapidcsv.h"
#include "backend.h"
#include "algorithms.h"


using namespace std;


//Pass in document to avoid loading multiple times
string getSong(int songId, rapidcsv::Document doc) {

    Song song( doc.GetRow<string>(songId)); //creates a song struct from the 10th row of data

    std::stringstream json;
    json << "{\n";
    json << "    \"artist\": \"" << strip(escapeJSON(song.artist)) << "\",\n";
    json << "    \"album\": \"" << strip(escapeJSON(song.album_name)) << "\",\n";
    json << "    \"trackName\": \"" << strip(escapeJSON(song.track_name)) << "\",\n";
    json << "    \"score\": \"" << escapeJSON(to_string(randomNumber())) << "\"\n";

    json << "}";
    return json.str();

    //for all 7 songs make the titles dependent on the node
    //ex. for node 3, do artist "    \"artist3\": \"" << strip(escapeJSON(song.artist)) << "\",\n";
    //and in js make id artist3.textContent = data.artist3
}


int main() {
    rapidcsv::Document songs("data/dataset.csv"); //sets the doc to read from
    vector<Song*> songv(114000);
    for (int i = 0; i < songv.size(); i++) {
        songv[i] = new Song(songs.GetRow<string>(i));
    }
    string track;
    getline(cin, track);
    vector<pair<Song*, float>> test = mostSimilar(songv[stoi(track)], songv);

    cout << songv[stoi(track)]->track_name << "\n";
    for (int i = 0; i < test.size(); i++) {
        cout << test[i].first->track_name << ": "  << test[i].first->artist << ": " << test[i].second << "\n";
    }

    //call my function mostSimilar(Song* ref, vector<Song*> allS); where ref is the song used as a reference and allS is songv
    httplib::Server svr;


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
            stringstream response;
            response << getSong(songIndex, songs);
            //cout << getSong(songIndex, songs)  << endl;



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