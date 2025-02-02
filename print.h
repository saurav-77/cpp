#define writer_out std::cout
template <typename A, typename B> ostream &operator<<(ostream &os, const pair<A, B> &p) {
    return os << '(' << p.first << ", " << p.second << ')';
}
template <typename... Args> ostream &operator<<(ostream &os, const tuple<Args...> &t) {
    os << '(';
    apply(
        [&os](const Args &...args) {
            size_t n = 0;
            ((os << args << (++n != sizeof...(Args) ? ", " : "")), ...);
        },
        t);
    return os << ')';
}
template <typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value,
                                                                typename T_container::value_type>::type>
ostream &operator<<(ostream &os, const T_container &v) {
    os << '{';
    string sep;
    for (const T &x : v)
        os << sep << x, sep = ", ";
    return os << '}';
}

void dbg_out() { writer_out << endl; }
template <typename Head, typename... Tail> void dbg_out(Head H, Tail... T) {
    writer_out << ' ' << H;
    dbg_out(T...);
}
#define clg(...)                                                                                             \
    writer_out << '[' << __func__ << ':' << __LINE__ << "] (" << #__VA_ARGS__ << "):", dbg_out(__VA_ARGS__)