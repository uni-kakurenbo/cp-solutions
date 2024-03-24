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
    string s; input >> s;
    vector<i64> c(n); input >> c;

    std::bitset<200'000> st;
    REP(i, n) if(s[i] == '1') st.set(i);

    // std::bitset<200'000> mask(s);
    // REP(i, 200'000, 2) mask.set(i);

    array<vector<i64>, 2> l, r;
    REP(x, 2) {
        l[x].resize(n + 1), r[x].resize(n + 1);

        l[x][0] = 0, r[x][n] = 0;

        REP(i, n) l[x][i + 1] = l[x][i] + (st[i] ^ x ^ (i % 2)) * c[i];
        REPD(i, n) r[x][i] = r[x][i + 1] + (st[i] ^ x ^ (i % 2) ^ (n % 2) ^ 1) * c[i];
    }
    // print(l[0]), print(l[1]);
    // print(r[0]), print(r[1]);

    auto cost = [&](int x, int i) -> i64 {
        auto left = l[(i % 2) ^ x][i];
        auto right = r[((n - i) % 2) ^ x][i];
        if(i == 7) debug(i, left, right);
        return left + right;
    };

    i64 ans = INF64;

    REP(i, 1, n) {
        chmin(ans, cost(0, i));
        chmin(ans, cost(1, i));
    }

    print(ans);
}
