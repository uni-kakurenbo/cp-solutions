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
    i64 n, l; input >> n >> l;
    vector<i64> a(n); input >> a;
    i64 m = a.max() + 1;

    vector<i64> ans(m, INF32);
    ans[0] = 0;

    i64 k = 1;
    i64 v = l - 1;
    while(v <= m && 2 * k <= l) {
        debug(v);
        REP(i, m) {
            if(i + v < m) chmin(ans[i + v], ans[i] + 1);
        }
        ++k;
        v = (l - k) * k;
    }

    ITR(x, a) {
        print(uni::to_optional_if_or_over(ans[x], INF32).value_or(-1));
    }
}
