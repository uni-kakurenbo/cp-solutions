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
    vector<i64> a(n), w(n); input >> a >> w; a -= 1;
    uni::inverse inv(a);
    debug(inv);

    i64 ans = 0;

    ITR(i, v, inv) {
        i32 max = 0;
        i64 sum = 0;
        ITR(j, v) chmax(max, w[j]), sum += w[j];
        ans += sum - max;
    }

    print(ans);
}