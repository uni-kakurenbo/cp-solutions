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

void solve() {
    i64 n, k; input >> n >> k;
    valarray<i64> a(n); input >> a;
    a.sort();
    debug(a);

    lib::counter cnt(a);
    lib::adjacent_difference diff(ALL(a));
    debug(diff);

    i64 mc = 0;
    ITR(v, c, cnt) chmax(mc, c);

    i64 ans = (n - mc) * k;
    debug(ans);

    if(mc == 1) {
        ans -= lib::min(k - diff.max(), a.max() - a.min());
    }
    else if(mc == 2) {
        assert(false);
    }

    print(ans);
}
