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
    i32 h, w, y; input >> h >> w >> y;
    uni::grid<i64> a(h, w); input >> a;

    std::priority_queue<spair<i64>, std::vector<spair<i64>>, std::greater<spair<i64>>> que;
    REP(i, h) {
        que.emplace(a(i, 0), a.id(i, 0));
        que.emplace(a(i, w - 1), a.id(i, w - 1));
    }
    REP(i, w) {
        que.emplace(a(0, i), a.id(0, i));
        que.emplace(a(h - 1, i), a.id(h - 1, i));
    }

    uni::grid<int> al(h, w);

    i32 cnt = 0;

    FOR(i, 1, y) {
        debug(que);
        while(!que.empty() && que.top().first <= i) {
            auto [tp, pos] = que.top(); que.pop();
            if(al(pos / w, pos % w)) continue;
            al(pos / w, pos % w) = true;
            if(tp <= i) {
                cnt++;
                ITR(ni, nj, a.vicinities4(pos / w, pos % w)) {
                    if(al(ni, nj)) continue;
                    que.emplace(a(ni, nj), a.id(ni, nj));
                }
            }
        }
        print(h * w - cnt);
    }
}
