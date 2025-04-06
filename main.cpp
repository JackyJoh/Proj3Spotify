#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include <vector>


using namespace std;

struct Song {
    string serial;
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
    Song(string serial, string track_id, string artist, string album_name, string track_name,
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
        : serial(""), track_id(""), artist(""), album_name(""), track_name(""),
          popularity(""), duration_ms(""), explicit_content(""), danceability(""),
          energy(""), key(""), loudness(""), mode(""), speechiness(""),
          acousticness(""), instrumentalness(""), liveness(""), valence(""),tempo(""), time_signature(""), genre("") {}
    void printSongColumns() {
        cout << "Song Data Structure Columns:" << endl;
        cout << "1. serial - Unique identifier for each song" << endl;
        cout << "2. track_id - Spotify track ID" << endl;
        cout << "3. artist - Artist name" << endl;
        cout << "4. album_name - Album title" << endl;
        cout << "5. track_name - Song title" << endl;
        cout << "6. popularity - Song popularity rating" << endl;
        cout << "7. duration_ms - Song duration in milliseconds" << endl;
        cout << "8. explicit_content - Whether song has explicit content" << endl;
        cout << "9. danceability - Measure of suitability for dancing" << endl;
        cout << "10. energy - Measure of intensity and activity" << endl;
        cout << "11. key - Musical key of the track" << endl;
        cout << "12. loudness - Overall loudness in decibels" << endl;
        cout << "13. mode - Major (1) or Minor (0) modality" << endl;
        cout << "14. speechiness - Presence of spoken words" << endl;
        cout << "15. acousticness - Amount of acoustic sound" << endl;
        cout << "16. instrumentalness - Amount of instrumental content" << endl;
        cout << "17. liveness - Presence of live audience" << endl;
        cout << "18. valence - Musical positiveness" << endl;
        cout << "19. tempo - Speed of the track in BPM" << endl;
        cout << "20. time_signature - Time signature of the track" << endl;
        cout << "21. genre - Musical genre" << endl;
    }
};



int main()
{
    vector<Song> songList;
    string line;
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
            line = line.substr(line.find(",") + 1);      // Remove the extracted value from the line
                switch (i) {
                case 0: song.track_id = item; break;
                case 1: song.artist = item; break;
                case 2: song.album_name = item; break;
                case 3: song.track_name = item; break;
                case 4: song.popularity = item; break;
                case 5: song.duration_ms = item; break;
                case 6: song.explicit_content = item; break;
                case 7: song.danceability = item; break;
                case 8: song.energy = item; break;
                case 9: song.key = item; break;
                case 10: song.loudness = item; break;
                case 11: song.mode = item; break;
                case 12: song.speechiness = item; break;
                case 13: song.acousticness = item; break;
                case 14: song.instrumentalness = item; break;
                case 15: song.liveness = item; break;
                case 16: song.valence = item; break;
                case 17: song.tempo = item; break;
                case 18: song.time_signature = item; break;
                case 19: song.genre = item; break;
                default: break;
            }


        }
            song.serial = songList.size() + 1; // Assign a serial number
            songList.push_back(song);
    }
    cout << "Successfully loaded " << songList.size() << " songs." << endl;
    songList[0].printSongColumns();


    return 0;
}
