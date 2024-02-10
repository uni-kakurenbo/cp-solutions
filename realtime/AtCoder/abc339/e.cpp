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

#include "data_structure/segment_tree.hpp"
#include "action/range_max.hpp"

void solve() {
    int n, d; input >> n >> d;
    valarray<i64> a(n); input >> a;
    int sup = a.max();
    a -= 1;

    lib::segment_tree<lib::actions::range_max<int>> dp(sup, 0);

    REP(i, n) {
        dp[a[i]] += dp(lib::max(0, a[i] - d), lib::min(sup, a[i] + d + 1)).fold().val() + 1;
        debug(dp);
    }

    print(dp.fold());
}
