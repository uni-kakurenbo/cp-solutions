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
    i32 h, w; input >> h >> w;
    lib::grid<i32> grid(h, w); input >> grid;

    i64 ans = 0;

    REP(x, 1UL, 1U << h) {
        vector<i32> cnt(h * w);

        REP(j, w) {
            i32 v = -1;
            bool ok = true;
            REP(i, h) {
                if(!lib::bit(x, i)) continue;
                if(v == -1) v = grid(i, j);
                if(v != grid(i, j)) BREAK(ok = false);
            }
            if(ok) cnt[v - 1]++;
        }
        debug(cnt);

        chmax(ans, std::popcount(x) * std::ranges::max(cnt));
    }

    print(ans);
}
