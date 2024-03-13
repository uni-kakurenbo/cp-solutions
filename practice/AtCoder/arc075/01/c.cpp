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

#include "data_structure/dynamic_sequence.hpp"
#include "action/range_add_range_sum.hpp"

void solve() {
    int n, k; input >> n >> k;
    valarray<i64> a(n); input >> a;

    lib::dynamic_sequence<lib::actions::range_add_range_sum<i64>> data;

    i64 ans = 0;

    a -= k;
    i64 sum = 0;

    data[sum] += 1;
    debug(sum, data);

    ITR(v, a) {
        ans += data(sum -= v, INF64).fold().val();
        data[sum] += 1;
        debug(sum, data);
    }

    print(ans);
}
