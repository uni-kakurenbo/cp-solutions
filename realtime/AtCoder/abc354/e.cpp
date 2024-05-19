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
    vector<i32> a(n), b(n); input >> uni::views::zip(a, b);

    static array<u32, 1UL << 20> memo;
    memo.fill(INF32);

    auto grundy = [&](auto& _f, u32 bits) -> u64 {
        if(memo[bits] != INF32) return memo[bits];

        std::vector<i32> res;

        REP(i, n) {
            if(uni::bit(bits, i)) continue;
            REP(j, i + 1, n) {
                if(uni::bit(bits, j)) continue;
                if(a[i] != a[j] && b[i] != b[j]) continue;
                res.push_back(_f(_f, uni::set_bit(uni::set_bit(bits, i), j)));
            }
        }

        return memo[bits] = uni::mex(res);
    };

    print(grundy(grundy, 0) == 0 ? "Aoki" : "Takahashi");
    // debug(memo);
}
