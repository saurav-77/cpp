#pragma GCC optimize("Ofast,unroll-loops,no-stack-protector,fast-math,inline")
#include <bits/stdc++.h>
using namespace std;
#define writer_out cout
template <typename A, typename B>
ostream &operator<<(ostream &os, const pair<A, B> &p) {
    return os << '(' << p.first << ", " << p.second << ')';
}
template <typename... Args>
ostream &operator<<(ostream &os, const tuple<Args...> &t) {
    os << '(';
    apply(
        [&os](const Args &...args) {
            size_t n = 0;
            ((os << args << (++n != sizeof...(Args) ? ", " : "")), ...);
        },
        t);
    return os << ')';
}
template <typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type>
ostream &operator<<(ostream &os, const T_container &v) {
    os << '{';
    string sep;
    for (const T &x : v) os << sep << x, sep = ", ";
    return os << '}';
}
void dbg_out() { writer_out << endl; }
template <typename Head, typename... Tail>
void dbg_out(Head H, Tail... T) {
    writer_out << ' ' << H;
    dbg_out(T...);
}
#define clg(...) writer_out << '[' << __FILE__ << ':' << __LINE__ << "] (" << #__VA_ARGS__ << "):", dbg_out(__VA_ARGS__)

using uint = uint32_t;
using ll = int64_t;
using ull = uint64_t;
using lll = __int128_t;
using ulll = __uint128_t;

const ll MOD = 1e9 + 7;
const ll OMOD = 998'244'353;

template <typename tree_type, typename F>
class seg_tree {
    vector<tree_type> tree;
    F op;
    tree_type identity;
    int n;
    template <typename given_type>
    void build(int id, int l, int r, vector<given_type> &given) {
        if (l == r) {
            tree[id] = given[l];
            return;
        }
        int mid = midpoint(l, r);
        int lc = id << 1;
        int rc = (id << 1) | 1;
        build(lc, l, mid, given);
        build(rc, mid + 1, r, given);
        tree[id] = op(tree[lc], tree[rc]);
    }
    tree_type query(int id, int l, int r, int ql, int qr) {
        if (l > qr || r < ql) {
            return identity;
        }
        if (l >= ql && r <= qr) {
            return tree[id];
        }
        int mid = midpoint(l, r);
        int lc = id << 1;
        int rc = (id << 1) | 1;
        tree_type lhs = query(lc, l, mid, ql, qr);
        tree_type rhs = query(rc, mid + 1, r, ql, qr);
        return op(lhs, rhs);
    }
    void set(int id, int l, int r, int ind, tree_type value) {
        if (l == r && l == ind) {
            tree[id] = value;
            return;
        }
        int mid = midpoint(l, r);
        int lc = id << 1;
        int rc = (id << 1) | 1;
        if (ind <= mid)
            set(lc, l, mid, ind, value);
        else
            set(rc, mid + 1, r, ind, value);
        tree[id] = op(tree[lc], tree[rc]);
    }

    void add(int id, int l, int r, int ind, tree_type value) {
        if (l == r && l == ind) {
            tree[id] += value;
            return;
        }
        int mid = midpoint(l, r);
        int lc = id << 1;
        int rc = (id << 1) | 1;
        if (ind <= mid)
            add(lc, l, mid, ind, value);
        else
            add(rc, mid + 1, r, ind, value);
        tree[id] = op(tree[lc], tree[rc]);
    }

    tree_type get(int id, int l, int r, int ind) {
        if (l == r && l == ind) {
            return tree[id];
        }
        int mid = midpoint(l, r);
        int lc = id << 1;
        int rc = (id << 1) | 1;
        if (ind <= mid) {
            return get(lc, l, mid, ind);
        }
        return get(rc, mid + 1, r, ind);
    }

   public:
    template <typename given_type>
    seg_tree(vector<given_type> &g, F operation, tree_type identity_element) : op(operation), identity(identity_element) {
        this->n = g.size();
        tree.resize(4 * n);
        build(1, 0, n - 1, g);
    }
    // [l, r] 0-indexed
    tree_type query(int ql, int qr) {
        assert(ql >= 0 && qr <= n - 1 && ql <= qr);
        return query(1, 0, n - 1, ql, qr);
    }
    void add(int ind, tree_type delta) {
        assert(ind >= 0 && ind <= n - 1);
        add(1, 0, n - 1, ind, delta);
    }
    void set(int ind, tree_type val) {
        assert(ind >= 0 && ind <= n - 1);
        set(1, 0, n - 1, ind, val);
    }
    tree_type get(int ind) {
        assert(ind >= 0 && ind <= n - 1);
        return get(1, 0, n - 1, ind);
    }
    tree_type prefix_query(int r) { return query(0, r); }
    tree_type suffix_query(int l) { return query(l, n - 1); }
    tree_type operator[](int ind) {
        assert(ind >= 0 && ind <= n - 1);
        return get(ind);
    }
    tree_type query_all() { return tree[1]; }
};

class Solution {
   public:
    vector<int> maxSumOfThreeSubarrays(vector<int> &nums, int k) {
        int n = nums.size();
        vector<ll> v;
        ll sum = 0;
        seg_tree sumst(nums, [](ll a, ll b) { return a + b; }, 0LL);
        for (int i = 0; i + k - 1 < n; ++i) {
            v.push_back(sumst.query(i, i + k - 1));
        }

        seg_tree st(v, [](ll a, ll b) { return max(a, b); }, LLONG_MIN);
        ll maxi = LLONG_MIN;
        for (int i = k; i + k - 1 < n - k; ++i) {
            ll mid = sumst.query(i, i + k - 1);
            ll pp = st.prefix_query(i - k);
            ll nn = st.suffix_query(i - k+2);
            maxi = max(maxi, mid + pp + nn);
        }
        vector<int> ans;
        ll ppp = -1;
        ll nnn = -1;
        for (int i = k; i + k - 1 < n - k; ++i) {
            ll mid = sumst.query(i, i + k - 1);
            ll pp = st.prefix_query(i - k);
            ll nn = st.suffix_query(i - k+2);
            ll cur = mid + pp + nn;
            if (cur == maxi) {
                ans = {0, i, 0};
                ppp = pp;
                nnn = nn;
                break;
            }
        }
        for (int i = 0; i + k - 1 < ans[1]; ++i) {
            if (sumst.query(i, i + k - 1) == ppp) {
                ans[0] = i;
                break;
            }
        }
        for (int i = ans[1] + k; i + k - 1 < n; ++i) {
            if (sumst.query(i, i + k - 1) == nnn) {
                ans[2] = i;
                break;
            }
        }
        assert(ans[0] != -1 && ans[2] != -1);
        return ans;
    }
};
