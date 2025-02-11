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

#include <atcoder/mincostflow.hpp>

#pragma GCC diagnostic warning "-Wshadow=local"
void solve() {
    i32 n, w; input >> n >> w;
    vector<i64> a(n); input >> a;

    atcoder::mcf_graph<i32, i32> mcf(n + 2);
    i32 no = n, ent = n + 1;

    REP(i, n) {
        mcf.add_edge(no, i, a[i], 1);
        mcf.add_edge(i, ent, w, 1);

        i32 k; input >> k;
        REP(k) {
            i32 v; input >> v; --v;
            mcf.add_edge(v, i, INF32, 1);
        }
    }

    print(a.sum() - mcf.flow(no, ent).first);
}
