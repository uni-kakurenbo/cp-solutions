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

#include "numeric/leveler.hpp"

#include "template/warnings.hpp"
void solve() {
    i32 h, w, k; input >> h >> w >> k;
    vector<i64> r(k), c(k); input >> uni::views::zip(r, c);
    r -= 1, c -= 1;

    uni::leveler<i64> lev(h, w);

    std::queue<i64> que;
    uni::vector<i64> dists(lev.sup(), INF64), cnt(lev.sup());

    REP(i, k) {
        que.emplace(lev.convert(r[i], c[i]));
        cnt[lev.convert(r[i], c[i])] = 2;
        dists[lev.convert(r[i], c[i])] = 0;
    }

    i64 ans = 0;

    while (!que.empty()) {
        debug(que, dists);
        auto id = que.front(); que.pop();
        auto v = lev.revert(id);

        REP(d, 4) {
            auto [dr, dc] = uni::DIRS4[d];
            auto nr = v[0] + dr, nc = v[1] + dc;
            if(nr < 0 || nr >= h || nc < 0 || nc >= w) continue;

            auto nid = lev.convert(nr, nc);

            if(++cnt[nid] == 2) {
                ans += (dists[nid] = dists[id] + 1);
                que.emplace(nid);
            }
        }
    }

    print(ans);
}
