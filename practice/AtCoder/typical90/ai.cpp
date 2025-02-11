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

#include "graph/compresseed_tree.hpp"
#include "graph/lowest_common_ancestor.hpp"

#pragma GCC diagnostic warning "-Wshadow=local"
void solve() {
    i32 n; input >> n;
    uni::graph<i32> tree(n); tree.read_bidirectionally(n - 1);

    vector<i32> ord(n);
    uni::lowest_common_ancestor lca(tree);

    i32 cnt = 0;
    auto dfs = [&](auto& _dfs, i32 v, i32 p) -> void {
        ord[v] = cnt++;
        ITR(e, tree[v]) {
            if(e == p) continue;
            _dfs(_dfs, e, v);
        }
    };
    dfs(dfs, 0, -1);


    i32 q; input >> q;
    REP(q) {
        i32 k; input >> k;
        vector<i32> vs(k); input >> vs;
        vs -= 1;
        vs.sort([&](i32 i, i32 j) { return ord[i] < ord[j]; });

        i32 res = 0;
        auto view = vs | uni::views::cyclic;
        REP(i, k) {
            res += lca.path_length(view[i], view[i + 1]);
        }

        print(res / 2);
    }
}
