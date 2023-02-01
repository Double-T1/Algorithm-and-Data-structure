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
using namespace std;


class SegmentTree {
private:
    vector<int> segment;
    int originalEnd;

public:
    template <typename T>
    SegmentTree(T& a) {
        int size = 1, n = a.size();
        originalEnd = n-1;
        while (size < 2*n)
            size <<= 1;
        
        segment.resize(size,0);
    }

    void update_point(int val, int i) { return update_range(val,i,i,0,0,originalEnd); }
    void update_range(int val, int left, int right) { return update_range(val,left,right,0,0,originalEnd); }
    void update_range(int val, int left, int right, int pos, int sLeft, int sRight) {
        if (left > sRight || right < sLeft) return;

        //without lazy propogation
        if (sLeft == sRight) {
            segment[pos] = compare(segment[pos],val);
            return
        }
        // with lazy propogation
        // if (left <= sLeft && sRight <= right) {
        //     segment[pos] = compare(segment[pos],val);
        //     return;
        // } 

        int leftTree = 2*pos+1, rightTree = 2*pos+2, mid = sLeft + (sRight-sLeft)/2;
        update_range(val,left,right,leftTree,sLeft,mid);
        update_range(val,left,right,rightTree,mid+1,sRight);
        merge(pos);
    }

    int query_point(int index) {return query_range(index,index); }
    int query_range(int left, int right, int pos=0, int sLeft=0, int sRight=originalEnd) {
        if (left > sRight || sLeft > right) return -1;

        if (left <= sLeft && sRight <= right) {
            return segment[pos];
        }

        int leftTree = 2*pos+1, rightTree = 2*pos+2, mid = sLeft + (sRight-sLeft)/2;
        return compare(query_range(left,right,leftTree,sLeft,mid),query_range(left,right,rightTree,mid+1,sRight));
    }

private:
    virtual void merge() {
        //do someting 
    }
}