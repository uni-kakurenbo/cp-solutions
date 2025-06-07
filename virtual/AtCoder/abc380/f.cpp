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
    i32 n, m, l; input >> n >> m >> l;
    vector<i64> a(n), b(m), c(l); input >> a >> b >> c;

    auto all = uni::views::concat(a, b, c);

    i32 s = n + m + l;
    auto r = 1U << s;
    auto full = r - 1;

    debug(s, r, full);

    uni::multi_container<i32, 2> dp(r, r, -1);
    auto dfs = [&](auto&& self, auto x, auto t) -> bool {
        if(dp(x, t) >= 0) return dp(x, t);

        bool res = false;

        auto y = full ^ x ^ t;
        assert((x & t) == 0);

        REP(i, s) {
            if(uni::bit(x, i)) {
                auto nt = t | (1U << i);
                res |= self(self, y, nt);
                REP(j, s) {
                    if(uni::bit(t, j) && all[j] < all[i]) res |= self(self, y, nt & ~(1U << j));
                }
            }
        }

        return dp(x, t) = !res;
    };

    u32 x = 0, t = 0;
    REP(i, n) x |= 1U << i;
    REP(i, n + m, s) t |= 1U << i;

    debug(n, m, l, s);

    debug(full, x, t);

    print.conditional(dfs(dfs, x, t), "Aoki", "Takahashi");
}
