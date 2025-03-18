#include <bits/stdc++.h>
using namespace std;

class BookMyShow {
  public:
    vector<pair<long, long>> g;
    vector<pair<long, long>> t_g;
    vector<long> s;
    vector<long> t_s;
    int n;
    int m;
    set<int> ti;
    BookMyShow(int n, int m) {
        for (int i = 0; i < n; ++i) {
            ti.insert(i);
        }
        this->n = n;
        this->m = m;
        g.assign(n, {m, 0});
        t_g.assign(4 * n, {m, 0});
        auto build = [&](this auto self, int ind, int l, int r) {
            if (l == r) {
                return;
            }
            int mid = l + (r - l) / 2;
            self(2 * ind + 1, l, mid);
            self(2 * ind + 2, mid + 1, r);
            t_g[ind] = {m, 0};
        };
        build(0, 0, n - 1);
        s.assign(n, m);
        t_s.assign(4 * n, m);
        auto bb = [&](this auto self, int ind, int l, int r) {
            if (l == r) {
                t_s[ind] = m;
                return;
            }
            int mid = l + (r - l) / 2;
            self(2 * ind + 1, l, mid);
            self(2 * ind + 2, mid + 1, r);
            int left = 2 * ind + 1;
            int right = 2 * ind + 2;
            t_s[ind] = t_s[left] + t_s[right];
        };
        bb(0, 0, n - 1);
    }

    vector<int> gather(int k, int maxRow) {
        auto search = [&](this auto self, int ind, int l, int r, int k, int &resind) -> pair<long, long> {
            if (t_g[ind].first >= k) {
                if (l == r) {
                    resind = l;
                    return t_g[ind];
                }
                int mid = l + (r - l) / 2;
                int left = 2 * ind + 1;
                int right = 2 * ind + 2;
                if (t_g[left].first >= k) {
                    return self(left, l, mid, k, resind);
                } else {
                    return self(right, mid + 1, r, k, resind);
                }
            }
            return {-1, -1};
        };
        int resind = -1;
        pair<long, long> res = search(0, 0, n - 1, k, resind);
        if (resind > maxRow || (res.first == -1 && res.second == -1)) {
            return {};
        }
        auto update = [&](this auto self, int ind, int l, int r, int tind, int val) {
            if (l == r && l == tind) {
                t_g[ind].first -= val;
                t_g[ind].second += val;
                return;
            }
            int mid = l + (r - l) / 2;
            int left = 2 * ind + 1;
            int right = 2 * ind + 2;
            if (tind <= mid) {
                self(left, 0, mid, tind, val);
            } else {
                self(right, mid + 1, r, tind, val);
            }
            t_g[ind] = t_g[left].first >= t_g[right].first ? t_g[left] : t_g[right];
        };
        update(0, 0, n - 1, resind, k);
        auto update_sum = [&](this auto self, int ind, int l, int r, int tind, int val) {
            if (l == r && l == tind) {
                t_s[ind] -= val;
                return;
            }
            int mid = l + (r - l) / 2;
            int left = 2 * ind + 1;
            int right = 2 * ind + 2;
            if (tind <= mid) {
                self(left, l, mid, tind, val);
            } else {
                self(right, mid + 1, r, tind, val);
            }
            t_s[ind] = t_s[left] + t_s[right];
        };
        update(0, 0, n - 1, resind, k);
        return {resind, (int)res.second};
    }

    bool scatter(int k, int maxRow) {}
};