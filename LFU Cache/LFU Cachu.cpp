class LFUCache {
private:    
    unordered_map<int,pair<int,int>> key2FreqNVal;
    unordered_map<int,list<int>:: iterator> key2Node;
    unordered_map<int,list<int>> freq2List; //list of keys
    int cap;
    int minFreq;
        
public:
    LFUCache(int capacity): cap(capacity), minFreq(0) {
    }
    
    int get(int key) {
        auto it = key2FreqNVal.find(key);
        if (it == key2FreqNVal.end()) return -1;
        
        auto freq = it->second.first;
        //delete it from the current list
        auto& curList = freq2List[freq];
        curList.erase(key2Node[key]);
        
        if (freq2List[freq].empty()) {
            if (freq == minFreq) minFreq++;
            freq2List.erase(freq);
        }
        
        //add to the new list
        it->second.first = ++freq;
        freq2List[freq].push_front(key);
        key2Node[key] = freq2List[freq].begin();
        
        return it->second.second;
    }
    
    void put(int key, int value) {
        auto it = key2FreqNVal.find(key);
        if (it == key2FreqNVal.end()) {
            if (cap == 0) {
                if (freq2List.find(minFreq) == freq2List.end()) return;
                auto& list = freq2List[minFreq];
                auto k = list.back();
                key2Node.erase(k);
                key2FreqNVal.erase(k);
                list.pop_back();
                if (list.empty()) freq2List.erase(minFreq);
                cap++;
            }
            
            freq2List[1].push_front(key);
            key2FreqNVal[key] = make_pair(1,value);
            key2Node[key] = freq2List[1].begin();
            
            cap--;
            minFreq = 1;
        } else {
            it->second.second = value;
            this->get(key);
        }
    }
};

/**
 * Your LFUCache object will be instantiated and called as such:
 * LFUCache* obj = new LFUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */

/*
operations needed
for get:
find if the key exists in chache: O(1)
if yes, update the frequency of the key,value: O(1)
return value

for put:
find if the key exists in the cache: O(1)
if yes, update the frequency and the value of key,value: O(1)
if no, insert a new key,value: O(1)
and delete the least frequently used and least recently used key,value: O(1)
(with capacity)



two layers of linked-list
1. capacity
2. first layer will be the frequnecy reference node
3. second layer will be the acutal nodes, which is linked behind each first layer node. Thus we call second layer nodes the children of first layer nodes
4. each first layer nodes should record its children end node, which are the least recently used node for this frequency layer
5. whenver a node is promoted up to next freq, they are inserted at the front of next layer as the most recently used node for that freq.
6. freq promote starts with: 
    (1) find the next layer, if it doesn't exist, create one
    (2) get the node to be promoted, delink from current position
    (3) insert at the front of the new freq layer
    (4) if the current layer has no nodes any more, we delete the current layer

1. deletion of layers
2. insertion of layers






*/
