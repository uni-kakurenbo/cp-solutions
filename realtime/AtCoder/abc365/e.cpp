/*
 * @uni_kakurenbo
 * https://github.com/uni-kakurenbo/competitive-programming-workspace
 *
 * CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja
 */
/* #language C++ 20 GCC */
// #define DEBUGGER_ENABLED

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

#include "template/warnings.hpp"
void solve() {
    i32 n; input >> n;
    vector<u64> a(n); input >> a;

    i64 ans = 0;

    REP(d, 62) {
        debug(d);
        vector<i64> bits(n);
        REP(i, n) bits[i] = uni::bit(a[i], d);
        debug(bits);

        vector<i64> cum(n + 1);
        REP(i, n) cum[i + 1] = (cum[i] + bits[i]) % 2;
        debug(cum);

        uni::counter cnt(cum);
        auto ps = cnt[0] * cnt[1] - bits.sum();
        debug(cnt, ps);

        ans += ps * (1ul << d);
    }

    print(ans);
}
