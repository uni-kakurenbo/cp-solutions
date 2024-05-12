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

void solve() {
    i64 cs[] = { 1, 5, 10, 50, 100, 500, 1000000 };
    array<i64, 6> cnt{}; input >> cnt;
    i64 n; input >> n;
    valarray<i64> xs(n); input >> xs;
    debug(xs, cnt);

    REP(i, 6) {
        i64 p = cs[i];
        i64 r = cs[i + 1];
        i64 take = ((xs % r) / p).sum();
        debug(r, xs, xs % r, take);

        if(take > cnt[i]) {
            print.no();
            return;
        }

        cnt[i] -= take;
        if(i < 5) cnt[i + 1] += (cnt[i] * p) / r;

        xs -= (xs % r);
    }

    print.yes();
}
