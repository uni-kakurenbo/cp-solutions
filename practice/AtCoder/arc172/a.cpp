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
    i64 h, w, n; input >> h >> w >> n;
    vector<i64> a(n); input >> a;
    lib::counter cnt(a);

    FORD(v, 25L) {
        debug(v, cnt[v]);
        if((h / (1 << v)) * (w / (1 << v)) < cnt[v]) {
            print.no();
            return;
        }
        cnt[v - 1] += cnt[v] * 4;
    }

    print.yes();
}
