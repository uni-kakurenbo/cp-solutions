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

using mint = lib::static_modint_64bit<(1L << 61) - 1>;

void solve() {
    int n; input >> n;
    valarray<mint> a(n);
    REP(i, n) {
        string s; input >> s;
        ITRR(d, s) {
            a[i] *= 10;
            a[i] += d - '0';
        }
    }

    lib::map<u64, int> cnt;
    ITR(v, a) cnt[v.val()]++;

    debug(a, cnt);

    i64 ans = 0;
    REP(i, n) REP(j, n) {
        ans += cnt[(a[i] * a[j]).val()];
    }

    print(ans);
}
