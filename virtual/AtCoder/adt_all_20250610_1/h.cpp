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
    i32 h, w, y; input >> h >> w >> y;
    uni::grid<i64> a(h, w); input >> a;

    debug(a);

    uni::priority_queue_rev<pair<i32, spair<i32>>> pq;
    REP(i, h) {
        pq.emplace(a(i, 0), std::make_pair(i, 0));
        pq.emplace(a(i, w-1), std::make_pair(i, w-1));
    }
    REP(i, w) {
        pq.emplace(a(0, i), std::make_pair(0, i));
        pq.emplace(a(h-1, i), std::make_pair(h-1, i));
    }

    debug(pq);
    i32 ans = h * w;

    uni::grid<i32> al(h, w);

    FOR(r, 1, y) {
        while(!pq.empty() && pq.top().first <= r) {
            auto p = pq.top().second; pq.pop();
            auto [i, j] = p;
            if(al(i, j)) continue;
            al(i, j) = true;
            --ans;

            REP(d, 4) {
                auto ni = i + DIRS4[d].first;
                auto nj = j + DIRS4[d].second;

                if(!a.is_valid(ni, nj)) continue;
                if(al(ni, nj)) continue;
                pq.emplace(a(ni, nj), std::make_pair(ni, nj));
            }
            debug(pq);
        }

        print(ans);
    }
}
