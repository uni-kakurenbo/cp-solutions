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
    vector<i32> a(n); input >> a;
    auto b = a;
    REP(i, n) a[i] += i;
    REP(i, n) b[i] -= i;

    uni::counter cnt(b);
    debug(cnt);

    i64 ans = 0;
    REP(i, n) {
        ans += cnt[-a[i]];
    }

    print(ans);
}
