#include <iostream>
#include <string>
#include <sstream>
#include "httplib.h"
#include "rapidcsv.h"
#include "backend.h"
#include "algorithms.h"
#include "trieTree.h"


using namespace std;

#include <random>
#include <ctime>




int main() {
    rapidcsv::Document songs("data/dataset.csv"); //sets the doc to read from
    vector<Song*> songv(114000);
    Trie songTree;

    for (int i = 0; i < songv.size(); i++) {
        songv[i] = new Song(songs.GetRow<string>(i));
        songTree.insert(songv[i]->track_name, i);
    }


    //call my function mostSimilar(Song* ref, vector<Song*> allS); where ref is the song used as a reference and allS is songv
    httplib::Server svr;

    svr.Options(".*", [](const auto& req, auto& res) {
        res.set_header("Access-Control-Allow-Origin", "http://localhost:63342");
        res.set_header("Access-Control-Allow-Methods", "GET, POST, OPTIONS");
        res.set_header("Access-Control-Allow-Headers", "Content-Type");
        return res.set_content("", "text/plain");
    });

    svr.Post("/updateSong", [&songv, &songTree](const httplib::Request &req, httplib::Response &res) {
        try {
            res.set_header("Access-Control-Allow-Origin", "http://localhost:63342");


            string body = req.body;
            string recieved = body;

            //cout << recieved << "\n";
            int index;
            if (recieved == "\"random\"")
            {
                index = rand() % songv.size() - 1;
            } else
            {
                index = songTree.search(recieved);
            }
            Song* song = songv[index];
            vector<pair<Song*,float>> inputSongs = mostSimilar(songv[index], songv);


            stringstream response;
            response << "{\n";
            response << "    \"main" << "\": \"" << strip(escapeJSON(song->track_name)) << "\",\n";
            response << "    \"main2" << "\": \"" << strip(escapeJSON(song->artist)) << "\",\n";

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