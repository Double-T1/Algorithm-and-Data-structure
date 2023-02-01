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

void build_z(vector<int>& z, string& s) {
    int left = 0, right = 0, n = s.size();
    for (int i=1; i<n; ++i) {
        if (right<i) {
            left = right = i;
            while (right<n && s[right] == s[right-left]) right++;
            z[i] = right-left;
            right--;
        } else {
            int k = i-left;
            if (z[k] + i <= right) z[i] = z[k];
            else {
                left = i;
                while (right<n && s[right] == s[right-left]) right++;
                z[i] = right-left;
                right--;
            }
        }
    }
}
