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
    valarray<i32> a(m); input >> a;

    if(a.max() == n || a.count(1) > 0) {
        print(-1);
        return;
    }

    a.sort();

    vector<i32> ans(n); std::iota(ALL(ans), 1);

    ITR(v, a) {
        std::swap(ans[v - 1], ans[v]);
    }

    print(ans);
}
