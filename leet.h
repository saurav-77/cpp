#include <bits/extc++.h>
using namespace std;

using ll = int64_t;
using ull = uint64_t;
using llx = __int128_t;
using ullx = __uint128_t;

const ll MOD = 1e9 + 7;
const ll OMOD = 998244353;

#define pinf(type) (numeric_limits<type>::max())
#define ninf(type) (numeric_limits<type>::min())

inline namespace IO {
#define SFINAE(x, ...)			 \
    template <class, class = void> \
    struct x : std::false_type {}; \
    template <class T>			 \
    struct x<T, std::void_t<__VA_ARGS__>> : std::true_type {}

    ostream &operator<<(ostream &os, __uint128_t x) {
        char buffer[41], *d = std::end(buffer);
        do *--d = '0' + (x % 10), x /= 10;
        while (x);
        os.rdbuf()->sputn(d, std::end(buffer) - d);
        return os;
    }
    ostream &operator<<(ostream &os, __int128_t x) {
        __uint128_t ans = x;
        if (x < 0) os << '-', ans = -ans;
        return os << ans;
    }

    SFINAE(DefaultO, decltype(std::cout << std::declval<T &>()));
    SFINAE(IsTuple, typename std::tuple_size<T>::type);
    SFINAE(Iterable, decltype(std::begin(std::declval<T>())));

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
}  // namespace IO

inline namespace Debug {
    template <typename... Args>
    void err(Args... args) {
        Writer<cout, true, false>{}.print_with_sep(" | ", args...);
    }
    template <typename... Args>
    void errn(Args... args) {
        Writer<cout, true, true>{}.print_with_sep(" | ", args...);
    }

    void err_prefix(string func, int line, string args) {
        cout << "DEBUG:"
             << " "
             << "" << func << ""
             << ":"
             << "" << line << ":"
             << "\n"
             << "[" << args << "] = ";
    }
}  // namespace Debug

#define clg(args...) err_prefix(__FUNCTION__, __LINE__, #args), err(args)
#define clgn(args...) err_prefix(__FUNCTION__, __LINE__, #args), errn(args)
