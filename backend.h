    //
    // Created by jacka on 4/15/2025.
    //
    #include "rapidcsv.h"
    #ifndef BACKEND_H
    #define BACKEND_H
    using namespace std;


    struct Song {
        int serial;
        string track_id;
        string artist;
        string album_name;
        string track_name;
        int popularity;
        int duration_ms;
        bool explicit_content;
        double danceability;
        double energy;
        int key;
        double loudness;
        int mode;
        double speechiness;
        double acousticness;
        string instrumentalness;
        double liveness;
        double valence;
        double tempo;
        int time_signature;
        string genre;

        //Base constructor
        Song(const vector<string>& values) {
            if (values.size() >= 21) {  //Ensure we have all needed values
                serial = stoi(values[0]);
                track_id = values[1];
                artist = values[2];
                album_name = values[3];
                track_name = values[4];
                popularity = stoi(values[5]);
                duration_ms = stoi(values[6]);
                explicit_content = values[7] == "True";
                danceability = stod(values[8]);
                energy = stod(values[9]);
                key = stoi(values[10]);
                loudness = stod(values[11]);
                mode = stoi(values[12]);
                speechiness = stod(values[13]);
                acousticness = stod(values[14]);
                instrumentalness = values[15];
                liveness = stod(values[16]);
                valence = stod(values[17]);
                tempo = stod(values[18]);
                time_signature = stoi(values[19]);
                genre = values[20];
            }
        }

        //Default constructor
        // Song()
        //     : serial(0), track_id(""), artist(""), album_name(""), track_name(""),
        //       popularity(""), duration_ms(""), explicit_content(""), danceability(""),
        //       energy(""), key(""), loudness(""), mode(""), speechiness(""),
        //       acousticness(""), instrumentalness(""), liveness(""), valence(""),tempo(""), time_signature(""), genre("") {}

    };

    void printSongColumns(Song song) {
        cout << "1. Serial: " << song.serial << endl;
        cout << "2. Track ID: " << song.track_id << endl;
        cout << "3. Artist: " << song.artist << endl;
        cout << "4. Album Name: " << song.album_name << endl;
        cout << "5. Track Name: " << song.track_name << endl;
        cout << "6. Popularity: " << song.popularity << endl;
        cout << "7. Duration (ms): " << song.duration_ms << endl;
        cout << "8. Explicit Content: " << song.explicit_content << endl;
        cout << "9. Danceability: " << song.danceability << endl;
        cout << "10. Energy: " << song.energy << endl;
        cout << "11. Key: " << song.key << endl;
        cout << "12. Loudness: " << song.loudness << endl;
        cout << "13. Mode: " << song.mode << endl;
        cout << "14. Speechiness: " << song.speechiness << endl;
        cout << "15. Acousticness: " << song.acousticness << endl;
        cout << "16. Instrumentalness: " << song.instrumentalness << endl;
        cout << "17. Liveness: " << song.liveness << endl;
        cout << "18. Valence: " << song.valence << endl;
        cout << "19. Tempo: " << song.tempo << endl;
        cout << "20. Time Signature: " << song.time_signature << endl;
        cout << "21. Genre: " << song.genre << endl;
        cout << "------------------------" << endl;
    }

    string escapeJSON(const string& str) {
        string escaped;
        for (char c : str) {
            if (c == '\"' || c == '\\' || iscntrl(c)) {
                escaped += '\\';
                escaped += c;
            } else {
                escaped += c;
            }
        }
        return escaped;
    }

    //If there are multiple artists, only shows the first
    string strip(const string& str)
    {
        string::size_type start = 0;
        string::size_type end = str.find(";");
        return str.substr(start, end - start);

    }
    double randomNumber()
    {
        return 1.0 + (rand() % 100) + (static_cast<double>(rand()) / RAND_MAX);
    }


//Pass in document to avoid loading multiple times
    string getSong(vector<Song> song, rapidcsv::Document doc) {
        stringstream json;
        json << "{\n";

        for(int i = 0; i < 7; i++) {
            json << "    \"artist" << i+1 << "\": \"" << strip(escapeJSON(song[i].artist)) << "\",\n";
            json << "    \"album" << i+1 << "\": \"" << strip(escapeJSON(song[i].album_name)) << "\",\n";
            json << "    \"trackName" << i+1 << "\": \"" << strip(escapeJSON(song[i].track_name)) << "\",\n";

            //Two decimals for score etc
            stringstream score, dance, energy, duration, tempo;
            score << fixed << setprecision(2) << randomNumber();
            dance << fixed << setprecision(2) << (song[i].danceability * 100);
            energy << fixed << setprecision(2) << (song[i].energy * 100);
            duration << fixed << setprecision(0) << (song[i].duration_ms / 1000.0);
            tempo << fixed << setprecision(2) << song[i].tempo;

            json << "    \"score" << i+1 << "\": \"" << escapeJSON(score.str()) << "\",\n";
            json << "    \"genre" << i+1 << "\": \"" << strip(escapeJSON(song[i].genre)) << "\",\n";
            json << "    \"danceability" << i+1 << "\": \"" << strip(escapeJSON(dance.str())) << "\",\n";
            json << "    \"energy" << i+1 << "\": \"" << strip(escapeJSON(energy.str())) << "\",\n";
            json << "    \"duration" << i+1 << "\": \"" << strip(escapeJSON(duration.str())) << "\",\n";
            json << "    \"tempo" << i+1 << "\": \"" << strip(escapeJSON(tempo.str())) << "\"";

            if(i < 6) {
                json << ",\n";
            } else {
                json << "\n";
            }
        }

        json << "}";
        return json.str();
    }






    #endif //BACKEND_H
