#include <iostream>
#include <algorithm>
#include <functional>
#include <vector>
#include <string>
#include <string.h>
#include <string_view>
#include <unordered_set>
#include <unordered_map>
#include <set>
#include <map>
#include <queue>
#include <array>
#include <stack>
#include <numeric>
#include <random> 
#include <stdio.h>
#include <bitset>
#include <ctype.h>
#include <chrono>
//#include <bits/std++.h>

using namespace std;

typedef long long ll;
typedef long double ld;
typedef std::vector<int> vi;
typedef std::vector<bool> vb;
typedef std::vector<string> vs;
typedef std::vector<double> vd;
typedef std::vector<long long> vll;
typedef std::vector<std::vector<int> > vvi;
typedef vector<vll> vvll;
typedef std::vector<std::pair<int, int> > vpi;
typedef vector<vpi> vvpi;
typedef std::pair<int, int> pi;
typedef std::pair<ll, ll> pll;
typedef std::vector<pll> vpll;
typedef vector<vvi> vvvi;
typedef vector<vvvi> vvvvi;
 
const long long mod = 1000000007;
ll gcd (ll a, ll b) {return b==0 ? a : gcd(b, a%b);}
const unsigned gen_seed = std::chrono::system_clock::now().time_since_epoch().count();
std::mt19937_64 gen(gen_seed);

#define fastio ios_base::sync_with_stdio(false);\
            cin.tie(NULL);\
            cout.tie(NULL)
#define mem(x) memset(x,0,sizoef(x))
#define all(c) (c).begin(),(c).end()
#define read(x) scanf("%d", &x)
#define readv(x, n) vi x(n); forn(i,0,n) scanf("%d", &x[i])
 
#define pb push_back
#define mp make_pair

//for range minimum query
//build: O(nlogn)
//query: O(1)
//table[start][k]:= get the minimum element in [start:start+2^k)
//k being 0,1,2,3 => 1,2,4,8.....
//build in nlogn => dp
//table[start][k] == min(table[start][k-1],table[start+2^(k-1)][k-1])


vector<int> get_lg(int n) {
    vector<int> lg(n,0);
    for (int i=2; i<=n; ++i)
        lg[i] = lg[i/2]+1;
    return lg;
}

vector<vector<int>> build_sparse(int arr[], int n, vector<int>& lg) {
    int K = lg[n];
    vector<vector<int>> spt(n,vector<int>(K+1));
    for (int start=0; start<n; ++start) 
        spt[start][0] = arr[start];

    for(int k = 1, k2=1; k <= K; k2<<=1, k++) {
		for(int i = 0; i + k2< n; i++) {
			spt[i][k] = min(spt[i][k-1], spt[i+k2][k-1]);
		}
	}
    return spt;
}

int query_min(vector<int>& lg, int l, int r, vector<vector<int>>& spt) {
    int k = lg[r-l+1];
    return min(spt[l][k],spt[r-(1<<k)+1][k]);
}

class sparseTable {
private:
    vector<vector<int>> spt;
    vector<int> lg;
    int n;

public:
    sparseTable(vector<int>& arr) {
        n = arr.size();
        spt = vector<vector<int>> (n,vector<int>(get_lg()+1));
        
        int K = lg[n];
        for (int i=0; i<n; ++i) 
            spt[i][0] = arr[i];
        
        for (int k=1, k2=1; k<=K; k2<<=1, ++k) {
            for (int i=0; i+k2<n; ++i) {
                spt[i][k] = min(spt[i][k-1],spt[i+k2][k-1]);
            }
        }
    }

    int query_min(int l, int r) {
        int k = lg[r-l+1];
        return min(spt[l][k],spt[r-(1<<k)+1][k]);
    }

private:
    int get_lg() {
        lg.resize(n+1);
        lg[1] = 0;
        for (int i=2; i<=n; ++i)
            lg[i] = lg[i/2]+1;
        return lg[n];
    }
};



int main() {
    fastio;


    
}
