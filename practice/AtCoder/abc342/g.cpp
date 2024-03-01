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
    // input >> $;
    for(int _ = 0; _ < $; ++_) {
        debug_("Case: #" + std::to_string(_));
        solve();
    }
    return 0;
}

#include "data_structure/segment_tree_rooter.hpp"
#include "data_structure/removable_priority_queue.hpp"

void solve() {
    int n; input >> n;

    std::vector<int> a(n);
    for(auto& v : a) input >> v;

    lib::segment_tree_rooter<int> rooter(n);
    std::cerr << rooter.allocated() << "\n";
    std::vector<lib::removable_priority_queue<std::priority_queue<int>/*, std::multiset<int>*/>> segments(rooter.allocated());

    for(int i=0; i<n; ++i) {
        segments[rooter.point_to_node(i)].emplace(a[i]);
    }

    int q; input >> q;
    std::vector<std::tuple<int, int, int>> queries;
    while(q-- > 0) {
        queries.emplace_back(-1, -1, -1);

        int t; input >> t;
        if(t == 1) {
            int l, r; input >> l >> r; --l;
            int x; input >> x;
            queries.back() = { l, r, x };

            rooter.range_to_nodes(l, r, [&](int p) {
                segments[p].emplace(x);
            });
        }
        if(t == 2) {
            int i; input >> i; --i;
            const auto [ l, r, x ] = queries[i];

            rooter.range_to_nodes(l, r, [&](int p) {
                segments[p].eliminate(x);
            });
        }
        if(t == 3) {
            int i; input >> i; --i;

            int ans = 0;

            rooter.point_to_path(i, [&](int p) {
                if(segments[p].empty()) return;
                ans = std::max(ans, segments[p].top());
            });

            print(ans);
        }
    }
}
