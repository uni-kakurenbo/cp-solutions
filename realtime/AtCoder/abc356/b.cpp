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
    uni::grid<i32> x(n, m); input >> x;

    REP(i, m) {
        i64 sum = 0;
        REP(j, n) {
            sum += x[j][i];
        }
        if(sum < a[i]) {
            print.no();
            return;
        }
    }

    print.yes();
}
