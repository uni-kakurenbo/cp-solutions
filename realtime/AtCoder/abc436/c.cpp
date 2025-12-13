/*
 * @uni_kakurenbo
 * https://github.com/uni-kakurenbo/competitive-programming-workspace
 *
 * CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja
 */
/* #language C++ 23 GCC */
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
    i64 n, m; input >> n >> m;
    vector<i64> r(m), c(m); input >> uni::views::zip(r, c);

    using point = uni::point<i64>;
    std::set<point> placed;

    i32 cnt = 0;

    ITR(i, j, uni::views::zip(r, c)) {
        auto ok = true;
        REP(di, 2) REP(dj, 2) {
            auto ni = i + di, nj = j + dj;
            if(placed.contains({ni, nj})) BREAK(ok = false);
        }

        if(!ok) continue;

        REP(di, 2) REP(dj, 2) {
            auto ni = i + di, nj = j + dj;
            placed.emplace(ni, nj);
        }

        ++cnt;
    }

    print(cnt);
}
