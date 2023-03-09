//
//  main.cpp
//  TrieNode
//
//  Created by Chen Wei-Chen on 2023/3/9.
//

#include <iostream>
#include <string>
using namespace std;

class TrieNode {
    TrieNode* children[26];
    bool isEnd = false;
    
    TrieNode() {
        memset(children,0,sizeof(children));
    }
    
    void add_word(string& word) {
        TrieNode* cur = this;
        for (auto c: word) {
            if (!cur->children[c-'a']) cur->children[c-'a'] = new TrieNode();
            cur = cur->children[c-'a'];
        }
        cur->isEnd = true;
    }
    
    bool has_word(string& word) {
        TrieNode* cur = this;
        for (auto c: word) {
            if (!cur->children[c-'a']) return false;
            cur = cur->children[c-'a'];
        }
        return cur->isEnd;
    }
};

