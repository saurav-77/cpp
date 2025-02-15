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

template <int m> class static_modint {
    using mint = static_modint;
    static_assert(m > 0, "Modulus must be positive");

  public:
    static constexpr int mod() { return m; }

    constexpr static_modint(long long y = 0) : x(y >= 0 ? y % m : (y % m + m) % m) {}

    constexpr int val() const { return x; }

    constexpr mint &operator+=(const mint &r) {
        if ((x += r.x) >= m)
            x -= m;
        return *this;
    }
    constexpr mint &operator-=(const mint &r) {
        if ((x += m - r.x) >= m)
            x -= m;
        return *this;
    }
    constexpr mint &operator*=(const mint &r) {
        x = static_cast<int>(1LL * x * r.x % m);
        return *this;
    }
    constexpr mint &operator/=(const mint &r) { return *this *= r.inv(); }

    constexpr bool operator==(const mint &r) const { return x == r.x; }

    constexpr mint operator+() const { return *this; }
    constexpr mint operator-() const { return mint(-x); }

    constexpr friend mint operator+(const mint &l, const mint &r) { return mint(l) += r; }
    constexpr friend mint operator-(const mint &l, const mint &r) { return mint(l) -= r; }
    constexpr friend mint operator*(const mint &l, const mint &r) { return mint(l) *= r; }
    constexpr friend mint operator/(const mint &l, const mint &r) { return mint(l) /= r; }

    constexpr mint inv() const {
        int a = x, b = m, u = 1, v = 0;
        while (b > 0) {
            int t = a / b;
            std::swap(a -= t * b, b);
            std::swap(u -= t * v, v);
        }
        return mint(u);
    }

    constexpr mint pow(unsigned long long n) const {
        mint ret(1), mul(x);
        while (n > 0) {
            if (n & 1)
                ret *= mul;
            mul *= mul;
            n >>= 1;
        }
        return ret;
    }

    friend std::ostream &operator<<(std::ostream &os, const mint &r) { return os << r.x; }

  private:
    int x;
};

// using mint = static_modint<998'244'353>;
using mint = static_modint<1'000'000'007>;

void solve() {}

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