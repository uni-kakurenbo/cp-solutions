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

#include "template/warnings.hpp"
void solve() {
    i32 n; input >> n;
    vector<array<i64, 3>> w(n); input >> w;

    array<i64, 3> dp{};

    REP(d, n) {
        array<i64, 3> nxt{};

        REP(i, 3) {
            REP(j, 3) {
                if(i == j) continue;
                nxt[i] = std::max(nxt[i], dp[j] + w[d][i]);
            }
        }

        dp = std::move(nxt);
    }

    print(std::ranges::max(dp));
}
