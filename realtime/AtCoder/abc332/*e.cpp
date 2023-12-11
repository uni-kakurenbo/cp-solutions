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
    int n, d; input >> n >> d;
    vector<i64> w(n); input >> w;

    auto dfs = [&](auto&& dfs, vector<i64> a, int cnt) -> spair<ld> {
        int m = a.size();

        if(cnt == k) {
            ld e2 = 0, e = 0;
            REP(i, m) e2 += 1.0 * a[i] * a[i], e = a[i];
            return { e2 - e * e, e };
        }

        ld va = INF<ld>;
        ld ea;

        REP(s, 1, 1 << m) {
            vector<i64> x, y;
            REP(i, m) {
                if((s >> i) & 1) x.push_back(a[i]);
                else y.push_back(a[i]);
            }
            auto [ vx, ex ] = dfs(dfs, x, cnt + 1);
            auto [ vy, ey ] = dfs(dfs, y, cnt + 1);
            auto ex2 = vx * vx + ex * ex;
            auto ey2 = vy * vy + ey * ey;

            auto e2 = (ex2 * x.size() + ey2 * y.size()) / (x.size() + y.size());
            auto e = (ex * x.size() + ey * y.size()) / (x.size() + y.size());

            auto v = e2 - e * e;

            if(chmin(va, v)) {
                ea = e;
            };
        }

        return { va, ea };
    };

    print(dfs(dfs, w).first);
}
