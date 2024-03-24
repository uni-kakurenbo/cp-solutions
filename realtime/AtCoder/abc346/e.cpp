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
        debug_("Case: #" + std::to_string(_));
        solve();
    }
    return 0;
}

void solve() {
    int h, w; cin >> h >> w;
    int q; cin >> q;

    vector<tuple<int,int,int>> queries;
    REP(i, h) {
        queries.emplace_back(1, i, 0);
    }
    REP(i, q) {
        int t, n, x; cin >> t >> n >> x; --n;
        queries.emplace_back(t, n, x);
    }

    reverse(ALL(queries));
    debug(queries);

    lib::map<int, ll> cnt;

    int a = 0, b = 0;
    lib::set<int> u, v;
    u.emplace(INF32), v.emplace(INF32);

    for(auto& [t, n, x] : queries) {
        if(t == 1) {
            if(*u.lower_bound(n) == n) continue;
            u.emplace(n);
            cnt[x] += w - b;
            ++a;
        }
        if(t == 2) {
            if(*v.lower_bound(n) == n) continue;
            v.emplace(n);
            cnt[x] += h - a;
            ++b;
        }
        debug(u, v); debug(cnt);
    }

    vector<spair<i64>> ans;

    FOR(i, 2 * 100'000) {
        if(cnt[i] > 0) ans.emplace_back(i, cnt[i]);
    }

    print(ans.size());
    ITR(v, c, ans) print(v, c);

    return;
}
