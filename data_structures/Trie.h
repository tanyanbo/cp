//
// Created by tanya on 2022/1/8.
//

#ifndef ALGO_TRIE_H
#define ALGO_TRIE_H
#include <string>
#include <unordered_map>

using namespace std;

class TrieNode {
    char letter;
public:
    bool isTerminal;
    unordered_map<char, TrieNode*> m;
    TrieNode(char l);
};

class Trie {
public:
    TrieNode* root;
    Trie();
    void insert(string word);
    bool search(string word);
    bool startsWith(string word);
};

#endif //ALGO_TRIE_H
