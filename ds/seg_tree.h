template <typename T, typename F>
struct seg_tree {
    int N;
    int size;
    vector<T> seg;
    const F f;
    const T I;

    void init(int _N) {
        N = _N;
        size = 1;
        while (size < N) size <<= 1;
        seg.assign(2 * size, I);
    }

    void build() {
        for (int k = size - 1; k > 0; k--) {
            seg[k] = f(seg[2 * k], seg[2 * k + 1]);
        }
    }

    void set(int k, T x) {
        k += size;
        seg[k] = x;
        while (k >>= 1) {
            seg[k] = f(seg[2 * k], seg[2 * k + 1]);
        }
    }

    void add(int k, T x) {
        k += size;
        seg[k] += x;
        while (k >>= 1) {
            seg[k] = f(seg[2 * k], seg[2 * k + 1]);
        }
    }

    // query to [a, b)
    T query(int a, int b) {
        T L = I, R = I;
        for (a += size, b += size; a < b; a >>= 1, b >>= 1) {
            if (a & 1) L = f(L, seg[a++]);
            if (b & 1) R = f(seg[--b], R);
        }
        return f(L, R);
    }

    T &operator[](const int &k) { return seg[k + size]; }

    seg_tree(F _f, const T &I_) : N(0), size(0), f(_f), I(I_) {}

    seg_tree(int _N, F _f, const T &I_) : f(_f), I(I_) { init(_N); }

    seg_tree(const vector<T> &v, F _f, T I_) : f(_f), I(I_) {
        init(v.size());
        for (int i = 0; i < (int)v.size(); i++) {
            seg[i + size] = v[i];
        }
        build();
    }
};