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
    i64 n, m; input >> n >> m;
    // 地上: a * (b - 1) ; 1 回なげると a 得
    // 空中: a * b ; b = 1 なら 1 回投げて a 得, b > 1 なら 1 回投げて 2 * a 得した上で 地上 に

    vector<spair<i64>> que;

    i64 ans = 0;

    REP(i, n) {
        i64 a, b, x; input >> a >> b >> x;
        ans += a * (b - !x);
        if(x == 0) {
            que.emplace_back(a, b - 1);
        }
        else {
            if(b == 1) que.emplace_back(a, 1);
            else {
                que.emplace_back(2 * a, 1);
                que.emplace_back(a, b - 2);
            }
        }
    }

    que.sort();

    while(not que.empty() and m > 0) {
        auto [ p, t ] = que.back(); que.pop_back();
        i64 take = lib::min(m, t);
        ans -= p * take;
        m -= take;
    }

    print(ans);
}
