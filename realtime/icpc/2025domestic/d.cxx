/*
 * @uni_kakurenbo
 * https://github.com/uni-kakurenbo/competitive-programming-workspace
 *
 * CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja
 */
/* #language C++ 23 GCC */
// #define DEBUGGER_ENABLED

#include "template/small.hpp"

// #include "template/debug.hpp"
// #include "snippet/aliases.hpp"
// #include <bits/stdc++.h>
// using namespace std;

using i32 = int;
using i64 = long;

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

#include "structure/grid.hpp"
#include "data_structure/disjoint_set.hpp"

#include "template/warnings.hpp"
void solve() {
    i32 h, w; input >> h >> w;
    if(h == 0) exit(0);

    uni::grid<char, string> g(h, w);
    input >> g;

    uni::disjoint_set ds(h * w);

    REP(i, h) REP(j, w) {
        ITR(ni, nj, g.vicinities4(i, j)) {
            if(g(i, j) == g(ni, nj)) {
                ds.merge(g.id(i, j), g.id(ni, nj));
            }
        }
    }


    i64 max_h = INF32, max_w = INF32;
    i64 min_h = -INF32, min_w = -INF32;

    auto groups = ds.groups();
    debug(g, groups);

    ITR(group, groups) {
        i64 min_i = INF32, min_j = INF32, max_i = -1, max_j = -1;

        bool side_h = false;
        bool side_w = false;

        ITR(x, group) {
            auto [ i, j ] = g.pos(x);

            if(i == 0 || i == h-1) side_h = true;
            if(j == 0 || j == w-1) side_w = true;

            chmin(min_i, i), chmin(min_j, j);
            chmax(max_i, i), chmax(max_j, j);
        }

        i64 vh = max_i - min_i + 1;
        i64 vw = max_j - min_j + 1;

        // debug(max_i, min_i);
        // debug(max_j, min_j);
        // debug(vh, vw, group.size());

        if(vh * vw != group.size()) {
            print(-1);
            return;
        }

        debug(vh, vw);

        if(!side_h && !side_w) {
            if(vh != vw) {
                print(-1);
                return;
            }
        }

        if(!side_h) {
            if(vh < min_h || vh > max_h) {
                print(-1);
                return;
            }
        }

        if(!side_w) {
            if(vw < min_w || vw > max_w) {
                print(-1);
                return;
            }
        }

        if(!side_h) chmin(max_h, vh);
        if(!side_w) chmin(max_w, vw);

        chmax(min_h, vh); chmax(min_w, vw);
    }

    debug(max_h, min_h, max_w, min_w);

    if(min_h > max_w || min_w > max_h || min_h > max_h || min_w > max_w) {
        print(-1);
        return;
    }

    if(max_h == min_h) {
        print(max_h);
        return;
    }

    if(max_w == min_w) {
        print(max_w);
        return;
    }

    print(0);
}
