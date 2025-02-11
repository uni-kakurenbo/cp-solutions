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
    i32 n, s; input >> n >> s;
    vector<i32> a(n), b(n);
    input >> uni::views::zip(a, b);

    multi_container<i32, 2> dp(n + 1, s + 1, 0);
    dp[0][0] = 1;
    REP(i, n) {
        REP(x, s) {
            if(!dp[i][x]) continue;
            if(x + a[i] <= s) {
                dp[i + 1][x + a[i]] = a[i];
            }
            if(x + b[i] <= s) {
                dp[i + 1][x + b[i]] = b[i];
            }
        }
    }
    debug(dp);

    if(!dp[n][s]) {
        print("Impossible");
        return;
    }

    string res;

    i32 cur = s;
    REPD(i, n) {
        i32 take = dp[i + 1][cur];
        res += take == a[i] ? "A" : "B";
        cur -= take;
    }

    print(uni::reversed(res));
}
