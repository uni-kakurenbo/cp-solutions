/*
 * @uni_kakurenbo
 * https://github.com/uni-kakurenbo/competitive-programming-workspace
 *
 * CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja
 */
/* #language C++ 20 GCC */
// #define DEBUGGER_ENABLED

#include "template/standard.hpp"

void solve();

signed main() {
    debug(__cplusplus);
    int $ = 1;
    // std::cin >> $;
    for(int _ = 0; _ < $; ++_) {
        debug_("Case: #" + std::to_string(_));
        solve();
    }
    return 0;
}

#include "data_structure/disjoint_set_union.hpp"

// Weighted Union-Find (T: the type of v[0], v[1], ..., v[N-1])
template<class T> struct WeightedUnionFind {
    // core member
    vector<int> par;
    vector<T> weight;

    // constructor
    WeightedUnionFind() { }
    WeightedUnionFind(int N, T zero = 0) : par(N, -1), weight(N, zero) {}
    void init(int N, T zero = 0) {
        par.assign(N, -1);
        weight.assign(N, zero);
    }

    // core methods
    int root(int x) {
        if (par[x] < 0) return x;
        else {
            int r = root(par[x]);
            weight[x] += weight[par[x]];
            return par[x] = r;
        }
    }
    bool same(int x, int y) {
        return root(x) == root(y);
    }
    int size(int x) {
        return -par[root(x)];
    }

    // v[y] - v[x] = w
    bool merge(int x, int y, T w) {
        w += get_weight(x), w -= get_weight(y);
        x = root(x), y = root(y);
        if (x == y) return false;
        if (par[x] > par[y]) swap(x, y), w = -w; // merge technique
        par[x] += par[y];
        par[y] = x;
        weight[y] = w;
        return true;
    }

    // get v[x]
    T get_weight(int x) {
        root(x);
        return weight[x];
    }

    // get v[y] - v[x]
    T get_diff(int x, int y) {
        return get_weight(y) - get_weight(x);
    }

    // get groups
    vector<vector<int>> groups() {
        vector<vector<int>> member(par.size());
        for (int v = 0; v < (int)par.size(); ++v) {
            member[root(v)].push_back(v);
        }
        vector<vector<int>> res;
        for (int v = 0; v < (int)par.size(); ++v) {
            if (!member[v].empty()) res.push_back(member[v]);
        }
        return res;
    }

    // debug
    friend ostream& operator << (ostream &s, WeightedUnionFind uf) {
        const vector<vector<int>> &gs = uf.groups();
        for (const vector<int> &g : gs) {
            s << "group: ";
            for (int v : g) s << v << "(" << uf.get_weight(v) << ") ";
            s << endl;
        }
        return s;
    }
};

void solve() {
    i32 n, m; input >> n >> m;

    valarray<i32> a(n), b(n), c(n); input >> uni::views::zip(a, b, c);

    WeightedUnionFind<i32> ds(n);
    ITR(x, y, w, uni::views::zip(a, b, c)) {
        ds.merge(x, y, w);
    }

    auto groups = ds.groups();
    i32 k = groups.ssize();

    REP(i, n) {
        vector<i32> ok;
        REP(p, n) {
            uni::multi_container<i32, 2> dp(1 << n, false);
            dp[0] = true;

            ITR(group, groups) {
                vector<i32> ps;
                if(group.contains(i)) {
                    ps.emplace_back(i);
                }
            }
        }
    }
}
