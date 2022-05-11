#include <unordered_map>
using namespace std;

template <typename T>
struct TrieNode {
    bool isEnd = false;
    unordered_map<T, TrieNode*> hashmap;
    
    TrieNode() {};
};

template<typename T>
class Trie {
private:
    TrieNode<T>* root = new TrieNode<T>();
    
public:
    Trie() {};
    
    void insert(const T& val) {
        auto node = root;
        for (auto& c : val) {
            if (node->hashmap[c] == nullptr) node->hashmap[c] = new TrieNode<T>();
            node = node->hashmap[c];
        }
        node->isEnd = true;
    }
    
    bool search(const T& val) {
        auto node = root;
        for (auto& c : val) {
            if (node->hashmap[c] == nullptr) return false;
            node = node->hashmap[c];
        }
        return node->isEnd;
    }
};
