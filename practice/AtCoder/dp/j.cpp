/*
 * @uni_kakurenbo
 * https://github.com/uni-kakurenbo/competitive-programming-workspace
 *
 * CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja
 */
/* #language C++ 23 GCC */
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
    vector<i64> a(n); input >> a;
    uni::counter cnt(a);

    uni::multi_container<ld, 3> dp(n + 1, n + 1, n + 1, -1);
    auto rec = [&](auto&& self, i64 x0, i64 x1, i64 x2) -> ld {
        if(dp(x0, x1, x2) >= 0) return dp(x0, x1, x2);
        if(x0 == 0 && x1 == 0 && x2 == 0) return 0;

        // debug(x0, x1, x2);

        ld res = 0;

        if(x0 > 0) res += self(self, x0 - 1, x1, x2) * x0;
        if(x1 > 0) res += self(self, x0 + 1, x1 - 1, x2) * x1;
        if(x2 > 0) res += self(self, x0, x1 + 1, x2 - 1) * x2;
        res += n;
        res /= (x0 + x1 + x2);

        return dp(x0, x1, x2) = res;
    };

    print(rec(rec, cnt[1], cnt[2], cnt[3]));
}
