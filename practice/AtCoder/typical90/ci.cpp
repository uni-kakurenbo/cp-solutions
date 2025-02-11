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

#include "numeric/boundary_seeker.hpp"

void solve() {
    i64 n, p, k; input >> n >> p >> k;
    uni::grid<i128> grid(n, n); input >> grid;

    bool strict = false;

    auto ok = [&](i128 x) {
        auto copy = grid;
        ITRR(row, copy) ITRR(v, row) {
            if(v < 0) v = x;
        }

        REP(k, n) REP(i, n) REP(j, n) {
            chmin(copy[i][j], copy[i][k] + copy[k][j]);
        }

        i32 cnt = 0;

        REP(i, n) REP(j, i + 1, n) {
            if(copy(i, j) <= p) cnt++;
        }

        if(strict) return cnt < k;
        else return cnt <= k;
    };

    uni::boundary_seeker<i128> seeker(ok);

    i64 l = seeker.bound(INF64, 0);

    strict = true;
    i64 r = seeker.bound(INF64, 0);

    if(r == INF64) {
        print(l == INF64 ? "0" : "Infinity");
        return;
    }

    debug(l, r);

    print(r - l);
}
