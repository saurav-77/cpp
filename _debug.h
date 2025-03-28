// #define cerr cout

namespace debug_printer {
    template <typename T>
    concept is_iterable =
        requires(T &&x) { begin(x); } && !is_same_v<remove_cvref_t<T>, string>;
    void print(const char *x) { cerr << x; }
    void print(char x) { cerr << "\'" << x << "\'"; }
    void print(bool x) { cerr << (x ? "True" : "False"); }
    void print(const __uint128_t x) {
        constexpr uint64_t d19 = 10'000'000'000'000'000'000U;
        if (x > d19) {
            cerr << uint64_t(x / d19) << setfill('0') << setw(19)
                 << uint64_t(x % d19);
        } else {
            cerr << uint64_t(x);
        }
    }
    void print(const __int128_t x) {
        if (x >= 0) {
            print(__uint128_t(x));
        } else {
            cerr << '-';
            print(__uint128_t(-x));
        }
    }
    void print(string x) { cerr << "\"" << x << "\""; }
    void print(vector<bool> &v) {
        int f = 0;
        cerr << '{';
        for (auto &&i : v) cerr << (f++ ? "," : "") << (i ? "True" : "False");
        cerr << "}";
    }
    template <typename T>
    void print(T &&x) {
        if constexpr (is_iterable<T>)
            if (size(x) && is_iterable<decltype(*(begin(x)))>) {
                int f = 0;
                cerr << "\n~~~~~\n";
                for (auto &&i : x) {
                    cerr << setw(2) << left << f++, print(i), cerr << "\n";
                }
                cerr << "~~~~~\n";
            } else {
                int f = 0;
                cerr << "{";
                for (auto &&i : x) cerr << (f++ ? "," : ""), print(i);
                cerr << "}";
            }
        else if constexpr (requires { x.pop(); }) {
            auto temp = x;
            int f = 0;
            cerr << "{";
            if constexpr (requires { x.top(); })
                while (!temp.empty())
                    cerr << (f++ ? "," : ""), print(temp.top()), temp.pop();
            else
                while (!temp.empty())
                    cerr << (f++ ? "," : ""), print(temp.front()), temp.pop();
            cerr << "}";
        } else if constexpr (requires {
                                 x.first;
                                 x.second;
                             }) {
            cerr << '(', print(x.first), cerr << ',', print(x.second),
                cerr << ')';
        } else if constexpr (requires { get<0>(x); }) {
            int f = 0;
            cerr << '(', apply(
                             [&f](auto... args) {
                                 ((cerr << (f++ ? "," : ""), print(args)), ...);
                             },
                             x);
            cerr << ')';
        } else
            cerr << x;
    }
    template <typename T, typename... V>
    void printer(const char *names, T &&head, V &&...tail) {
        int i = 0;
        for (size_t bracket = 0;
             names[i] != '\0' and (names[i] != ',' or bracket != 0); i++)
            if (names[i] == '(' or names[i] == '<' or names[i] == '{')
                bracket++;
            else if (names[i] == ')' or names[i] == '>' or names[i] == '}')
                bracket--;
        cerr.write(names, i) << " = ";
        print(head);
        if constexpr (sizeof...(tail))
            cerr << " ||", printer(names + i + 1, tail...);
        else
            cerr << "]\n";
    }

}  // namespace debug_printer
void err_prefix(string func, int line) {
    std::cerr << "\033[0;31m\u001b[1mDEBUG\033[0m: "
              << "\u001b[34m" << func << "\033[0m"
              << ":"
              << "\u001b[34m" << line << "\033[0m: [";
}

#ifdef CDEBUG
#define clg(...)                        \
    err_prefix(__FUNCTION__, __LINE__), \
        debug_printer::printer(#__VA_ARGS__, __VA_ARGS__)
#else
#define clg(...)                                        \
    writer_out << __func__ << ":" << __LINE__ << ": [", \
        debug_printer::printer(#__VA_ARGS__, __VA_ARGS__)
#endif