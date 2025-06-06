#define writer_out cerr

namespace debug_printer {
    template <typename T>
    concept is_iterable = requires(T &&x) { begin(x); } && !is_same_v<remove_cvref_t<T>, string>;
    void print(const char *x) { writer_out << x; }
    void print(char x) { writer_out << "\'" << x << "\'"; }
    void print(bool x) { writer_out << (x ? "True" : "False"); }
    void print(const __uint128_t x) {
        constexpr uint64_t d19 = 10'000'000'000'000'000'000U;
        if (x > d19) {
            writer_out << uint64_t(x / d19) << setfill('0') << setw(19) << uint64_t(x % d19);
        } else {
            writer_out << uint64_t(x);
        }
    }
    void print(const __int128_t x) {
        if (x >= 0) {
            print(__uint128_t(x));
        } else {
            writer_out << '-';
            print(__uint128_t(-x));
        }
    }
    void print(string x) { writer_out << "\"" << x << "\""; }
    void print(vector<bool> &v) {
        int f = 0;
        writer_out << '{';
        for (auto &&i : v) writer_out << (f++ ? "," : "") << (i ? "True" : "False");
        writer_out << "}";
    }
    template <typename T>
    void print(T &&x) {
        if constexpr (is_iterable<T>)
            if (size(x) && is_iterable<decltype(*(begin(x)))>) {
                int f = 0;
                writer_out << "\n~~~~~\n";
                for (auto &&i : x) {
                    writer_out << setw(2) << left << f++, print(i), writer_out << "\n";
                }
                writer_out << "~~~~~\n";
            } else {
                int f = 0;
                writer_out << "{";
                for (auto &&i : x) writer_out << (f++ ? "," : ""), print(i);
                writer_out << "}";
            }
        else if constexpr (requires { x.pop(); }) {
            auto temp = x;
            int f = 0;
            writer_out << "{";
            if constexpr (requires { x.top(); })
                while (!temp.empty()) writer_out << (f++ ? "," : ""), print(temp.top()), temp.pop();
            else
                while (!temp.empty()) writer_out << (f++ ? "," : ""), print(temp.front()), temp.pop();
            writer_out << "}";
        } else if constexpr (requires {
                                 x.first;
                                 x.second;
                             }) {
            writer_out << '(', print(x.first), writer_out << ',', print(x.second), writer_out << ')';
        } else if constexpr (requires { get<0>(x); }) {
            int f = 0;
            writer_out << '(', apply([&f](auto... args) { ((writer_out << (f++ ? "," : ""), print(args)), ...); }, x);
            writer_out << ')';
        } else
            writer_out << x;
    }
    template <typename T, typename... V>
    void printer(const char *names, T &&head, V &&...tail) {
        int i = 0;
        for (size_t bracket = 0; names[i] != '\0' and (names[i] != ',' or bracket != 0); i++)
            if (names[i] == '(' or names[i] == '<' or names[i] == '{')
                bracket++;
            else if (names[i] == ')' or names[i] == '>' or names[i] == '}')
                bracket--;
        writer_out.write(names, i) << " = ";
        print(head);
        if constexpr (sizeof...(tail))
            writer_out << " ||", printer(names + i + 1, tail...);
        else
            writer_out << "]\n";
    }

}  // namespace debug_printer
void err_prefix(string func, int line) {
    std::writer_out << "\033[0;31m\u001b[1mDEBUG\033[0m: "
                    << "\u001b[34m" << func << "\033[0m"
                    << ":"
                    << "\u001b[34m" << line << "\033[0m: [";
}

#ifdef CDEBUG
#define clg(...) err_prefix(__FUNCTION__, __LINE__), debug_printer::printer(#__VA_ARGS__, __VA_ARGS__)
#else
#define clg(...) writer_out << __func__ << ":" << __LINE__ << ": [", debug_printer::printer(#__VA_ARGS__, __VA_ARGS__)
#endif