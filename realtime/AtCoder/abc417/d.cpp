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

#include "data_structure/dynamic_sequence.hpp"
#include "data_structure/disjoint_set.hpp"

#include "template/warnings.hpp"
void solve() {
    i32 n; input >> n;
    vector<i64> p(n), a(n), b(n); input >> uni::views::zip(p, a, b);

    const auto sup = (p + a).max();

    uni::grid<i64> dp(n + 1, sup + 1); std::iota(ALL(dp[n]), 0);

    REPD(i, n) {
        FOR(j, sup) {
            if(j <= p[i]) dp[i][j] = dp[i + 1][j + a[i]];
            else dp[i][j] = dp[i + 1][uni::max(j - b[i], 0)];
        }
    }

    uni::accumulation acc(b);

    i32 q; input >> q;
    REP(q) {
        i32 x; input >> x;

        print([&] -> i32 {
            auto itr = acc.lower_bound(x - sup);
            auto m = itr - acc.begin();
            if(itr == acc.end()) return x - acc[-1];
            return dp[m][uni::max(0, x - *itr)];
        }());
    }
}
