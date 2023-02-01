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

void build_mana(string& s) {
    int n = s.size(), m = 2*n+3;
    char t[m];
    t[0] = '&';
    t[m-1] = '$';
    int i = 0;
    for (auto c: s) {
        t[++i] = '#';
        t[++i] = c;
    }
    t[++i] = '#';

    int start = 0;
    int center = 0;
    int right = 0;
    int maxLen = 0;
    int rad[m];
    memset(rad,0,sizeof(rad)); 
    for (int i=1; i<m-1; ++i) {
        if (i < right) {
            rad[i] = min(rad[2*center-i], right-i);
        }

        while (t[i + rad[i] + 1] == t[i - rad[i] - 1]) {
            rad[i]++;
        }

        if (i + rad[i] > right) {
            right = i + rad[i];
            center = i;
        }

        if (rad[i] > maxLen) {
            start = (i - rad[i] - 1)/2;
            maxLen = rad[i];
        }
    }
}