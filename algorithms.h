//
// Created by joeyp on 4/17/2025.
//

#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include "backend.h"
#include "rapidcsv.h"
#include <cmath>
#include <unordered_set>

using namespace std;

class minHeap {
    vector<pair<Song*, float>> songs;
    int size;
    public:
        minHeap(int n) {
            songs.resize(n);
            size = n;
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
        void pop() {
            songs[0] = songs[songs.size() - 1];
            songs.erase(songs.begin() + songs.size() - 1);
            size--;
            heapifyDown(songs[0], 0);
        }
        vector<pair<Song*, float>> getSongs() {
            vector<pair<Song*, float>> orderedsongs(size);
            int index = 0;
            while (size > 0) {
                orderedsongs[index] = extract();
                index++;
                pop();
            }
            return orderedsongs;
        }
};

float getScore(Song* ref, Song* comp) {
    float score = 0;
    if (ref->artist == comp->artist) {
        if (ref->album_name == comp->album_name) {
            score += 0.35;
        } else {
            score += 0.25;
        }
    }
    if (fabs(comp->loudness - ref->loudness) < 0.1) {
        score += 0.1;
    }
    if (comp->genre == ref->genre) {
        score += 0.5;
    }
    if (comp->tempo/ref->tempo >= 0.9 && comp->tempo/ref->tempo <= 1.1) {
        score += 0.15;
    } else if (comp->tempo/ref->tempo >= 0.8 && comp->tempo/ref->tempo <= 1.2) {
        score += 0.05;
    }
    if (comp->mode == ref->mode && comp->mode == 0) {
        score += 0.15;
    }
    if (comp->time_signature == ref->time_signature) {
        score += 0.1;
    }
    if (comp->explicit_content == ref->explicit_content) {
        score += 0.05;
    }
    if (comp->valence/ref->valence >= 0.9 && comp->valence/ref->valence <= 1.1) {
        score += 0.1;
    }
    if (comp->energy/ref->energy >= 0.9 && comp->energy/ref->energy <= 1.1) {
        score += 0.15;
    }
    if (fabs(comp->danceability - ref->danceability) <= 0.1) {
        score += 0.05;
    }
    return score;
}

vector<pair<Song*, float>> mostSimilar(Song* ref, vector<Song*>& allS) {
    minHeap mh(7);
    unordered_set<string> seen;
    for (int i = 0; i < 7; i++) {
        if (seen.count(allS[i]->track_name) == 1) {
            continue;
        }
        pair<Song*, float> p(allS[i], getScore(ref, allS[i]));
        mh.insertInit(p, i);
        seen.insert(allS[i]->track_name);
    }
    for (int i = 7; i < allS.size(); i++) {
        if (seen.count(allS[i]->track_name) == 1) {
            continue;
        }
        pair<Song*, float> p(allS[i], getScore(ref, allS[i]));
        if (p.second > mh.extract().second && p.first != ref) {
            mh.insert(p);
        }
        seen.insert(allS[i]->track_name);
    }
    return mh.getSongs();
}

#endif //ALGORITHMS_H
