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

using mint = lib::modint998244353;

void solve() {
    int n, k; input >> n >> k;
    string s; input >> s;
    valarray<int> a(n);
    REP(i, n) a[i] = s[i] - 'A';

    lib::valarray<mint> dp(n);

    array<int, 3> cnt; cnt.fill(0);
    mint ans = 0;
    REP(i, n) {
        ans += (i - cnt[a[i]]);
        debug(ans);
        cnt[a[i]]++;
    }
    debug(ans);
}
