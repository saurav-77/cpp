#pragma GCC optimize("Ofast,unroll-loops,no-stack-protector,fast-math,inline")
#include <bits/stdc++.h>
using namespace std;

using uint = uint32_t;
using ll = int64_t;
using ull = uint64_t;
using lll = __int128_t;
using ulll = __uint128_t;

const ll MOD = 1e9 + 7;
const ll OMOD = 998'244'353;

#define writer_out cerr
string to_string(char c) { return "'" + string(1, c) + "'"; }

string to_string(const string &s) { return '"' + s + '"'; }

string to_string(bool b) { return (b ? "true" : "false"); }

std::string to_string(const char *c) { return string(c); }

inline char digit_to_char(int digit) { return static_cast<char>(digit + 48); }

auto to_string(__int128_t num, int base = 10) {
    const bool neg = num < 0;
    std::string str;
    if (num < -1'000'000) {
        str.push_back((-(num % 10)) + 48);
        num /= 10;
    }
    if (neg) num = -num;
    do str += digit_to_char(num % base), num /= base;
    while (num > 0);
    if (neg) str += '-';
    std::reverse(str.begin(), str.end());
    return str;
}

auto to_string(__uint128_t num, int base = 10) {
    std::string str;
    do str += digit_to_char(num % base), num /= base;
    while (num > 0);
    std::reverse(str.begin(), str.end());
    return str;
}

template <typename T>
string to_string(queue<T> q) {
    bool first = true;
    string res = "{";
    while (!q.empty()) {
        if (!first) {
            res += ", ";
        }
        first = false;
        res += to_string(q.front());
        q.pop();
    }
    res += "}";
    return res;
}

template <typename T>
string to_string(stack<T> st) {
    bool first = true;
    string res = "{";
    while (!st.empty()) {
        if (!first) {
            res += ", ";
        }
        first = false;
        res += to_string(st.top());
        st.pop();
    }
    res += "}";
    return res;
}

template <typename T, typename Sequence = vector<T>, typename Compare = less<T>>
string to_string(priority_queue<T, Sequence, Compare> pq) {
    bool first = true;
    string res = "{";
    while (!pq.empty()) {
        if (!first) {
            res += ", ";
        }
        first = false;
        res += to_string(pq.top());
        pq.pop();
    }
    res += "}";
    return res;
}

string to_string(const vector<bool> &v) {
    bool first = true;
    string res = "{";
    for (int i = 0; i < (int)v.size(); i++) {
        if (!first) {
            res += ", ";
        }
        first = false;
        res += to_string(v[i]);
    }
    res += "}";
    return res;
}

template <typename A, typename B>
string to_string(const pair<A, B> &p) {
    return "(" + to_string(p.first) + ", " + to_string(p.second) + ")";
}

template <class... Ts>
std::string to_string(const std::tuple<Ts...> &t) {
    std::string s = "(";
    [&]<std::size_t... I>(std::index_sequence<I...>) { ((s += to_string(std::get<I>(t)) + ((I < sizeof...(Ts) - 1) ? ", " : "")), ...); }(std::make_index_sequence<sizeof...(Ts)>());
    s += ")";
    return s;
}

template <size_t N>
string to_string(const bitset<N> &v) {
    string res = v.to_string();
    return res;
}

template <typename A>
string to_string(const A &v) {
    bool first = true;
    string res = "{";
    for (auto &x : v) {
        if (!first) {
            res += ", ";
        }
        first = false;
        res += to_string(x);
    }
    res += "}";
    return res;
}

void debug_out() { writer_out << "\n"; }
template <typename Head, typename... Tail>
void debug_out(const Head H, const Tail &...T) {
    writer_out << to_string(H);
    if (sizeof...(T))
        writer_out << "] [";
    else
        writer_out << "]";
    debug_out(T...);
}

void err_prefix(string func, int line) {
    writer_out << "\033[0;31m\u001b[1mDEBUG\033[0m: "
               << "\u001b[34m" << func << "\033[0m"
               << ":"
               << "\u001b[34m" << line << "\033[0m: ";
}
#ifdef CDEBUG
#define clg(...) err_prefix(__FUNCTION__, __LINE__), writer_out << "[" << #__VA_ARGS__ << "] = [", debug_out(__VA_ARGS__)
#else
#define clg(...) writer_out << __func__ << ":" << __LINE__ << ": " << "[" << #__VA_ARGS__ << "] = [", debug_out(__VA_ARGS__)
#endif

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
    template <typename IStream, std::enable_if_t<std::conjunction_v<std::is_base_of<std::istream, std::remove_reference_t<IStream>>, std::negation<std::is_const<std::remove_reference_t<IStream>>>>, std::nullptr_t> = nullptr>
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
                if ('0' <= c and c <= '9') ret = 10 * ret + c - '0';
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
            if constexpr (N < sizeof...(Args)) *this >> std::get<N>(a), _read<N + 1>(a);
        }
        template <typename Iterable, std::enable_if_t<is_iterable_v<Iterable>, std::nullptr_t> = nullptr>
        void _read(Iterable &a) {
            for (auto &e : a) *this >> e;
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
}  // namespace reader
using reader::re;
namespace printer {
#define SFINAE(x, ...)             \
    template <class, class = void> \
    struct x : std::false_type {}; \
    template <class T>             \
    struct x<T, std::void_t<__VA_ARGS__>> : std::true_type {}

    ostream &operator<<(ostream &os, const __uint128_t &x) {
        constexpr uint64_t d19 = 10'000'000'000'000'000'000U;
        if (x > d19) {
            os << uint64_t(x / d19) << setfill('0') << setw(19) << uint64_t(x % d19);
        } else {
            os << uint64_t(x);
        }
        return os;
    }
    ostream &operator<<(ostream &os, const __int128_t &x) {
        if (x >= 0) {
            os << __uint128_t(x);
        } else {
            os << '-' << __uint128_t(-x);
        }
        return os;
    }

    SFINAE(DefaultO, decltype(std::cout << std::declval<T &>()));
    SFINAE(IsTuple, typename std::tuple_size<T>::type);
    SFINAE(Iterable, decltype(std::begin(std::declval<T>())));

    template <auto &os, bool print_nd>
    struct Writer {
        template <class T>
        constexpr char Space(const T &) const {
            return print_nd && (Iterable<T>::value or IsTuple<T>::value) ? '\n' : ' ';
        }
        template <class T>
        void Impl(T const &t) const {
            if constexpr (DefaultO<T>::value)
                os << t;
            else if constexpr (Iterable<T>::value) {
                int i = 0;
                for (auto &&x : t) ((i++) ? (os << Space(x), Impl(x)) : Impl(x));
            } else if constexpr (IsTuple<T>::value) {
                std::apply(
                    [this](auto const &...args) {
                        int i = 0;
                        (((i++) ? (os << " ", Impl(args)) : Impl(args)), ...);
                    },
                    t);
            } else
                static_assert(IsTuple<T>::value, "No matching type for print");
        }
        template <class T>
        void ImplWrapper(T const &t) const {
            Impl(t);
        }
        template <class... Ts>
        void print(Ts const &...ts) const {
            ((Impl(ts)), ...);
        }
        template <class F, class... Ts>
        void print_with_sep(const std::string &sep, F const &f, Ts const &...ts) const {
            ImplWrapper(f), ((os << sep, ImplWrapper(ts)), ...), os << '\n';
        }
        void print_with_sep(const std::string &) const { os << '\n'; }
    };

    template <class... Ts>
    void pr(Ts const &...ts) {
        Writer<cout, true>{}.print(ts...);
    }
    template <class... Ts>
    void ps(Ts const &...ts) {
        Writer<cout, true>{}.print_with_sep(" ", ts...);
    }
}  // namespace printer
using printer::pr;
using printer::ps;

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

/****************************************************************************************************************************************************/

void solve() {
    ll n;
    re(n);
    vector<ll> v(n);
    re(v);
    vector<ll> s(n + 1);
    {
        int i = 0;
        while (i < n) {
            int j = i;
            int cnt = 0;
            while (j < n && v[j] == v[i]) {
                cnt++;
                ++j;
            }
            s[v[i]] = max<ll>(s[v[i]], cnt);
            i = j;
        }
    }
    ll ans = LLONG_MAX;
    for (int i = 1; i <= n; ++i) {
        if (s[i] != 0) {
            ans = min(ans, (n - s[i]) * (ll)i);
        }
    }
    ps(ans);
}