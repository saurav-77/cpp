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

void solve();

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

#include <bits/stdc++.h>
using namespace std;

template <typename T>
class LazySegtree {
  private:
    const int sz;
    vector<T> tree;
    vector<T> lazy;

    void apply(int v, int len, T add) {
        tree[v] += add * len;
        lazy[v] += add;
    }

    void push_down(int v, int l, int r) {
        int m = (l + r) / 2;
        apply(2 * v, m - l + 1, lazy[v]);
        apply(2 * v + 1, r - m, lazy[v]);
        lazy[v] = 0;
    }

    void range_add(int v, int l, int r, int ql, int qr, int add) {
        if (qr < l || ql > r) {
            return;
        }
        if (ql <= l && r <= qr) {
            apply(v, r - l + 1, add);
        } else {
            push_down(v, l, r);
            int m = (l + r) / 2;
            range_add(2 * v, l, m, ql, qr, add);
            range_add(2 * v + 1, m + 1, r, ql, qr, add);
            tree[v] = tree[2 * v] + tree[2 * v + 1];
        }
    }

    T range_sum(int v, int l, int r, int ql, int qr) {
        if (qr < l || ql > r) {
            return 0;
        }
        if (ql <= l && r <= qr) {
            return tree[v];
        }
        push_down(v, l, r);
        int m = (l + r) / 2;
        return range_sum(2 * v, l, m, ql, qr) + range_sum(2 * v + 1, m + 1, r, ql, qr);
    }

  public:
    LazySegtree(int n) : sz(n), tree(4 * n), lazy(4 * n) {}

    void range_add(int ql, int qr, int add) { range_add(1, 0, sz - 1, ql, qr, add); }

    T range_sum(int ql, int qr) { return range_sum(1, 0, sz - 1, ql, qr); }
};
namespace reader {
    template <typename T>
    class is_iterable {
        template <typename T_>
        static auto test(T_ e) -> decltype(e.begin(), e.end(), std::true_type{});
        static std::false_type test(...);

      public:
        static constexpr bool value = decltype(test(std::declval<T>()))::value;
    };
    template <typename T>
    static constexpr bool is_iterable_v = is_iterable<T>::value;
    template <typename T>
    class is_readable {
        template <typename T_>
        static auto test(T_ e) -> decltype(std::declval<std::istream &>() >> e, std::true_type{});
        static std::false_type test(...);

      public:
        static constexpr bool value = decltype(test(std::declval<T>()))::value;
    };
    template <typename T>
    static constexpr bool is_readable_v = is_readable<T>::value;
    template <typename IStream,
              std::enable_if_t<std::conjunction_v<std::is_base_of<std::istream, std::remove_reference_t<IStream>>,
                                                  std::negation<std::is_const<std::remove_reference_t<IStream>>>>,
                               std::nullptr_t> = nullptr>
    struct InputStream {
      private:
        using istream_type = std::remove_reference_t<IStream>;
        IStream is;
        struct {
            InputStream *is;
            template <typename T>
            operator T() {
                T e;
                *is >> e;
                return e;
            }
        } _reader{this};

      public:
        template <typename IStream_>
        InputStream(IStream_ &&ts) : is(std::move(ts)) {}
        template <typename IStream_>
        InputStream(IStream_ &ts) : is(ts) {}
        template <typename T>
        InputStream &operator>>(T &e) {
            if constexpr (is_readable_v<T>)
                is >> e;
            else
                _read(e);
            return *this;
        }
        auto read() { return _reader; }
        template <typename Head, typename... Tail>
        void read(Head &head, Tail &...tails) {
            ((*this >> head) >> ... >> tails);
        }
        istream_type &get_stream() { return is; }

      private:
        static __uint128_t _stou128(const std::string &s) {
            __uint128_t ret = 0;
            for (char c : s)
                if ('0' <= c and c <= '9')
                    ret = 10 * ret + c - '0';
            return ret;
        }
        static __int128_t _stoi128(const std::string &s) { return (s[0] == '-' ? -1 : +1) * _stou128(s); }

        void _read(__uint128_t &v) { v = _stou128(std::string(_reader)); }
        void _read(__int128_t &v) { v = _stoi128(std::string(_reader)); }
        template <typename T, typename U>
        void _read(std::pair<T, U> &a) {
            *this >> a.first >> a.second;
        }
        template <size_t N = 0, typename... Args>
        void _read(std::tuple<Args...> &a) {
            if constexpr (N < sizeof...(Args))
                *this >> std::get<N>(a), _read<N + 1>(a);
        }
        template <typename Iterable, std::enable_if_t<is_iterable_v<Iterable>, std::nullptr_t> = nullptr>
        void _read(Iterable &a) {
            for (auto &e : a)
                *this >> e;
        }
    };
    template <typename IStream>
    InputStream(IStream &&) -> InputStream<IStream>;
    template <typename IStream>
    InputStream(IStream &) -> InputStream<IStream &>;

    InputStream cin{std::cin};

    auto re() { return cin.read(); }
    template <typename Head, typename... Tail>
    void re(Head &head, Tail &...tails) {
        cin.read(head, tails...);
    }
} // namespace reader
using reader::re;

/****************************************************************************************************************************************************/

void solve() {
    ll n, m;
    re(n, m);
    vector<ll> v(m);
    re(v);
    LazySegtree<ll> tree(n + 1);
    ll ans = 0;
    tree.range_add(1, min(n - 1, v[0]), 1);
    for (int i = 1; i < m; ++i) {
        if (v[i] == n) {
            ll g = tree.range_sum(1, n - 1);
            ans += g * 2;
            tree.range_add(1, n - 1, 1);
            continue;
        }
        ll t = n - v[i];
        ll g = tree.range_sum(t, n - 1);
        ans += g * 2;
        tree.range_add(1, v[i], 1);
    }
    cout << ans << endl;
}