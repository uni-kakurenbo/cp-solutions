/*
 * @uni_kakurenbo
 * https://github.com/uni-kakurenbo/competitive-programming-workspace
 *
 * CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja
 */
/* #language C++ 20 GCC */
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

void solve() {
    int n, q; input >> n >> q;
    vector<int> x(n); input >> x;

    lib::graph<int> tree(n); tree.read_bidirectionally(n - 1);

    vector<multiset<int>> sets(n);

    auto dfs = [&](auto&& dfs, int v, int p) -> multiset<int> {
        multiset<int> res = { x[v] };
        ITR(nv, tree[v]) {
            if(nv == p) continue;
            res |= dfs(dfs, nv, v);
            while(res.size() > 20) res.pop_min();
        }
        return sets[v] = res;
    };
    dfs(dfs, 0, -1);

    REP(q) {
        int v, k; input >> v >> k; --v, --k;
        print(*std::next(sets[v].rbegin(), k));
    }
}
