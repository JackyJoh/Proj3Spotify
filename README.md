COP3530 Proj3Spotify

*Launching Project Locally*

Assuming all extensions/apps are installed:
Edit the "Proj3Spotify" run configuration and add the following to "Before Launch" if not already configured:
"Launch Web Browser" with it set to this link: http://localhost:63342/Proj3Spotify/frontEnd/index.html
Also make sure to remove the "build" step in before launch to reduce launch time.
Then to run just press run and it should take you to the local web page and the server should boot, allowing you to easily test the current version.



*Song Struct*

A data structure representing a song with its various attributes from a music dataset.

Members:
- serial: Unique identifier for the song (integer)
- track_id: Spotify's unique identifier for the track (string)
- artist: Name of the song's artist (string)
- album_name: Name of the album containing the song (string)
- track_name: Title of the song (string)
- popularity: Popularity rating of the song (integer)
- duration_ms: Duration of the song in milliseconds (integer)
- explicit_content: Whether the song contains explicit content (boolean)
- danceability: Measure of song's suitability for dancing (double, 0.0-1.0)
- energy: Measure of intensity and activity (double, 0.0-1.0)
- key: Musical key of the track (integer, 0-11)
- loudness: Overall loudness in decibels (double)
- mode: Musical modality, 0 for minor, 1 for major (integer)
- speechiness: Presence of spoken words (double, 0.0-1.0)
- acousticness: Measure of acoustic sound (double, 0.0-1.0)
- instrumentalness: Amount of instrumental content (string)
- liveness: Presence of live audience (double, 0.0-1.0)
- valence: Musical positiveness measure (double, 0.0-1.0)
- tempo: Speed of the track in BPM (double)
- time_signature: Time signature of the track (integer)
- genre: Musical genre classification (string)

*Creating a Song Struct*

//Song song(songs.GetRow<string>(int index)); //creates a song struct from the index+1 row of data (0 indexed csv WITH header)
Ex. //Song song(songs.GetRow<string>(1)); creates a valid Song for the first song in the dataset

*Getting a specific column*

//vector<string> col =  songs.GetColumn<string>(string rowName);
This reads data from a specifc column and stores in vector
Ex. //vector<string> col =  songs.GetColumn<string>("artists"); stores all of the artists name in a vector

*Getting one specific item*

//string item = songs.GetCell<string>(String row, int index); 
Stores the specifc item- can be seen as songs[row][column] (will be a string because it is reading "raw" data)
Ex. //string artist = songs.GetCell<string>("artists", 5);  //Gets the 6th row of the "artists" column






