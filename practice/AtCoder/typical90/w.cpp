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

#include "adaptor/auto_expander.hpp"

using mint = uni::modint1000000007;

void solve() {
    i32 h, w; input >> h >> w;
    uni::grid<char> c(h, w); input >> c;
    debug(c);

    vector<u32> valid;

    REP(s, 1u << (w + 1)) {
        if(
            std::ranges::count_if(
                std::views::iota(0, w),
                [&](i32 i) { return uni::bit(s, i) && uni::bit(s, i + 1); }
            ) <= 1
        ) {
            // debug(bitset<8>(s));
            valid.push_back(s);
        }
    }
    debug(valid.size());

    static array<i32, 33554432> rev;
    ITR(i, v, valid | uni::views::enumerate) rev[v] = i;

    vector<mint> dp(valid.size());
    dp[0] = 1;

    REP(i, h) REP(j, w) {
        vector<mint> nxt(valid.size());

        ITR(t, s, valid | uni::views::enumerate) {
            if(dp[t] == 0) continue;

            u32 ns = uni::clear_higher_bits(s << 1, w + 1);
            debug(bitset<8>(s), bitset<8>(ns), t, id, dp[t]);
            nxt[rev[ns]] += dp[t];

            if(c(i, j) == '#') continue;
            if(i > 0) {
                if(j > 0 && uni::bit(s, w)) continue;
                if(uni::bit(s, w - 1)) continue;
                if(j < w - 1 && uni::bit(s, w - 2)) continue;
            }
            if(j > 0 && uni::bit(s, 0)) continue;

            debug_("can");

            nxt[rev[ns | 1]] += dp[t];
        }

        dp = std::move(nxt);
    }

    print(dp.sum());
}
