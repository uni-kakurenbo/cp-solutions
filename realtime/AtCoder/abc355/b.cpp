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
    i32 n, m; input >> n >> m;
    vector<i64> a(n), b(m); input >> a >> b;
    auto v = uni::views::concat(a, b);
    vector<i64> c(ALL(v));
    c.sort();

    bool ok = false;

    uni::inverse<i64> inv(c);

    ITR(x, a) ITR(y, a) {
        if(x == y) continue;
        ok |= inv[x][0] + 1 == inv[y][0];
    }

    print.yesno(ok);
}
