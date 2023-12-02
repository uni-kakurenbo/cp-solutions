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
        DEBUG("Case: #" + std::to_string(_));
        solve();
    }
    return 0;
}

void solve() {
    int r, c; input >> r >> c;
    lib::grid<int> G(r, c); input >> G;

    i64 ans = 0;

    REP(x, 1U << r) {
        i64 pro = 0;

        REP(i, c) {
            i64 cnt = 0;
            REP(j, r) {
                cnt += G(j, i) ^ lib::bit(x, j);
            }
            pro += lib::max(cnt, r - cnt);
        }

        chmax(ans, pro);
    }

    print(ans);
}
