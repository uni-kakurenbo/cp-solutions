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
    i32 n; input >> n;
    vector<i64> a(n); input >> a;
    a.sort();

    i32 ans = 0;

    REP(i, n) {
        if(n - i >= a[i]) {
            chmax(ans, a[i]);
        }
    }

    FOR(i, n + 10) {
        if(a.end() - a.lower_bound(i)>= i) {
            chmax(ans, i);
        }
    }

    print(ans);
}
