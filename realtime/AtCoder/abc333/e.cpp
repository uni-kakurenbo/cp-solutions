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
    int n; input >> n;

    lib::map<int, priority_queue<i64>> pq;

    i64 cnt = 0;

    std::vector<int> used;
    std::vector<spair<int>> tx;

    REP(n) {
        int t, x; input >> t >> x;
        tx.emplace_back(t, x);
        if(t == 1) {
            pq[x].emplace(cnt++);
        }
        if(t == 2) {
            if(pq[x].empty()) {
                print(-1);
                return;
            }
            auto t0 = pq[x].top(); pq[x].pop();
            used.push_back(t0);
        }
    }

    std::vector<int> ans(cnt);
    ITR(t, used) ans[t] = 1;

    i64 cr = 0;
    i64 k = 0;

    cnt = 0;
    ITR(t, x, tx) {
        if(t == 1) {
            if(ans[cnt++] == 1) {
                chmax(k, ++cr);
            }
        }
        if(t == 2) {
            cr--;
        }
    }

    print(k);
    print(ans);
}
