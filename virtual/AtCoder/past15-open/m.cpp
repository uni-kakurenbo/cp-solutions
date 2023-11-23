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

#include "algebraic/minimum.hpp"

void solve() {
    int n; input >> n;
    valarray<i64> d(n); input >> d;

    constexpr int MAX = 4'000'000;
    std::bitset<MAX> dp;
    dp.set(MAX / 2);
    ITR(v, d) dp = (dp << v) | (dp >> v);

    lib::algebraic::minimum<i64> ans;

    REP(i, MAX) {
        if(dp.test(i)) ans = ans + std::abs(i - MAX / 2);
    }

    print(ans);
}
