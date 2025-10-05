#include <bits/extc++.h>
using namespace std;

using ll = int64_t;
using ull = uint64_t;
using llx = __int128_t;
using ullx = __uint128_t;

const ll MOD = 1e9 + 7;
const ll OMOD = 998244353;

inline namespace IO {
#define SFINAE(x, ...)             \
    template <class, class = void> \
    struct x : std::false_type {}; \
    template <class T>             \
    struct x<T, std::void_t<__VA_ARGS__>> : std::true_type {}

    ostream &operator<<(ostream &os, __uint128_t x) {
        char buffer[41], *d = std::end(buffer);
        do *--d = '0' + (x % 10), x /= 10;
        while (x);
        os.rdbuf()->sputn(d, std::end(buffer) - d);
        return os;
    }
    ostream &operator<<(ostream &os, __int128_t x) {
        if (x < 0) os << '-';
        return os << (__uint128_t(x < 0 ? -x : x));
    }

    __uint128_t _stou128(const std::string &s) {
        __uint128_t ret = 0;
        for (char c : s)
            if ('0' <= c and c <= '9') ret = 10 * ret + c - '0';
        return ret;
    }
    __int128_t _stoi128(const std::string &s) { return (s[0] == '-' ? -1 : +1) * _stou128(s); }

    istream &operator>>(istream &in, __uint128_t &v) {
        string s;
        in >> s;
        v = _stou128(s);
        return in;
    }
    istream &operator>>(istream &in, __int128_t &v) {
        string s;
        in >> s;
        v = _stoi128(s);
        return in;
    }

    SFINAE(DefaultI, decltype(std::cin >> std::declval<T &>()));
    SFINAE(DefaultO, decltype(std::cout << std::declval<T &>()));
    SFINAE(IsTuple, typename std::tuple_size<T>::type);
    SFINAE(Iterable, decltype(std::begin(std::declval<T>())));

    template <auto &is>
    struct Reader {
        template <class T>
        void Impl(T &t) {
            if constexpr (DefaultI<T>::value)
                is >> t;
            else if constexpr (Iterable<T>::value) {
                for (auto &x : t) Impl(x);
            } else if constexpr (IsTuple<T>::value) {
                std::apply([this](auto &...args) { (Impl(args), ...); }, t);
            } else
                static_assert(IsTuple<T>::value, "No matching type for read");
        }
        template <class... Ts>
        void read(Ts &...ts) { ((Impl(ts)), ...); }
    };

    template <class... Ts>
    void re(Ts &...ts) { Reader<cin>{}.read(ts...); }

    template <auto &os, bool debug, bool print_nd>
    struct Writer {
        string comma() const { return debug ? "," : ""; }
        template <class T>
        constexpr char Space(const T &) const {
            return print_nd && (Iterable<T>::value or IsTuple<T>::value) ? '\n'
                                                                         : ' ';
        }
        template <class T>
        void Impl(T const &t) const {
            if constexpr (DefaultO<T>::value)
                os << t;
            else if constexpr (Iterable<T>::value) {
                if (debug) os << '{';
                int i = 0;
                for (auto &&x : t)
                    ((i++) ? (os << comma() << Space(x), Impl(x)) : Impl(x));
                if (debug) os << '}';
            } else if constexpr (IsTuple<T>::value) {
                if (debug) os << '(';
                std::apply(
                    [this](auto const &...args) {
                        int i = 0;
                        (((i++) ? (os << comma() << " ", Impl(args)) : Impl(args)),
                         ...);
                    },
                    t);
                if (debug) os << ')';
            } else
                static_assert(IsTuple<T>::value, "No matching type for print");
        }
        template <class T>
        void ImplWrapper(T const &t) const {
            if (debug) os << "";
            Impl(t);
            if (debug) os << "";
        }
        template <class... Ts>
        void print(Ts const &...ts) const {
            ((Impl(ts)), ...);
        }
        template <class F, class... Ts>
        void print_with_sep(const std::string &sep, F const &f,
                            Ts const &...ts) const {
            ImplWrapper(f), ((os << sep, ImplWrapper(ts)), ...), os << '\n';
        }
        void print_with_sep(const std::string &) const { os << '\n'; }
    };

    template <class... Ts>
    void pr(Ts const &...ts) {
        Writer<cout, false, true>{}.print(ts...);
    }
    template <class... Ts>
    void ps(Ts const &...ts) {
        Writer<cout, false, true>{}.print_with_sep(" ", ts...);
    }
}  // namespace IO

inline namespace Debug {
    template <typename... Args>
    void err(Args... args) {
        Writer<cerr, true, false>{}.print_with_sep(" | ", args...);
    }
    template <typename... Args>
    void errn(Args... args) {
        Writer<cerr, true, true>{}.print_with_sep(" | ", args...);
    }

    void err_prefix(string func, int line, string args) {
        cerr << "[DEBUG]"
             << " "
             << "[" << func << ""
             << ":"
             << "" << line << "]"
             << " "
             << "[" << args << "] = ";
    }

#ifndef LOCAL
#define clg(args...) err_prefix(__FUNCTION__, __LINE__, #args), err(args)
#define clgn(args...) err_prefix(__FUNCTION__, __LINE__, #args), errn(args)
#else
#define clg(...)
#define clgn(args...)
#endif
}  // namespace Debug

void solve() {
}

int32_t main() {
    ios_base::sync_with_stdio(false), cin.tie(nullptr);
#ifdef CDEBUG
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    // freopen("error.txt", "w", stderr);
#endif
    int tc = 1;
    cin >> tc;
    for (int i = 1; i <= tc; ++i) {
        solve();
    }
    return 0;
}