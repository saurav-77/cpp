#define writer_out cerr
string to_string(char c) { return "'" + string(1, c) + "'"; }

string to_string(const string &s) { return '"' + s + '"'; }

string to_string(bool b) { return (b ? "true" : "false"); }

std::string to_string(const char *c) { return string(c); }

inline auto digit_to_char(int digit) { return static_cast<char>(digit > 9 ? 'a' + digit - 10 : '0' + digit); }

inline auto to_string(__int128_t num, int base = 10) {
    const auto neg = num < 0;
    std::string str;
    if (neg)
        num = -num;
    do
        str += digit_to_char(num % base), num /= base;
    while (num > 0);
    if (neg)
        str += '-';
    std::reverse(str.begin(), str.end());
    return str;
}

inline auto to_string(__uint128_t num, int base = 10) {
    std::string str;
    do
        str += digit_to_char(num % base), num /= base;
    while (num > 0);
    std::reverse(str.begin(), str.end());
    return str;
}

template <typename T> string to_string(queue<T> q) {
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

template <typename T> string to_string(stack<T> st) {
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

template <typename A, typename B> string to_string(const pair<A, B> &p) {
    return "(" + to_string(p.first) + ", " + to_string(p.second) + ")";
}

template <typename A, typename B, typename C> string to_string(const tuple<A, B, C> &p) {
    return "(" + to_string(get<0>(p)) + ", " + to_string(get<1>(p)) + ", " + to_string(get<2>(p)) + ")";
}

template <typename A, typename B, typename C, typename D> string to_string(const tuple<A, B, C, D> &p) {
    return "(" + to_string(get<0>(p)) + ", " + to_string(get<1>(p)) + ", " + to_string(get<2>(p)) + ", " +
           to_string(get<3>(p)) + ")";
}

template <size_t N> string to_string(const bitset<N> &v) {
    string res = v.to_string();
    return res;
}

template <typename A> string to_string(const A &v) {
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
template <typename Head, typename... Tail> void debug_out(const Head H, const Tail &...T) {
    writer_out << to_string(H);
    if (sizeof...(T))
        writer_out << "] [";
    else
        writer_out << "]";
    debug_out(T...);
}

#define clg(...)                                                                                             \
    writer_out << "\033[0;31m\u001b[1mDEBUG\033[0m: ";                                                       \
    writer_out << __func__ << ":" << __LINE__ << ": " << "[" << #__VA_ARGS__ << "]: [",                     \
        debug_out(__VA_ARGS__)

#define start                                                                                                \
    using namespace chrono;                                                                                  \
    auto start_time = high_resolution_clock::now();

#define stop                                                                                                 \
    auto stop_time = high_resolution_clock::now();                                                           \
    auto duration = duration_cast<milliseconds>(stop_time - start_time);                                     \
    cerr << "[Time Taken" << " = " << duration << "]" << endl << endl;
