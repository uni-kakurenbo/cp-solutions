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
    int n; input >> n;
    valarray<i64> a(n); input >> a;

    map<int, int> next, prev;
    next.set_default(-1);
    prev.set_default(-1);

    REP(i, 1, n) {
        prev[a[i]] = a[i - 1];
        next[a[i - 1]] = a[i];
    }


    next[0] = a[0];
    prev[a[0]] = 0;

    debug(next, prev);

    int q; input >> q;
    REP(q) {
        int t; input >> t;

        if(t == 1) {
            int x, y; input >> x >> y;
            prev[next[x]] = y;
            next[y] = next[x];
            next[x] = y;
            prev[y] = x;
        }
        if(t == 2) {
            int x; input >> x;
            next[prev[x]] = next[x];
            prev[next[x]] = prev[x];
        }

        debug(next, prev);
    }

    vector<int> ans;

    int now = 0;
    while(true) {
        now = next[now];
        if(now <= 0) break;
        ans.push_back(now);
    }

    print(ans);
}
