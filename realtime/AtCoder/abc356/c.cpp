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
    i32 n, m, k; input >> n >> m >> k;
    vector<char> r(m);
    vector<vector<i32>> a(m);

    REP(i, m) {
        i32 c; input >> c;
        a[i].resize(c); input >> a[i];
        a[i] -= 1;
        input >> r[i];
    }

    i32 ans = 0;

    REP(s, uni::shiftl(1UL, n)) {
        auto ok = [&]() {
            REP(i, m) {
                i32 cnt = 0;
                ITR(v, a[i]) cnt += uni::bit(s, v);
                if((r[i] == 'o') != (cnt >= k)) {
                    return false;
                }
            }
            return true;
        };
        ans += ok();
    }

    print(ans);
}
