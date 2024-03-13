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

void solve() {
    string t; input >> t;
    int n; input >> n;
    vector<vector<string>> s(n);
    REP(i, n) {
        int l; input >> l;
        REP(l) {
            string v; input >> v;
            s[i].push_back(v);
        }
    }
    debug(t, n, s);

    vector<int> dp(t.size() + 1, INF32);
    dp[0] = 0;

    REP(i, n) {
        auto next = dp;
        ITR(v, s[i]) {
            FOR(j, t.size() - v.size()) {
                debug(j, v, t.substr(j, v.size()));
                if(v == t.substr(j, v.size())) {
                    chmin(next[j + v.size()], dp[j] + 1);
                }
            }
        }
        dp = std::move(next);
        debug(dp);
    }

    print(lib::to_optional_if_or_over(dp[t.size()], INF32).value_or(-1));
}
