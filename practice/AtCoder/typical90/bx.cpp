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
    vector<i32> a(n); input >> a;
    i64 sum = lib::sum(a, 0L);

    if(sum % 10) {
        print.no();
        return;
    }
    sum /= 10;

    lib::accumulation<i64> cum(lib::views::concat(a, a));
    debug(cum);

    REP(i, n) {
        if(cum.binary_search(sum + cum[i])) {
            print.yes();
            return;
        }
    }

    print.no();
}
