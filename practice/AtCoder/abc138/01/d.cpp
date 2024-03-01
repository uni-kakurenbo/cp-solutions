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
    lib::graph<int> tree(n); tree.read_bidirectionally(n - 1);

    std::vector<i64> parent(n);

    std::vector<i64> cnt(n);
    REP(q) {
        int p, x; input >> p >> x; --p;
        cnt[p] += x;
    }

    auto dfs = [&](auto&& dfs, int v, int p) -> void {
        if(p >= 0) cnt[v] += cnt[p];
        ITR(nv, tree[v]) {
            if(nv == p) continue;
            dfs(dfs, nv, v);
        }
    };
    dfs(dfs, 0, -1);

    print(cnt);
}
