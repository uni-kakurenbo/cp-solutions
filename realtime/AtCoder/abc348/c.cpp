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
    int n; input >> n;
    vector<int> a(n), c(n); input >> lib::views::zip(a, c);

    lib::map<int, int> min;
    min.set_default(INF32);

    ITR(x, y, lib::views::zip(a, c)) {
        chmin(min[y], x);
    }
    debug(min);

    int ans = 0;
    ITR(x, y, min) chmax(ans, y);

    print(ans);
}
