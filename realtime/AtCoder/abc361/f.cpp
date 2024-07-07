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

#include "numeric/divisor_multiple_transform.hpp"

#include "template/warnings.hpp"
void solve() {
    i64 n; input >> n;

    vector<i64> cnt(60);
    for(i64 i = 2; (1L << i) <= n; i++) {
        cnt[i] = uni::kth_root_floor(n,  i) - 1;
    }

    uni::multiple_transform::mobius(cnt);

    print(1 - cnt[1]);
}
