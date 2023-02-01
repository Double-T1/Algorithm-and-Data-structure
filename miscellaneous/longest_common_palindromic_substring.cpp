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

//return the length of the longest common palindromic substring
//navie approach: O(n^3)
//dp with suffix array: O(n^2)
//manacher + segment tree + suffix array: O(nlogn) <= the one implemented here
//we need lcp, suffix array, segment tree that updates the range for elements in two strings, manacher

void count_sort(vector<int>& rank, vector<int>& suf, int r) {
    int count[r], n = suf.size();
    memset(count,0,sizeof(count));
    vector<int> new_suf(n);
    for (auto x: suf) {
        count[rank[x]]++;
    }

    for (int i=1; i<r; ++i) {
        count[i] += count[i-1];
    }

    for (int i=n-1; i>=0; --i) {
        new_suf[--count[rank[suf[i]]]] = suf[i];
    }
    swap(new_suf,suf);
}

void build_suf(vector<int>& suf, vector<int>& rank, string& s) {
    int count[256], n = s.size();
    memset(count,0,sizeof(count));
    for (auto c: s) {
        count[c]++;
    }

    for (int i=1; i<256; ++i) {
        count[i] += count[i-1];
    }

    for (int i=0; i<n; ++i) {
        suf[--count[i]] = i;
    }

    int r = 1;
    rank[suf[0]] = 0;
    for (int i=1; i<n; ++i) {
        r += suf[i] != suf[i-1];
        rank[suf[i]] = r-1;
    }

    for (int k=1; k<n; k <<= 1) {
        for (auto& x: suf) {
            x = (x-k+n)%n;
        }
        count_sort(rank,suf,r);

        vector<int> new_rank(n,0);
        r = 1;
        new_rank[suf[0]] = 0;
        array<int,2> prev = {rank[suf[0]], rank[(suf[0]+k)%n]};
        for (int i=1; i<n; ++i) {
            array<int,2> cur = {rank[suf[i]], rank[(suf[i] + k)%n]};
            r += prev != cur;
            new_rank[suf[i]] = r-1;
            swap(prev,cur);
        }
        swap(new_rank,rank);
    } 
}

void build_lcp(vector<int>& lcp, vector<int>& suf, string& s) {
    s += ' ';
    int n = s.size();
    suf.resize(n,0);
    vector<int> rank(n,0);
    build_suf(suf,rank,s);

    lcp.resize(n-1);
    int k = 0;
    for (int i=0; i<n-1; ++i) {
        int si = rank[i];
        int j = suf[si-1];

        while (s[i+k] == s[j+k]) ++k;
        lcp[si-1] = k;
        k = max(0,k-1);
    }
    s.pop_back();
}

//range leftmost or rightmost query
class SegmentTree {
private:
    vector<int> segment;
    int originalEnd;
    bool toLeft;

public:
    template <typename T>
    SegmentTree(T& a, bool toLeft): toLeft(toLeft) {
        int size = 1, n = a.size();
        originalEnd = n-1;
        while (size < 2*n)
            size <<= 1;
        
        segment.resize(size,0);
    }

    void update_range(int val, int left, int right) { return update_range(val,left,right,0,0,originalEnd); }
    void update_range(int val, int left, int right, int pos, int sLeft, int sRight) {
        if (left > sRight || right < sLeft) return;

        //without lazy propogation
        if (sLeft == sRight) {
            segment[pos] = compare(segment[pos],val);
            return;
        }
        // with lazy propogation
        // if (left <= sLeft && sRight <= right) {
        //     segment[pos] = compare(segment[pos],val);
        //     return;
        // } 

        int leftTree = 2*pos+1, rightTree = 2*pos+2, mid = sLeft + (sRight-sLeft)/2;
        update_range(val,left,right,leftTree,sLeft,mid);
        update_range(val,left,right,rightTree,mid+1,sRight);
        segment[pos] = compare(segment[leftTree],segment[rightTree]);
    }

    int query_point(int index) {return query_range(index,index); }
    int query_range(int left, int right) { return query_range(left,right,0,0,originalEnd); }
    int query_range(int left, int right, int pos, int sLeft, int sRight) {
        if (left > sRight || sLeft > right) return -1;

        if (left <= sLeft && sRight <= right) {
            return segment[pos];
        }

        int leftTree = 2*pos+1, rightTree = 2*pos+2, mid = sLeft + (sRight-sLeft)/2;
        return compare(query_range(left,right,leftTree,sLeft,mid),query_range(left,right,rightTree,mid+1,sRight));
    }

private:
    int compare(int a, int b) {
        if (a == -1 || b == -1) return a == -1 ? b : a;
        return toLeft ? min(a,b) : max(a,b);
    }
};

//manacher's
//the longest radius for each element
void build_mana(vector<int>& mana, string& s) {
    int n = s.size(), m = 2*n+3;
    mana.resize(n,1);
    char arr[m];
    memset(arr,0,sizeof(arr));
    arr[0] = '@';
    arr[m-1] = '&';
    int i=0;
    for (auto c: s) {
        arr[++i] = '#';
        arr[++i] = c;
    }
    arr[++i] = '#';

    int center = 0, right = 0;
    int rad[m];
    memset(rad,0,sizeof(rad));
    for (int i=1; i<m-1; ++i) {
        if (i < right) 
            rad[i] = min(right-i,rad[2*center-i]);

        while (s[rad[i]+i+1] == s[i-rad[i]-1])
            ++rad[i];

        if (i+rad[i] > right) {
            center = i;
            right = i+rad[i];
        }

        if (i%2 == 0) {
            mana[i/2-1] = rad[i];
        }
    }
}


/**
 
 */


int main() {
    string a = "ababcdcba", b = "cacdcaba";
    string c = a + '$' + b;
    vector<int> lcp, suf;
    build_lcp(lcp,suf,c);

    SegmentTree *toLeftA = new SegmentTree(a,true), *toLeftB = new SegmentTree(b,true);
    SegmentTree *toRightA = new SegmentTree(a,false), *toRightB = new SegmentTree(b,false);

    auto update = [](int cur, int len, SegmentTree* toLeft, SegmentTree* toRight){ 
        int mid = cur + len/2, right = cur+len-1;
        toLeft->update_range(cur,cur,mid);
        toRight->update_range(right,mid+1,right);
    }

    int m = a.size(), n = suf.size();
    for (int i=3; i<n; ++i) {
        int cur = suf[i];
        int prev = suf[i-1];
        if ((cur < m)^(prev >= m)) continue; //one of the conidition satisfy and the other doesn't

        if (cur >= m) swap(cur,prev);
        int len = lcp[i-1];
        update(cur,len,toLeftA,toRightA);
        update(prev,len,toLeftB,toRightB);
    }

    vector<int> lpsA, lpsB; //longest palindromic substring
    build_mana(lpsA,a), build_mana(lpsB,b);

    auto traverse = [](vector<int>& lps, string& s, SegmentTree* toLeft, SegmentTree* toRight){   
        int ans = 0;
        for (int i=0; i<s.size(); ++i) {
            int left = toLeft->query_point(i), right = toRight->query_point(i);
            int rad = max(right-i+1,i-left+1);
            ans = max(ans,min(rad,lps[i]));
        }
        return ans;
    }
    
    return max(traverse(lpsA,a,toLeftA,toRightA),traverse(lpsB,b,toLeftB,toRightB));
}


/**
 from Quora:
 
 O(N^2) Algorithm:

 First using DP we can easily find what is the longest palindromic sub-string in each sub-string starting from position 'i' and ending at position 'j' for all (1 <= i <= j <= n) in string A and store it in a 2D array dp[i][j] in O(N^2) time like this,
 First we define another 2D array pos[][] where pos[i][j] stores a bool value if the sub-string A[i....j] is a palindrome, this array can be recursively calculated as pos[i][j] = (A[i] == A[j]) && (pos[i+1][j-1]).
 Second we define the recursive relation to calculate dp[i][j] as
 if pos[i][j] == true : then dp[i][j] = j - i + 1,
 else : dp[i][j] = max(dp[i + 1][j], dp[i][j - 1]).
 This is because if A[i....j] is palindrome then it will be the longest palindromic substring of A[i....j] else we take the maximum of the dp[i+1][j], dp[i][j-1] because the longest palindromic sub-string of A[i....j] now could only contain either A[i] or A[j] but not both.

 Now we make a new string C = A + "$" + B (here '+' represent concatenation of strings), and calculate the suffix array for it in O(N logN) and calculate the LCP array (longest common prefixes for each adjacent suffix) in O(N).

 In the string C, the indices of the characters of string A lie in the range (0 to N - 1), Nth character will be '$' and indices characters of B lie in the range (N + 1, N + N). Now if we consider suffix starting from an index less than N (say 'i') and another suffix which starts from index greater than N (say 'j') the LCP of these two suffixes will not be more than max(N-i+1, N+N-j+1), in simple terms the longest common prefix of these two suffixes doesn't include the '$' character.

 Now all we need to do is for each pair of adjacent suffixes in the sorted suffix array if one is less than N (say i') and other is greater than N (say 'j') and let the LCP be 'k', then the respective sub-string we need to consider in string A will be P = "A[i]A[i + 1]....A[i+k-1]" and the respective sub-tring in B will be Q = "B[j]B[j + 1]....B[j+k-1]". As P == Q here, we just update the answer with max(current answer, dp[i][i + k -1]).

 The total complexity is O(N^2) = O(N^2) for dp + O(NlogN) for suffix sort + O(N) for lcp respectively. Here the slowest part is the DP part of O(N^2). So if we can improve this to something faster then we can improve the whole solution.

 O(N logN) Algorithm :

 Now after creating the suffix array and finding LCP, all we got is some ranges (i, i+k-1) and asked us to find what is the longest palindromic sub-string in this range, i.e, simply for each index 'j' (i <= j <= i+k-1) we need to find the longest palindromic sub-string centered at 'j' and which can start after 'i' and end before 'i'+'k'-1. We might have maximum of 2*N such queries. I am only considering odd length palindromes in this solution, even length can also be found by making simple modifications.

 Here what we can do is for every index 'j' we can store the right most index at which the palindrome can end and the left most index at which the palindrome can start if the center is at 'j'. Now in each query, we can see that only the starting points will change for j such that (i <= j < i+k/2) and ending points will change for j such that (i+k/2 <= j < i+k). So we need to update the starting and ending points for respective 'j's'. This can be done using segment tree in O(logN) per each query.

 Now we have for each center 'j' the left most starting and right most ending points, and we can find the longest palindromic sub-string centered at each position in O(N) using Manacher's Algorithm.

 So our final answer can be calculated by calculating the largest palindromic sub-string centered at each 'j' which can be possible, i.e, by considering the left most starting points and right most ending points.







*/
