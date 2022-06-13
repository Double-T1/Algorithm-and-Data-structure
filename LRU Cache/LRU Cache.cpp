class LRUCache {
private:   
    typedef list<int> LI; // key
    typedef unordered_map<int,pair<int,LI::iterator>> hashmap; //key: [value,it]
    
    LI li;
    int _capacity;
    hashmap cache;
    
    void touch(hashmap::iterator& it) {
        auto key = it->first;
        li.erase(it->second.second);
        li.push_front(key);
        cache[key] = make_pair(it->second.first,li.begin());
    }
    
public:
    LRUCache(int capacity): _capacity(capacity) {
    }
    
    int get(int key) {
        auto it = cache.find(key);
        if (it == cache.end()) return -1;
        touch(it);

        return it->second.first;
    }
    
    void put(int key, int value) {
        auto it = cache.find(key);
        if (it == cache.end()) {
            if (_capacity == li.size()) {
                cache.erase(li.back());
                li.pop_back();
            }   
            li.push_front(key);
        } else {
            touch(it);
        }
        cache[key] = {value,li.begin()};
    }
};
