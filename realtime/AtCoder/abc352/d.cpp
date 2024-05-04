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

#include "data_structure/disjoint_sparse_table.hpp"
#include "action/range_chminchmax_range_minmax.hpp"

void solve() {
    i32 n, k; input >> n >> k;
    valarray<i32> p(n); input >> p; p -= 1;

    // if(k == 1) {
    //     print(0);
    //     return;
    // }

    uni::inverse<i32> inv(p);
    uni::disjoint_sparse_table<uni::actions::range_chminchmax_range_minmax<i32>> vv(({
        vector<spair<i32>> v(n);
        REP(i, n) v[i] = { inv[i][0], inv[i][0] };
        v;
    }));

    debug(inv, vv);

    i32 ans = INF32;
    FOR(i, n - k) {
        auto v = vv(i, i + k).fold();
        debug(v);
        chmin(ans, v->second - v->first);
    }

    print(ans);

}
