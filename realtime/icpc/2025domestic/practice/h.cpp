/*
 * @uni_kakurenbo
 * https://github.com/uni-kakurenbo/competitive-programming-workspace
 *
 * CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja
 */
/* #language C++ 23 GCC */
// #define DEBUGGER_ENABLED

#include "template/small.hpp"

void solve();

signed main() {
    debug(__cplusplus);
    int $ = 0;
    while(true) {
        debug_("Case: #" + std::to_string($++));
        solve();
    }
    return 0;
}

#include "numeric/fast_prime.hpp"
#include "structure/grid.hpp"

#include "template/warnings.hpp"
void solve() {
    i64 h, w; input >> h >> w;
    if(h == 0) exit(0);

    if(w == 2) {
        print.yes();
        REP(h) print(0, 1);
        return;
    }

    if(h % 2 == 0 || !uni::is_prime(w)) {
        print.no();
        return;
    }

    auto r = uni::primitive_root(w);

    uni::grid<i64> grid(h, w - 1);

    vector<i64> row(w - 1);

    i64 p = 1;
    REP(i, w - 1) {
        row[i] = p;
        p *= r;
        p %= w;
    }

    REP(i, h) {
        grid[i] = row;
        row.reverse();
    }

    debug(grid);

    vector<i64> ps(w - 1);

    REP(j, w - 1) {
        ps[j] = 1;
        REP(i, h) ps[j] *= grid(i, j), ps[j] %= w;
    }

    debug(ps);

    vector<i64> ids(w - 1); std::iota(ALL(ids), 0);
    ids.sort([&](auto i, auto j) { return ps[i] < ps[j]; });
    debug(ids);

    uni::grid<i64> ans(h, w);

    REP(i, h) REP(j, w - 1) {
        ans(i, j + 1) = grid(i, ids[j]);
    }

    bool ok = true;
    REP(j, w) {
        i64 p = 1;
        REP(i, h) p *= ans(i, j), p %= w;
        if(p != j) ok = false;
    }

    assert(ok);

    print.yes();
    ITR(row, ans) print(row);
}
