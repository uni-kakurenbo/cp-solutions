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
    uni::multi_container<i64, 3> a(n, n, n), b(n + 1, n + 1, n + 1); input >> a;

    REP(i, n ) REP(j, n) REP(k, n) b[i + 1][j + 1][k + 1] = a[i][j][k];

    FOR(i, n) FOR(j, n) REP(k, n) b[i][j][k + 1] += b[i][j][k];
    FOR(i, n) REP(j, n) FOR(k, n) b[i][j + 1][k] += b[i][j][k];
    REP(i, n) FOR(j, n) FOR(k, n) b[i + 1][j][k] += b[i][j][k];

    i32 q; input >> q;
    REP(q) {
        uni::array<spair<i32>, 3> p; input >> p;

        REP(i, 3) p[i].first--;

        i64 res = b[p[0].second][p[1].second][p[2].second];

        res -= b[p[0].first][p[1].second][p[2].second];
        res -= b[p[0].second][p[1].first][p[2].second];
        res -= b[p[0].second][p[1].second][p[2].first];

        res += b[p[0].first][p[1].first][p[2].second];
        res += b[p[0].second][p[1].first][p[2].first];
        res += b[p[0].first][p[1].second][p[2].first];

        res -= b[p[0].first][p[1].first][p[2].first];

        print(res);
    }
}
