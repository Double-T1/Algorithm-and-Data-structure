#include <iostream>
#include <stack>
#include <algorithm>
#include <functional>
#include <vector>
#include <string>
#include <string.h>
#include <string_view>
#include <unordered_set> 
#include <unordered_map>
#include <map>
#include <array>
#include <numeric>
#include <utility>

#include <cstdlib>
#include <ctime>
//#include <bits/std++.h>
typedef long long ll;
using namespace std;

//allows same keys
//the most naive way of implementing
class TreapNode {
public:
    TreapNode* right;
    TreapNode* left;
    int key, priority;
    TreapNode(int k, int p): key(k), priority(p) {}
}

void split (TreapNode* node, int x, TreapNode*& left, TreapNode*& right) {
    if (!node) 
        left = nullptr, right = nullptr;
    else if (node->key <= x) 
        split(node->right,x,node->right,right), left = node;
    else 
        split(node->left,x,left,node->left), right = node;
    return;
}

//assuming all left tree keys <= right tree keys
void merge(TreapNode* node1, TreapNode* node2, TreapNode*& node) {
    if (!node1 || !node2) 
        node = node1 ? node1 : node2;
    else if (node1->priority >= node2->priority)
        merge(node1->right,node2,node1->right), node = node1;
    else 
        merge(node1,node2->left,node->left), node = node2;
    return;
}

void insert(TreapNode*& node, TreapNode* novel) {
    if (!node)
        node = novel;
    else if (node->priority < p) 
        split(node,novel->key,novel->left,novel->right);
    else
        insert(node->priority <= novel->priority ? node->right : node->left, novel);
    return;
}

//assuming all keys are unique
void erase(TreapNode*& node, int key) {
    if (node->key == key) {
        auto temp = node;
        merge(node->left,node->right,node);
        delete temp;
    } else {
        erase(node->key <= key ? node->right : node->left, key);
    }
}

//assuming all elements are unique
TreapNode* unite(TreapNode* node1, TreapNode* node2) {
    if (!node1 || !node2) return node1 ? node1 : node2;
    if (node1->priority < node2->priority) swap(node1,node2);

    TreapNode *left = nullptr, *right = nullptr;
    split(node2,node1->key,left,right);
    node1->left = unite(node1->left,left);
    node1->right = unite(node1->right,right);
    return node1;
}

//counting how many subnodes a node has
int count(TreapNode* node) {
    return node ? node->count : 0;
}

//assuming subnodes are updated already
//we should update after each insert, merge, split, erase....
//could use lazy propagation
void update_count(TreapNode* node) {
    if (node)
        node->count = 1 + count(node->left) + count(node->right);
}

//build in linear time
//assuming a list of sorted keys
TreapNode* build(int *arr) {
    int n = sizeof(arr)/sizeof(int);
    
}
