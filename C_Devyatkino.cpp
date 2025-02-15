#pragma GCC optimize("Ofast,unroll-loops,no-stack-protector,fast-math,inline")
#include <bits/stdc++.h>
using namespace std;

using uint = uint32_t;
using ll = int64_t;
using ull = uint64_t;
using lll = __int128_t;
using ulll = __uint128_t;

#define len(x) (int(x.size()))

const ll MOD = 1e9 + 7;
const ll OMOD = 998'244'353;

#if defined(LOCAL)
#include "debug.h"
#else
#define clg(...)
#endif

void solve() {
    ll n;
    cin >> n;
    ll ans = LONG_MAX;
    {
        ll r = n % 10;
        if (r <= 6) {
            ans = r + 3;
        } else {
            ans = r - 7;
        }
    }
    
}

int32_t main() {
#ifdef CDEBUG
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    // freopen("error.txt", "w", stderr);
#endif
    ios::sync_with_stdio(0);
    cin.tie(0);
    int tc = 1;
    cin >> tc;
    for (int i = 1; i <= tc; ++i) {
        solve();
    }
    return 0;
}