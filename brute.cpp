#pragma GCC optimize("Ofast,unroll-loops,no-stack-protector,fast-math,inline")
#include <bits/stdc++.h>
using namespace std;

using ll = int64_t;
using ull = uint64_t;
using uint = uint32_t;
using i8 = int8_t;
using u8 = uint8_t;
using ish = int16_t;
using ush = uint16_t;

#if defined(LOCAL)
#include "util.h"
#else
#define clg(x)
#endif

const ll MOD = 1e9 + 7;
const ll OMOD = 998'244'353;

inline namespace IO {
#define SFINAE(x, ...)																					   \
    template <class, class = void> struct x : std::false_type {};											\
    template <class T> struct x<T, std::void_t<__VA_ARGS__>> : std::true_type {}

SFINAE(DefaultI, decltype(std::cin >> std::declval<T &>()));
SFINAE(DefaultO, decltype(std::cout << std::declval<T &>()));
SFINAE(IsTuple, typename std::tuple_size<T>::type);
SFINAE(Iterable, decltype(std::begin(std::declval<T>())));

template <auto &is> struct Reader {
    template <class T> void Impl(T &t) {
        if constexpr (DefaultI<T>::value)
            is >> t;
        else if constexpr (Iterable<T>::value) {
            for (auto &x : t)
                Impl(x);
        } else if constexpr (IsTuple<T>::value) {
            std::apply([this](auto &...args) { (Impl(args), ...); }, t);
        } else
            static_assert(IsTuple<T>::value, "No matching type for read");
    }
    template <class... Ts> void read(Ts &...ts) { ((Impl(ts)), ...); }
};

template <class... Ts> void re(Ts &...ts) { Reader<cin>{}.read(ts...); }

template <auto &os, bool debug, bool print_nd> struct Writer {
    string comma() const { return debug ? "," : ""; }
    template <class T> constexpr char Space(const T &) const {
        return print_nd && (Iterable<T>::value or IsTuple<T>::value) ? '\n' : ' ';
    }
    template <class T> void Impl(T const &t) const {
        if constexpr (DefaultO<T>::value)
            os << t;
        else if constexpr (Iterable<T>::value) {
            if (debug)
                os << '{';
            int i = 0;
            for (auto &&x : t)
                ((i++) ? (os << comma() << Space(x), Impl(x)) : Impl(x));
            if (debug)
                os << '}';
        } else if constexpr (IsTuple<T>::value) {
            if (debug)
                os << '(';
            std::apply(
                [this](auto const &...args) {
                    int i = 0;
                    (((i++) ? (os << comma() << " ", Impl(args)) : Impl(args)), ...);
                },
                t);
            if (debug)
                os << ')';
        } else
            static_assert(IsTuple<T>::value, "No matching type for print");
    }
    template <class T> void ImplWrapper(T const &t) const {
        if (debug)
            os << "\033[0;31m";
        Impl(t);
        if (debug)
            os << "\033[0m";
    }
    template <class... Ts> void print(Ts const &...ts) const { ((Impl(ts)), ...); }
    template <class F, class... Ts>
    void print_with_sep(const std::string &sep, F const &f, Ts const &...ts) const {
        ImplWrapper(f), ((os << sep, ImplWrapper(ts)), ...), os << '\n';
    }
    void print_with_sep(const std::string &) const { os << '\n'; }
};

template <class... Ts> void pr(Ts const &...ts) { Writer<cout, false, true>{}.print(ts...); }
template <class... Ts> void ps(Ts const &...ts) { Writer<cout, false, true>{}.print_with_sep(" ", ts...); }
} // namespace IO

void solve() {
    
}

int32_t main() {
#if defined(LOCAL)
    freopen("input.txt", "r", stdin);
    freopen("brute.out.txt", "w", stdout);
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