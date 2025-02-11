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


constexpr string RGB = "RGB";

#include "hash/sequence_hasher.hpp"

#include "template/warnings.hpp"
void solve() {
    i32 n; input >> n;
    string s, t; input >> s >> t;

    auto rgb = RGB | uni::views::cyclic;

    uni::sequence_hasher hash_s(s);

    i32 cnt = 0;

    REP(p, 3) {
        auto r = t;
        std::ranges::replace(r, rgb[p + 1], 'X');
        std::ranges::replace(r, rgb[p + 2], rgb[p + 1]);
        std::ranges::replace(r, 'X', rgb[p + 2]);
        debug(s, p, r);

        uni::sequence_hasher hash_r(r);
        REP(k, n) {
            debug(k, hash_s(0, n - k), hash_r(k, n));
            cnt += hash_s(0, n - k) == hash_r(k, n);
        }
        REP(k, -n + 1, 0) {
            cnt += hash_s(-k, n) == hash_r(0, n + k);
        }
    }

    print(cnt);
}
