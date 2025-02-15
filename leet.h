#define writer_out cout
namespace __DEBUG_UTIL__ {
    /* Primitive Datatypes Print */
    void print(const char *x) { writer_out << x; }
    void print(bool x) { writer_out << (x ? "T" : "F"); }
    void print(char x) { writer_out << '\'' << x << '\''; }
    void print(signed short int x) { writer_out << x; }
    void print(unsigned short int x) { writer_out << x; }
    void print(signed int x) { writer_out << x; }
    void print(unsigned int x) { writer_out << x; }
    void print(signed long int x) { writer_out << x; }
    void print(unsigned long int x) { writer_out << x; }
    void print(signed long long int x) { writer_out << x; }
    void print(unsigned long long int x) { writer_out << x; }
    void print(float x) { writer_out << x; }
    void print(double x) { writer_out << x; }
    void print(long double x) { writer_out << x; }
    void print(string x) { writer_out << '\"' << x << '\"'; }
    template <size_t N> void print(bitset<N> x) { writer_out << x; }
    void print(vector<bool> v) { /* Overloaded this because stl optimizes
                                    vector<bool> by using _Bit_reference instead of
                                    bool to conserve space. */
        int f = 0;
        writer_out << '{';
        for (auto &&i : v)
            writer_out << (f++ ? "," : "") << (i ? "T" : "F");
        writer_out << "}";
    }
    /* Templates Declarations to support nested datatypes */
    template <typename T> void print(T &&x);
    template <typename T> void print(vector<vector<T>> mat);
    template <typename T, size_t N, size_t M> void print(T (&mat)[N][M]);
    template <typename F, typename S> void print(pair<F, S> x);
    template <typename T, size_t N> struct Tuple;
    template <typename T> struct Tuple<T, 1>;
    template <typename... Args> void print(tuple<Args...> t);
    template <typename... T> void print(priority_queue<T...> pq);
    template <typename T> void print(stack<T> st);
    template <typename T> void print(queue<T> q);
    /* Template Datatypes Definitions */
    template <typename T> void print(T &&x) {
        /*  This works for every container that supports range-based loop
            i.e. vector, set, map, oset, omap, dequeue */
        int f = 0;
        writer_out << '{';
        for (auto &&i : x)
            writer_out << (f++ ? "," : ""), print(i);
        writer_out << "}";
    }
    template <typename T> void print(vector<vector<T>> mat) {
        int f = 0;
        writer_out << "\n~~~~~\n";
        for (auto &&i : mat) {
            writer_out << setw(2) << left << f++, print(i), writer_out << "\n";
        }
        writer_out << "~~~~~\n";
    }
    template <typename T, size_t N, size_t M> void print(T (&mat)[N][M]) {
        int f = 0;
        writer_out << "\n~~~~~\n";
        for (auto &&i : mat) {
            writer_out << setw(2) << left << f++, print(i), writer_out << "\n";
        }
        writer_out << "~~~~~\n";
    }
    template <typename F, typename S> void print(pair<F, S> x) {
        writer_out << '(';
        print(x.first);
        writer_out << ',';
        print(x.second);
        writer_out << ')';
    }
    template <typename T, size_t N> struct Tuple {
        static void printTuple(T t) {
            Tuple<T, N - 1>::printTuple(t);
            writer_out << ",", print(get<N - 1>(t));
        }
    };
    template <typename T> struct Tuple<T, 1> {
        static void printTuple(T t) { print(get<0>(t)); }
    };
    template <typename... Args> void print(tuple<Args...> t) {
        writer_out << "(";
        Tuple<decltype(t), sizeof...(Args)>::printTuple(t);
        writer_out << ")";
    }
    template <typename... T> void print(priority_queue<T...> pq) {
        int f = 0;
        writer_out << '{';
        while (!pq.empty())
            writer_out << (f++ ? "," : ""), print(pq.top()), pq.pop();
        writer_out << "}";
    }
    template <typename T> void print(stack<T> st) {
        int f = 0;
        writer_out << '{';
        while (!st.empty())
            writer_out << (f++ ? "," : ""), print(st.top()), st.pop();
        writer_out << "}";
    }
    template <typename T> void print(queue<T> q) {
        int f = 0;
        writer_out << '{';
        while (!q.empty())
            writer_out << (f++ ? "," : ""), print(q.front()), q.pop();
        writer_out << "}";
    }
    /* Printer functions */
    void printer(const char *) {} /* Base Recursive */
    template <typename T, typename... V> void printer(const char *names, T &&head, V &&...tail) {
        /* Using && to capture both lvalues and rvalues */
        int i = 0;
        for (size_t bracket = 0; names[i] != '\0' and (names[i] != ',' or bracket != 0); i++)
            if (names[i] == '(' or names[i] == '<' or names[i] == '{')
                bracket++;
            else if (names[i] == ')' or names[i] == '>' or names[i] == '}')
                bracket--;
        writer_out.write(names, i) << " = ";
        print(head);
        if (sizeof...(tail))
            writer_out << " ||", printer(names + i + 1, tail...);
        else
            writer_out << "]\n";
    }
    /* PrinterArr */
    void printerArr(const char *) {} /* Base Recursive */
    template <typename T, typename... V> void printerArr(const char *names, T arr[], size_t N, V... tail) {
        size_t ind = 0;
        for (; names[ind] and names[ind] != ','; ind++)
            writer_out << names[ind];
        for (ind++; names[ind] and names[ind] != ','; ind++)
            ;
        writer_out << " = {";
        for (size_t i = 0; i < N; i++)
            writer_out << (i ? "," : ""), print(arr[i]);
        writer_out << "}";
        if (sizeof...(tail))
            writer_out << " ||", printerArr(names + ind + 1, tail...);
        else
            writer_out << "]\n";
    }
} // namespace __DEBUG_UTIL__

#define clg(...) writer_out << __func__ << ":" << __LINE__ << ": [", __DEBUG_UTIL__::printer(#__VA_ARGS__, __VA_ARGS__)
