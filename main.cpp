#include <bits/extc++.h>
using namespace std;

using ll = int64_t;
using ull = uint64_t;
using xll = __int128_t;
using xull = __uint128_t;

#if defined(LOCAL)
#include "__debug.h"
#else
#define clg(...)
#endif

void solve() {
    
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