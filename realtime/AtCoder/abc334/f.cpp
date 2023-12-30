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


#include "data_structure/implicit_treap.hpp"
#include "action/range_add_range_min.hpp"

using point = lib::point<ld>;

void solve() {
    int n, k; input >> n >> k;
    valarray<point> ps(n + 1); input >> ps;
    auto s = ps.front();

    lib::implicit_treap<lib::actions::range_add_range_min<ld>> dp(k+1, INF64);

    dp[k] = 0;

    FOR(i, 1, n) {
        ld min = dp(0, k).fold().val();

        dp.apply(0, k+1, lib::distance(ps[i-1], ps[i]));

        if(min < INF64) dp[k] = min + lib::distance(ps[i-1], s) + lib::distance(s, ps[i]);

        dp.pop_front();
        dp.push_back(INF64);
    }

    print(dp(0, k).fold().val() + lib::distance(ps[n], s));
}
