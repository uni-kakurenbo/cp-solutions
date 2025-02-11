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
    i32 n, k; i64 p; input >> n >> k >> p;
    vector<i64> a(n); input >> a;

    array<vector<vector<i64>>, 2> s;
    REP(i, 2) s[i].resize(k + 1);

    i32 m = uni::div_ceil(n, 2);

    REP(x, 1UL << m) {
        if(std::popcount(x) > k) continue;

        i64 sum = 0;
        REP(i, m) {
            if(uni::bit(x, i)) sum += a[i];
        }

        s[0][std::popcount(x)].emplace_back(sum);
    }

    m = n - m;
    REP(x, 1UL << m) {
        if(std::popcount(x) > k) continue;

        i64 sum = 0;
        REP(i, m) {
            if(uni::bit(x, i)) sum += a[n - m + i];
        }

        s[1][std::popcount(x)].emplace_back(sum);
    }

    i64 ans = 0;

    FOR(i, k) {
        s[1][k - i].sort();

        ITR(v, s[0][i]) {
            ans += s[1][k - i].upper_bound(p - v) - s[1][k - i].begin();
        }
    }

    print(ans);
}
