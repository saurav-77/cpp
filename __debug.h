namespace debug_io {
#define S99(x, ...)                \
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

    S99(DefaultO, decltype(std::cout << std::declval<T &>()));
    S99(IsTuple, typename std::tuple_size<T>::type);
    S99(Iterable, decltype(std::begin(std::declval<T>())));

    template <auto &os, bool debug, bool print_nd>
    struct Writer {
        string comma() const { return debug ? "," : ""; }
        template <class T>
        constexpr char Space(const T &) const {
            return print_nd && (Iterable<T>::value or IsTuple<T>::value) ? '\n' : ' ';
        }
        template <class T>
        void Impl(T const &t) const {
            if constexpr (DefaultO<T>::value)
                os << t;
            else if constexpr (Iterable<T>::value) {
                if (debug) os << '{';
                int i = 0;
                for (auto &&x : t) ((i++) ? (os << comma() << Space(x), Impl(x)) : Impl(x));
                if (debug) os << '}';
            } else if constexpr (IsTuple<T>::value) {
                if (debug) os << '(';
                std::apply(
                    [this](auto const &...args) {
                        int i = 0;
                        (((i++) ? (os << comma() << " ", Impl(args)) : Impl(args)), ...);
                    },
                    t);
                if (debug) os << ')';
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
}  // namespace debug_io

namespace debug {
    using namespace debug_io;
    template <typename... Args>
    void err(Args... args) {
        Writer<cerr, true, false>{}.print_with_sep(" | ", args...);
    }

    void err_prefix(string func, int line, string args) {
        cerr << "\033[0;31m\u001b[1mDEBUG\033[0m"
             << " | "
             << "\u001b[34m" << func << "\033[0m"
             << ":"
             << "\u001b[34m" << line << "\033[0m"
             << ": "
             << "[" << args << "] = ";
    }
    void err_prefix2(string func, int line, string args) {
        cout << "DEBUG"
             << " | " << func << ":" << line << ": "
             << "[" << args << "] = ";
    }
}  // namespace debug

#ifdef CDEBUG
#define clg(args...) debug::err_prefix(__FUNCTION__, __LINE__, #args), debug::err(args)
#else
#define clg(args...) debug::err_prefix2(__FUNCTION__, __LINE__, #args), debug::err(args)
#endif