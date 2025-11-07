template <typename tree_type>
class seg_tree {
   public:
    vector<tree_type> tree;
    tree_type identity;
    int n;

    // merge function
    tree_type op(tree_type x, true_type y) {
        return x + y;
    }


    template <typename given_type>
    void build(int id, int l, int r, vector<given_type>& given) {
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

    template <typename given_type>
    seg_tree(vector<given_type>& g, tree_type identity_element) : identity(identity_element) {
        this->n = g.size();
        tree.resize(4 * n);
        build(1, 0, n - 1, g);
    }

    seg_tree() {

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
