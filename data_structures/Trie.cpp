//
// Created by tanya on 2022/1/8.
//

#include "Trie.h"

TrieNode::TrieNode(char l)
{
    letter = l;
    isTerminal = false;
}

Trie::Trie()
{
    root = new TrieNode('\0');
}

void Trie::insert(string word)
{
    TrieNode* temp = root;
    for (char ch: word) {
        if (temp->m.count(ch)==0) {
            temp->m[ch] = new TrieNode(ch);
        }
        temp = temp->m[ch];
    }
    temp->isTerminal = true;
}

bool Trie::search(string word)
{
    TrieNode* temp{root};
    for (char ch: word) {
        if (!temp->m.count(ch)) {
            return false;
        }
        temp = temp->m[ch];
    }
    return temp->isTerminal;
}

bool Trie::startsWith(string prefix)
{
    TrieNode* temp = root;
    for (const char& ch: prefix) {
        if (!temp->m.count(ch)) return false;
        temp = temp->m[ch];
    }
    return true;
}
