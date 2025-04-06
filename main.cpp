#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include <vector>


using namespace std;

struct Song {
    int serial;
    string track_id;
    string artist;
    string album_name;
    string track_name;
    string popularity;
    string duration_ms;
    string explicit_content;
    string danceability;
    string energy;
    string key;
    string loudness;
    string mode;
    string speechiness;
    string acousticness;
    string instrumentalness;
    string liveness;
    string valence;
    string tempo;
    string time_signature;
    string genre;

    // Parameterized constructor
    Song(int serial, string track_id, string artist, string album_name, string track_name,
         string popularity, string duration_ms, string explicit_content, string danceability,
         string energy, string key, string loudness, string mode, string speechiness,
         string acousticness, string instrumentalness, string liveness, string valence,
         string tempo, string time_signature, string genre)
        : serial(serial), track_id(track_id), artist(artist), album_name(album_name),
          track_name(track_name), popularity(popularity), duration_ms(duration_ms),
          explicit_content(explicit_content), danceability(danceability), energy(energy),
          key(key), loudness(loudness), mode(mode), speechiness(speechiness),
          acousticness(acousticness), instrumentalness(instrumentalness),
          liveness(liveness), valence(valence), tempo(tempo), time_signature(time_signature),
          genre(genre) {}

    // Default constructor
    Song()
        : serial(0), track_id(""), artist(""), album_name(""), track_name(""),
          popularity(""), duration_ms(""), explicit_content(""), danceability(""),
          energy(""), key(""), loudness(""), mode(""), speechiness(""),
          acousticness(""), instrumentalness(""), liveness(""), valence(""),tempo(""), time_signature(""), genre("") {}

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

int main()
{
    // vector<Song> songList;
    string line;
    int index=0;
    Song* songList = new Song[114000];
    ifstream file("data/dataset.csv");

    cout << "test change" << endl;
    // Skip header line
    getline(file, line);
    // Read data line by line
    while (getline(file, line))
    {
        //cout << line << "\n";
        stringstream ss(line);
        Song song;



        // Parse CSV line
        for (int i = 0; i < 21; i++)
        {

            string item = (line.substr(0, line.find(",")));
            //cout << item << endl;// Extract the value before the comma
            line = line.substr(line.find(",") + 1);;// Remove the extracted value from the line
                switch (i) {
                case 0: song.serial = index; break;
                case 1: song.track_id = item; break;
                case 2: song.artist = item; break;
                case 3: song.album_name = item; break;
                case 4: song.track_name = item; break;
                case 5: song.popularity = item; break;
                case 6: song.duration_ms = item; break;
                case 7: song.explicit_content = item; break;
                case 8: song.danceability = item; break;
                case 9: song.energy = item; break;
                case 10: song.key = item; break;
                case 11: song.loudness = item; break;
                case 12: song.mode = item; break;
                case 13: song.speechiness = item; break;
                case 14: song.acousticness = item; break;
                case 15: song.instrumentalness = item; break;
                case 16: song.liveness = item; break;
                case 17: song.valence = item; break;
                case 18: song.tempo = item; break;
                case 19: song.time_signature = item; break;
                case 20: song.genre = item; break;
                default: break;
            }


        }
            // song.serial = songList.size() + 1; // Assign a serial number
        //cout << index << endl;
            songList[index] = song;
        index++;
    }
    //cout << "Successfully loaded " << songList.length() << " songs." << endl;
    for (int i = 0; i < 3; i++)
    {
        printSongColumns(songList[i]);
        cout << endl;
    }



    return 0;
}
