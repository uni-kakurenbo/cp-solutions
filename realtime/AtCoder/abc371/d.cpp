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

#include "data_structure/dynamic_segment_tree.hpp"
#include "action/range_sum.hpp"

#include "template/warnings.hpp"

void solve() {
    i32 n; input >> n;
    vector<i64> x(n), p(n); input >> x >> p;

    auto base = INF32;
    x += base;

    debug(x);

    uni::dynamic_segment_tree<uni::actions::range_sum<i64>> ps(INF64);

    REP(i, n) {
        ps[x[i]] += p[i];
    }

    i32 q; input >> q;
    REP(q) {
        i64 l, r; input >> l >> r; ++r;
        l += base, r += base;
        print(ps(l, r).fold());
    }
}
