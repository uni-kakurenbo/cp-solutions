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

void solve() {
    i32 n, m; input >> n >> m;

    uni::graph<i64> graph(n + m);
    vector<vector<i32>> as(n);
    valarray<i32> ks(m), cs(m);

    REP(i, m) {
        input >> ks[i] >> cs[i];
        as[i].resize(ks[i]);
        input >> as[i];
        ITRR(v, as[i]) --v;
    }
    debug(ks, cs, as);

    vector<i32> inds(m); std::iota(ALL(inds), 0);
    inds.sort([&](i32 i, i32 j) { return cs[i] < cs[j]; });
    debug(inds);


    uni::dsu ds(n + m);
    i64 ans = 0;

    ITR(i, inds) {
        uni::set<i32> roots;
        ITR(v, as[i]) roots.emplace(ds.leader(v));
        debug(i, roots);

        ans += cs[i] * (roots.ssize() - 1);

        ITR(v, as[i]) ds.merge(v, n + i);
    }

    {
        uni::set<i32> roots;
        REP(i, n) roots.emplace(ds.leader(i));
        if(roots.ssize() != 1) {
            print(-1);
            return;
        }
    }

    print(ans);
}
