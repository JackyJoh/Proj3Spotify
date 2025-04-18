//
// Created by joeyp on 4/17/2025.
//

#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include "backend.h"
#include "rapidcsv.h"
#include <cmath>

using namespace std;

class minHeap {
    vector<pair<Song*, float>> songs;
    public:
        minHeap(int n) {
            songs.resize(n);
        }
        pair<Song*, float> extract() {
            return songs[0];
        }
        void heapifyDown(pair<Song*, float>& song, int ind) {
            if (2*ind + 1 >= songs.size() ) {
                return;
            }
            if (2*ind + 2 >= songs.size()) {
                if (songs[ind].second > songs[2*ind + 1].second) {
                    pair<Song*, float> temp = songs[ind];
                    songs[ind] = songs[2*ind + 1];
                    songs[2*ind + 1] = temp;
                    heapifyDown(songs[2*ind + 1], 2*ind + 1);
                }
                return;
            }
            if (songs[ind].second < songs[2*ind + 1].second && songs[ind].second < songs[2*ind + 2].second) {
                return;
            }
            if (songs[2*ind + 1].second < songs[2*ind + 2].second) {
                pair<Song*, float> temp = songs[ind];
                songs[ind] = songs[2*ind + 1];
                songs[2*ind + 1] = temp;
                heapifyDown(songs[2*ind + 1], 2*ind + 1);
            } else {
                pair<Song*, float> temp = songs[ind];
                songs[ind] = songs[2*ind + 2];
                songs[2*ind + 2] = temp;
                heapifyDown(songs[2*ind + 2], 2*ind + 2);
            }
        }
        void insertInit(pair<Song*, float> p, int ind) {
            songs[ind] = p;
        }
        void insert(pair<Song*, float> p) {
            songs[0] = p;
            heapifyDown(songs[0], 0);
        }
        vector<pair<Song*, float>> getSongs() {
            return songs;
        }
};

// float getScore(Song* ref, Song* comp) {
//     float score = 0;
//     if (ref->artist == comp->artist) {
//         if (ref->album_name == comp->album_name) {
//             score += 0.3;
//         } else {
//             score += 0.2;
//         }
//     }
//     if (comp->loudness/ref->loudness >= 0.9 && comp->loudness/ref->loudness <= 1.1) {
//         score += 0.1;
//     } else if (comp->loudness/ref->loudness >= 0.8 && comp->loudness/ref->loudness <= 1.2) {
//         score += 0.05;
//     }
//     if (comp->genre == ref->genre) {
//         score += 0.1;
//     }
//     if (comp->tempo/ref->tempo >= 0.9 && comp->tempo/ref->tempo <= 1.1) {
//         score += 0.15;
//     } else if (comp->tempo/ref->tempo >= 0.8 && comp->tempo/ref->tempo <= 1.2) {
//         score += 0.05;
//     }
//     if (comp->mode == ref->mode) {
//         if (comp->mode == 1) {
//             score += 0.15;
//         } else {
//             score += 0.05;
//         }
//     }
//     if (comp->time_signature == ref->time_signature) {
//         score += 0.1;
//     }
//     if (comp->liveness/ref->liveness >= 0.9 && comp->liveness/ref->liveness <= 1.1) {
//         score += 0.1;
//     }
//     return score;
// }
// Added artist and album boosts
float getScore(Song* ref, Song* comp) {
    float score = 0;
    float albumBoost=1;
    float artistBoost=1;
    // Artist and album matching (0.25 total)
    if (ref->artist == comp->artist) {
        score += 0.12;
        albumBoost = 1.05;
        if (ref->album_name == comp->album_name) {
            score += 0.10;
            albumBoost = 1.05;
        }
    }

    // Genre matching (0.20)
    if (comp->genre == ref->genre) {
        score += 0.20;
    }

    // Tempo difference (0.15)
    float tempoDiff = abs(1 - (comp->tempo / ref->tempo));
    score += (0.15f * (1 - tempoDiff));

    // Loudness difference (0.10)
    float loudnessDiff = abs(1 - (comp->loudness / ref->loudness));
    score += (0.10f * (1 - loudnessDiff));

    // Mode and time signature (0.10 total)
    if (comp->mode == ref->mode) {
        score += 0.05;
    }
    if (comp->time_signature == ref->time_signature) {
        score += 0.05;
    }

    // Liveness and energy differences (0.20 total)
    float livenessDiff = abs(1 - (comp->liveness / ref->liveness));
    score += (0.10f * (1 - livenessDiff));

    float energyDiff = abs(1 - (comp->energy / ref->energy));
    score += (0.10f * (1 - energyDiff));

    return score * albumBoost * artistBoost; // Total possible score = 1.0
}

vector<pair<Song*, float>> mostSimilar(Song* ref, vector<Song*>& allS) {
    minHeap mh(7);
    for (int i = 0; i < 7; i++) {
        pair<Song*, float> p(allS[i], getScore(ref, allS[i]));
        mh.insertInit(p, i);
    }
    for (int i = 7; i < allS.size(); i++) {
        pair<Song*, float> p(allS[i], getScore(ref, allS[i]));
        if (p.second > mh.extract().second && p.first != ref) {
            mh.insert(p);
        }
    }
    return mh.getSongs();
}

#endif //ALGORITHMS_H
