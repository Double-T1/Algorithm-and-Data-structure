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

class Fraction {
public:
    ll n, d;
    
public:
    // a being the nominator, b being the denominator
    Fraction(ll a=0, ll b=1) {
        trim(a,b);
        n = a, d = b;
    }
    
    void fAdd(ll a, ll b) {
        if (b == 0) return;
        trim(a,b);
        ll new_n = a*d + n*b;
        ll new_d = b*d;
        trim(new_n, new_d);
        n = new_n;
        d = new_d;
    }
    
private:
    void trim(ll& n, ll& d) {
        long long g = gcd(n,d);
        n /= g;
        d /= g;
    }
};


int main() {
    


    
}