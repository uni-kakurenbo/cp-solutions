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

#include "data_structure/lazy_segment_tree.hpp"
#include "action/range_set_range_max.hpp"
#include "action/range_set_range_min.hpp"

#include "template/warnings.hpp"
void solve() {
    i32 n, q; input >> n >> q;

    uni::lazy_segment_tree<uni::actions::range_set_range_min<i64>> min(n);
    uni::lazy_segment_tree<uni::actions::range_set_range_max<i64>> max(n);

    REP(i, n) {
        min[i] = i, max[i] = i;
    }

    vector<i64> cnt(n, 1);

    REP(q) {
        i32 t; input >> t;
        if(t == 1) {
            i32 x, c; input >> x >> c; --x, --c;

            auto v = min[x].val();
            debug(x, c, v);
            debug(min);

            auto l0 = min.min_left(x + 1, [&](auto s) { return s > INF32 || s == v; });
            auto l1 = max.min_left(x + 1, [&](auto s) { return s < -INF32 || s == v; });

            auto r0 = min.max_right(x, [&](auto s) { return s > INF32 || s == v; });
            auto r1 = max.max_right(x, [&](auto s) { return s < -INF32 || s == v; });

            auto l = uni::max(l0, l1);
            auto r = uni::min(r0, r1);

            debug(l0, l1, r0, r1);
            debug(l, r);

            min.apply(l, r, c);
            max.apply(l, r, c);

            cnt[v.val()] -= r - l;
            cnt[c] += r - l;
        }

        if(t == 2) {
            i32 c; input >> c; --c;

            print(cnt[c]);
        }

        debug(min, cnt);
    }
}
