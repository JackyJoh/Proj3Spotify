#include <iostream>
#include <string>
#include <sstream>
#include "httplib.h"
#include "rapidcsv.h"
#include "backend.h"
#include "algorithms.h"
#include "trieTree.h"

using namespace std;




int main() {
    rapidcsv::Document songs("data/dataset.csv"); //sets the doc to read from
    vector<Song*> songv(114000);
    Trie songTree;
    for (int i = 0; i < songv.size(); i++) {
        songv[i] = new Song(songs.GetRow<string>(i));
        songTree.insert(songv[i]->track_name, i);
    }
    //call search on the trie tree with a string (must be a variable since its a reference) i.e songTree(myString); returns the index of the song in the vector
    //call my function mostSimilar(Song* ref, vector<Song*> allS); where ref is the song used as a reference and allS is songv
    httplib::Server svr;

    svr.Options(".*", [](const auto& req, auto& res) {
        //res.set_header("Access-Control-Allow-Origin", "http://127.0.0.1:5500");
        res.set_header("Access-Control-Allow-Origin", "http://localhost:63342");
        res.set_header("Access-Control-Allow-Methods", "GET, POST, OPTIONS");
        res.set_header("Access-Control-Allow-Headers", "Content-Type");
        return res.set_content("", "text/plain");
    });

    svr.Post("/updateSong", [songs, &songv](const httplib::Request &req, httplib::Response &res) {
        try {
            res.set_header("Access-Control-Allow-Origin", "http://localhost:63342");

            string body = req.body;
            // size_t msgStart = body.find("\"message\"");
            // size_t colonPos = body.find(":", msgStart);
            // size_t startQuote = body.find("\"", colonPos);
            // size_t endQuote = body.find("\"", startQuote + 1);
            string recieved = body;

            //random song testing
            int random = rand() % 100001;
            Song* song = songv[random];
            vector<pair<Song*,float>> inputSongs = mostSimilar(songv[random], songv);



            //Create JSON response with song details
            // int songIndex = stoi(recieved);
            // vector<Song> arrExample;
            // for (int i =0; i < 64; i++)
            // {
            //     arrExample.push_back(Song(songs.GetRow<string>(songIndex+i)));
            // }

            stringstream response;
            response << "{\n";
            response << "    \"main" << "\": \"" << strip(escapeJSON(song->track_name)) << "\",\n";

            //pass in vector of 7 songs
            response << getSong(inputSongs);


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