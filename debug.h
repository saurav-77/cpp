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

auto to_string(__uint128_t num, int base = 10) {
    std::string str;
    do
        str += digit_to_char(num % base), num /= base;
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
    [&]<std::size_t... I>(std::index_sequence<I...>) {
        ((s += to_string(std::get<I>(t)) + ((I < sizeof...(Ts) - 1) ? ", " : "")),
         ...);
    }(std::make_index_sequence<sizeof...(Ts)>());
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