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
    i32 h, w; input >> h >> w;

    uni::grid<i32> g(h, w, true);

    vector<uni::set<i32>> wall_h(h), wall_v(w);
    REP(i, h) REP(j, w) {
        wall_h[i].insert(j);
        wall_v[j].insert(i);
    }
    debug(wall_h, wall_v);

    i32 q; input >> q;
    REP(q) {
        debug(g);

        i32 i, j; input >> i >> j; --i, --j;

        if(g[i][j]) {
            g[i][j] = false;
            wall_h[i].erase(j);
            wall_v[j].erase(i);
            continue;
        }

        {
            auto pj = wall_h[i].next(j);
            if(pj) {
                debug(wall_h[i], *pj);
                assert(g[i][*pj]);
                g[i][*pj] = false;
                wall_h[i].erase(*pj), wall_v[*pj].erase(i);
                debug("test");
            }
        }
        {
            // debug("a");
            auto pj = wall_h[i].prev(j);
            // debug("b");
            if(pj) {
                debug(*pj);
                assert(g[i][*pj]);
                g[i][*pj] = false;
                wall_h[i].erase(*pj), wall_v[*pj].erase(i);
            }
        }
        {
            auto pi = wall_v[j].next(i);
            if(pi) {
                assert(g[*pi][j]);
                g[*pi][j] = false;
                wall_h[*pi].erase(j), wall_v[j].erase(*pi);
            }
        }
        {
            auto pi = wall_v[j].prev(i);
            if(pi) {
                assert(g[*pi][j]);
                g[*pi][j] = false;
                wall_h[*pi].erase(j), wall_v[j].erase(*pi);
            }
        }
    }
    debug(g);

    i32 sum = 0;
    ITR(x, g) sum += x.sum();
    print(sum);
}
