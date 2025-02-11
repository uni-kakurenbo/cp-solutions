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

using mint = uni::modint998244353;

#include "data_structure/dynamic_sequence.hpp"
#include "action/range_add_range_sum.hpp"

#include "template/warnings.hpp"
void solve() {
    i64 n, k; input >> n >> k;
    vector<i64> a(n); input >> a;

    uni::dynamic_sequence<uni::actions::range_add_range_sum<mint>, uni::treap_context<uni::i128>> dp;
    dp.expand(-INF64, INF64);

    i64 base = 0;

    dp[0] = 1;

    REP(i, n) {
        // debug(dp);
        if(i != 0) {
            auto ak = dp[k + base].val().val();
            auto sum = dp.fold().val() - ak;
            dp[base] += sum;
        }

        base -= a[i];
    }

    auto ak = dp[k + base].val().val();
    print(dp.fold().val() - ak);
}
