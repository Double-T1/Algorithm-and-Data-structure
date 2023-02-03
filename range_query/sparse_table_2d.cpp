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

class sparseTable2D {
private:
    vvvvi spt; //spt[i][k][j][t]
    vector<int> lg;
    int n, m;

public:
    sparseTable2D(vvi& arr) {
        n = arr.size(), m = arr[0].size();
        get_lg(max(n,m));
        spt = vvvvi(n,vvvi(lg[n]+1,vvi(m,vi(lg[m]+1,0))));
        
        build(arr);
    }

    int query_max(int x1, int y1, int x2, int y2) {
        int t = lg[y2-y1+1], k = lg[x2-x1+1]; 
        x2 = x2 - (1<<k) + 1;
        y2 = y2 - (1<<t) + 1;
        return max({spt[x1][k][y1][t],spt[x1][k][y2][t],spt[x2][k][y1][t],spt[x2][k][y2][t]});
    }

private:
    void get_lg(int k) {
        lg.resize(k+1);
        lg[1] = 0;
        for (int i=2; i<=k; ++i)
            lg[i] = lg[i/2]+1;
    }

    void build(vvi& arr) { 
        for (int i=0; i<n; ++i) {
            for (int j=0; j<m; ++j) {
                spt[i][0][j][0] = arr[i][j];
            }
        }

        for (int t=1; (1<<t)<=m; ++t) {
            for (int i=0; i<n; ++i) {
                for (int j=0; j<m-(1<<t)+1; ++j) {
                    spt[i][0][j][t] = max(spt[i][0][j][t-1],spt[i][0][j+(1<<(t-1))][t-1]);
                }
            }
        }

        for (int k=1; (1<<k)<=n; ++k) {
            for (int t=0; (1<<t)<= m; ++t) {
                for (int i=0; i<n-(1<<k)+1; ++i) {
                    for (int j=0; j<m-(1<<t)+1; ++j) {
                        spt[i][k][j][t] = max(spt[i][k-1][j][t],spt[i+(1<<(k-1))][k-1][j][t]);
                    }
                }
            }
        }
    }
};

//not bundled into a class 
{
    const int maxSide = 1005; //depends on the question
    const int maxK = 10; //depends on the question
    int spt[maxSide][maxK][maxSide][maxK], n, m;
    int lg[maxSide], arr[maxSide][maxSide];

    void get_lg() {
        lg[1] = 0;
        for (int i=2; i<maxSide; ++i)
            lg[i] = lg[i/2]+1;
    }

    void build(int n, int m) {
        for (int i=0; i<n; ++i) {
            for (int j=0; j<m; ++j) {
                spt[i][0][j][0] = arr[i][j];
            }
        }

        for (int t=1; (1<<t)<=m; ++t) {
            for (int i=0; i<n; ++i) {
                for (int j=0; j<m-(1<<t)+1; ++j) {
                    spt[i][0][j][t] = max(spt[i][0][j][t-1],spt[i][0][j+(1<<(t-1))][t-1]);
                }
            }
        }

        for (int k=1; (1<<k)<=n; ++k) {
            for (int t=0; (1<<t)<= m; ++t) {
                for (int i=0; i<n-(1<<k)+1; ++i) {
                    for (int j=0; j<m-(1<<t)+1; ++j) {
                        spt[i][k][j][t] = max(spt[i][k-1][j][t],spt[i+(1<<(k-1))][k-1][j][t]);
                    }
                }
            }
        }
    }

    int query_max(int x1, int y1, int x2, int y2) {
        int t = lg[y2-y1+1], k = lg[x2-x1+1]; 
        x2 = x2 - (1<<k) + 1;
        y2 = y2 - (1<<t) + 1;
        return max({spt[x1][k][y1][t],spt[x1][k][y2][t],spt[x2][k][y1][t],spt[x2][k][y2][t]});
    }
}
