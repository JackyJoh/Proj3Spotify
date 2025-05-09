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
    float maxScore = 1.0;
    float artistWeight = 0.2;
    float albumWeight = 0.1;
    float loudnessWeight = 0.05;
    float genreWeight = 0.2;
    float tempoWeight = 0.1;
    float modeWeight = 0.05;
    float timeSignatureWeight = 0.05;
    float explicitWeight = 0.05;
    float valenceWeight = 0.05;
    float energyWeight = 0.1;
    float danceabilityWeight = 0.05;

    // Artist and album match
    if (ref->artist == comp->artist) {
        score += artistWeight;
        if (ref->album_name == comp->album_name) {
            score += albumWeight;
        }
    }

    //Loudness similarity
    float loudnessDiff = fabs((comp->loudness - ref->loudness) / ref->loudness);
    if (loudnessDiff <= 0.1) {
        score += loudnessWeight * (1 - loudnessDiff);
    }

    // Genre match
    if (comp->genre == ref->genre) {
        score += genreWeight;
    }

    //Tempo similarity
    float tempoDiff = fabs((comp->tempo - ref->tempo) / ref->tempo);
    if (tempoDiff <= 0.2) {
        score += tempoWeight * (1 - tempoDiff);
    }

    //Mode match
    if (comp->mode == ref->mode && comp->mode == 0) {
        score += modeWeight;
    }

    //Time signature match
    if (comp->time_signature == ref->time_signature) {
        score += timeSignatureWeight;
    }

    //Explicit content match
    if (comp->explicit_content == ref->explicit_content) {
        score += explicitWeight;
    }

    //Valence similarity
    float valenceDiff = fabs((comp->valence - ref->valence) / ref->valence);
    if (valenceDiff <= 0.1) {
        score += valenceWeight * (1 - valenceDiff);
    }

    //Energy similarity
    float energyDiff = fabs((comp->energy - ref->energy) / ref->energy);
    if (energyDiff <= 0.1) {
        score += energyWeight * (1 - energyDiff);
    }

    //Danceability similarity
    float danceabilityDiff = fabs((comp->danceability - ref->danceability) / ref->danceability);
    if (danceabilityDiff <= 0.1) {
        score += danceabilityWeight * (1 - danceabilityDiff);
    }

    return score * 100;
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

void merge(vector<pair<Song*, float>>& songs, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    vector<pair<Song*, float>> L(n1);
    vector<pair<Song*, float>> R(n2);
    for (int i = 0; i < n1; i++) {
        L[i] = songs[left + i];
    }
    for (int i = 0; i < n2; i++) {
        R[i] = songs[mid + 1 + i];
    }
    int i = 0;
    int j = 0;
    int k = left;
    while (i < n1 && j < n2) {
        if (L[i].second >= R[j].second) {
            songs[k] = L[i];
            i++;
        } else {
            songs[k] = R[j];
            j++;
        }
        k++;
    }
    while (i < n1) {
        songs[k] = L[i];
        i++;
        k++;
    }
    while (j < n2) {
        songs[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(vector<pair<Song*, float>>& songs, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(songs, left, mid);
        mergeSort(songs, mid + 1, right);
        merge(songs, left, mid, right);
    }
}

vector<pair<Song*, float>> mostSimilarMerge(Song* ref, vector<Song*>& allS) {
    vector<pair<Song*, float>> allSongs;
    unordered_set<string> seen;
    for (int i = 0; i < allS.size(); i++) {
        if (seen.count(allS[i]->track_name) == 0 && ref->track_name != allS[i]->track_name) {
            pair<Song*, float> p(allS[i], getScore(ref, allS[i]));
            allSongs.push_back(p);
            seen.insert(allS[i]->track_name);
        }
    }
    mergeSort(allSongs, 0, allSongs.size() - 1);
    vector<pair<Song*, float>> topSeven(7);
    for (int i = 6; i >= 0; i--) {
        topSeven[6 - i] = allSongs[i];
    }
    return topSeven;
}
#endif //ALGORITHMS_H.,l