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

using mint = uni::modint998244353;

void solve() {
    i32 n, k; input >> n >> k;
    string s; input >> s;

    std::map<string, mint> dp;
    dp[""] = 1;

    REP(i, n) {
        map<string, mint> next;
        ITR(v, c, dp) {
            auto ok = [&](auto t) {
                return t.ssize() != k || t != uni::reversed(t);
            };

            if(s[i] != 'B' && ok(v + 'A')) next[(v + 'A').substr(v.ssize() >= k - 1)] += c;
            if(s[i] != 'A' && ok(v + 'B')) next[(v + 'B').substr(v.ssize() >= k - 1)] += c;
        }
        dp = std::move(next);
    }

    mint ans = 0;
    ITR(_v, c, dp) ans += c;

    print(ans);
}
