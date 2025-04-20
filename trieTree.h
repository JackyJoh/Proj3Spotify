//
// Created by allan on 4/18/2025.
//

#ifndef TRIETREE_H
#define TRIETREE_H

#endif //TRIETREE_H

#include <iostream>
#include <cctype>
#include <set>
#include <string>
#include <unordered_map>

class TrieNode {
public:
    std::unordered_map<char, TrieNode*> children;
    bool isEndOfWord;
    int index;

    TrieNode() : isEndOfWord(false) {}
};

class Trie {
public:
    TrieNode* root;
    unordered_set<char> alphabet = {' ','a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z','0','1','2','3','4','5','6','7','8','9'};

    Trie() : root(new TrieNode()) {}

    void insert(const std::string& word, int vectorIndex) {
        TrieNode* current = root;
        for (char ch : word) {
            ch = tolower(ch);
            if (alphabet.count(ch) == 0)
            {
                continue;
            }
            if (current->children.find(ch) == current->children.end()) {
                current->children[ch] = new TrieNode();
            }
            current = current->children[ch];
        }
        if(current == root)
        {
            return;
        }
        current->isEndOfWord = true;
        current->index = vectorIndex;
    }

    int search(const std::string& word) {
        TrieNode* current = root;
        for (char ch : word) {
            if (alphabet.count(ch) == 0)
            {
                continue;
            }
            if (current->children.find(ch) == current->children.end()) {
                break;
            }
            current = current->children[ch];
        }
        if (current->isEndOfWord)
        {
            return current->index;
        }
        if(current == root)
        {
            return 51216;
        }
        while(!current->isEndOfWord)
        {
            for(char c : alphabet)
            {
                if(!(current->children.find(c) == current->children.end()))
                {
                    current = current->children[c];
                    break;
                }
            }
        }
        return current->index;
    }
};