/*
 * @uni_kakurenbo
 * https://github.com/uni-kakurenbo/competitive-programming-workspace
 *
 * CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja
 */
/* #language C++ 23 GCC */
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

#include "template/warnings.hpp"
void solve() {
    i32 n, m; input >> n >> m;

    uni::disjoint_set ds(n);

    vector<i64> deg(n);

    REP(m) {
        i32 p, q; char x, y; input >> p >> x >> q >> y;
        --p, --q;
        ds.merge(p, q);
        deg[p]++, deg[q]++;
    }

    auto groups = ds.groups();

    i64 ans = 0;

    ITR(group, groups) {
        bool f = true;
        ITR(i, group) {
            if(deg[i] != 2) f = false;
        }
        ans += f;
    }

    print(ans, ds.group_count() - ans);
}
