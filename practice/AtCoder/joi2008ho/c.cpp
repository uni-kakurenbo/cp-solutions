/*
 * @uni_kakurenbo
 * https://github.com/uni-kakurenbo/competitive-programming-workspace
 *
 * CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja
 */
/* #language C++ 20 GCC */
#include "template/standard.hpp"

void solve();

signed main() {
    debug(__cplusplus);
    int $ = 1;
    // std::cin >> $;
    for(int _ = 0; _ < $; ++_) {
        DEBUG("Case: #" + std::to_string(_));
        solve();
    }
    return 0;
}

void solve() {
    int n, m; input >> n >> m;
    valarray<i64> p(n); input >> p;


    lib::set<i64> q;
    q.insert(0);

    REP(i, n) {
        if(p[i] > m) continue;
        q.insert(p[i]);
        REP(j, i, n) {
            if(p[i] + p[j] > m) continue;
            q.insert(p[i] + p[j]);
        }
    }
    debug(q);

    i64 ans = 0;

    ITR(v, q) {
        auto itr = q.upper_bound(m - v);
        if(itr == q.begin()) chmax(ans, v);
        else chmax(ans, v + *std::ranges::prev(itr));
    }

    print(ans);
}
