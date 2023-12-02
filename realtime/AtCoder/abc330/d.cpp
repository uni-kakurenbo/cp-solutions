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
    lib::grid<char,string> G(n, n); input >> G;

    using point = spair<int>;
    i64 ans = 0;

    valarray<int> cnt_v(n), cnt_h(n);
    REP(i, n) REP(j, n) {
        cnt_v[i] += G(i, j) == 'o';
        cnt_h[j] += G(i, j) == 'o';
    }

    REP(i, n) REP(j, n) {
        if(G(i, j) != 'o') continue;
        ans += 1LL * (cnt_v[i] - 1) * (cnt_h[j] - 1);
    }

    print(ans);
}
