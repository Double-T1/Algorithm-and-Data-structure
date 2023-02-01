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
//#include <bits/std++.h>
typedef long long ll;
using namespace std;

void count_sort(vector<int>& suf, vector<int>& rank, int r) {
    int n = suf.size(), count[r];
    vector<int> new_suf(n);
    memset(count,0,sizeof(count));
    for (auto x: rank) {
        count[x]++;
    }

    for (int i=1; i<r; ++i) {
        count[i] += count[i-1];
    }

    for (int i=n-1; i>=0; --i) {
        new_suf[--count[rank[suf[i]]]] = suf[i];
    }
    swap(new_suf,suf);
}

void build_suffix(vector<int>& suf, vector<int>& rank, string & s) {
    int n = s.size();
    rank.resize(n,0);
    suf.resize(n,0);
    
    int x = max(256,n),count[x];
    memset(count,0,sizeof(count));
    for (auto c: s) {
        count[c]++;
    }

    for (int i=1; i<x; ++i) {
        count[i] += count[i-1];
    }

    for (int i=0; i<n; ++i) {
        suf[--count[s[i]]] = i;
    }

    int r=1; //class
    rank[suf[0]] = 0;
    for (int i=1; i<n; ++i) {
        r += s[suf[i]] != s[suf[i-1]];
        rank[suf[i]] = r-1;
    }
    
    for (int k=1; k<n; k <<=1) {
        for (int i=0; i<n; ++i) {
            suf[i] = (suf[i] - k + n)%n;
        }
        count_sort(suf,rank,r);
        
        r = 1;
        rank[suf[0]] = 0;
        vector<int> new_rank(n);
        array<int,2> prev = {rank[suf[0]],rank[(suf[0] + k)%n]};
        for (int i=1; i<n; ++i) {
            array<int,2> cur = {rank[suf[i]], rank[(suf[i] + k)%n]};
            r += prev != cur;
            new_rank[suf[i]] = r-1;
            swap(prev,cur);
        } 
        swap(new_rank,rank);
    }
}

void build_lcp(string& s, vector<int>& lcp, vector<int>& suf) {
    s += '#';
    vector<int> rank;
    build_suffix(suf,rank,s);
    
    int n = s.size(), k = 0;
    lcp.resize(n-1);
    for (int i=0; i<n-1; ++i) { 
        int si = rank[i];
        //if (si == 0) continue;
        int j = suf[si-1];

        while (s[i+k] == s[j+k]) k++;
        lcp[si-1] = k;
        k = max(0,k-1);
    }
    s.pop_back();
}