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
        DEBUG("Case: #" + std::to_string(_));
        solve();
    }
    return 0;
}

#include "data_structure/lazy_segment_tree.hpp"
#include "action/range_add_range_sum.hpp"

void solve() {
    int n, m; input >> n >> m;
    valarray<i64> a(n), b(m); input >> a >> b;

    lib::lazy_segment_tree<lib::actions::range_add_range_sum<i64>> cnt(a);

    REP(i, m) {
        i64 v = cnt[b[i]].val().val();
        cnt[b[i]] = 0;

        i64 base = v / n;
        cnt.apply(base);

        i64 bind = b[i] + v - base * n + 1;

        debug(v, base, bind);

        cnt(b[i] + 1, lib::min(bind, n)).apply(1);

        if(bind >= n) {
            cnt(0, bind - n).apply(1);
        }

        debug(cnt);
    }

    print(cnt);
}
