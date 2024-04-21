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

#include "data_structure/disjoint_set_union.hpp"

void solve() {
    i32 n, m; input >> n >> m;

    vector<i32> deg(n);
    uni::dsu ds(n);

    REP(m) {
        i32 a, b; input >> a >> b; --a, --b;
        ds.merge(a, b);
        deg[a]++, deg[b]++;
    }

    auto groups = ds.groups();

    i64 ans = 0;

    ITR(group, groups) {
        i32 es = 0;
        ITR(v, group) es += deg[v];
        debug(es);
        es /= 2;

        ans += uni::nCr(group.ssize(), 2L) - es;
    }

    print(ans);
}
