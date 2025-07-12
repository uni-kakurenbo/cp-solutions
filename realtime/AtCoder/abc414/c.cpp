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

#include "template/warnings.hpp"
void solve() {
    i64 a, n; input >> a >> n;

    constexpr i64 MAX = 1'000'000;

    i64 ans = 0;

    FOR(x, 0, MAX) {
        auto xx = (x == 0 ? ""s : std::to_string(x));

        if(x > 0) {
            auto s = xx + uni::reversed(xx);
            auto v = std::stoll(s);
            if(v > n) continue;

            // debug(s);
            if(uni::is_palindrome(uni::to_base_n_string(v, a))) {
                ans += v;
            }
        }

        REP(t, 10) {
            auto tt = std::to_string(t);
            auto s = xx + tt + uni::reversed(xx);
            auto v = std::stoll(s);

            // debug(s);
            if(v > n) continue;
            if(uni::is_palindrome(uni::to_base_n_string(v, a))) {
                ans += v;
            }
        }
    }

    print(ans);
}
