#define Writer_out cerr

inline namespace debug_print {
#define SFINAE(x, ...)                                                                                       \
    template <class, class = void> struct x : std::false_type {};                                            \
    template <class T> struct x<T, std::void_t<__VA_ARGS__>> : std::true_type {}

SFINAE(DefaultI, decltype(std::cin >> std::declval<T &>()));
SFINAE(DefaultO, decltype(std::cout << std::declval<T &>()));
SFINAE(IsTuple, typename std::tuple_size<T>::type);
SFINAE(Iterable, decltype(std::begin(std::declval<T>())));

template <auto &os, bool debug, bool print_nd> struct Printer {
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
    template <class T> void ImplWrapper(T const &t) const { Impl(t); }
    template <class... Ts> void print(Ts const &...ts) const { ((Impl(ts)), ...); }
    template <class F, class... Ts>
    void print_with_sep(const std::string &sep, F const &f, Ts const &...ts) const {
        ImplWrapper(f), ((os << sep, ImplWrapper(ts)), ...), os << '\n';
    }
    void print_with_sep(const std::string &) const { os << '\n'; }
};

} // namespace debug_print

template <typename... Args> void printerr(Args... args) {
    Printer<Writer_out, true, false>{}.print_with_sep(" | ", args...);
}
template <typename... Args> void printerrn(Args... args) {
    Printer<Writer_out, true, true>{}.print_with_sep(" | ", args...);
}

void err_prefix(string func, int line, string args) {
    Writer_out << func << ":" << line << ": "
               << "[" << args << "] = ";
}
#define clg(args...) err_prefix(__FUNCTION__, __LINE__, #args), printerr(args)