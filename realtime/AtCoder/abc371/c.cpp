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
    i32 n; input >> n;

    uni::graph<i32> g0(n), g1(n);

    i32 m0; input >> m0;
    g0.read_bidirectionally(m0);

    i32 m1; input >> m1;
    g1.read_bidirectionally(m1);

    auto p0 = g0.make_has_edges();
    auto p1 = g1.make_has_edges();

    debug(g0, g1, p0, p1);

    uni::grid<i64> a(n, n);
    REP(i, n) {
        REP(j, i + 1, n) {
            i32 x; input >> x;
            a[i][j] = a[j][i] = x;
        }
    }
    debug(a);

    i64 ans = INF64;

    uni::vector<i32> p(n); std::iota(ALL(p), 0);
    // uni::vector<i32> p = { 1, 2, 3, 0, 4 };
    do {
        i64 sum = 0;

        REP(i, n) {
            REP(j, i + 1, n) {
                if(p1(i, j) != p0(p[i], p[j])) {
                    // debug(i, j, p[i], p[j], p0(i, j), p1(p[i], p[j]));
                    sum += a(i, j);
                }
            }
        }

        // debug(sum);
        chmin(ans, sum);
    } while(std::ranges::next_permutation(p).found);

    print(ans);
}
