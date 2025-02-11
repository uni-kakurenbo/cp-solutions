/*
 * @uni_kakurenbo
 * https://github.com/uni-kakurenbo/competitive-programming-workspace
 *
 * CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja
 */
/* #language C++ 23 GCC */
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

#include "data_structure/fenwick_tree.hpp"
#include "action/range_sum.hpp"

void solve() {
    i32 n; input >> n;
    valarray<i32> l(n), r(n); input >> uni::views::zip(l, r);
    l -= 1;

    ld ans = 0;

    REP(i, n) REP(j, i+1, n) {
        i64 sum = 0;
        REP(x, l[i], r[i]) REP(y, l[j], r[j]) {
            sum += (y < x);
        }
        ans += (ld)sum / ((r[i] - l[i]) * (r[j] - l[j]));
    }

    print(ans);
}
