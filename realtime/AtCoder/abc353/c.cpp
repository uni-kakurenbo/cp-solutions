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

constexpr i64 M = 100'000'000;

void solve() {
    i64 n; input >> n;
    vector<i64> a(n); input >> a;
    uni::array<i64, M> cnt{};
    ITR(v, a) cnt[v]++;
    REPD(i, 1, M) cnt[i - 1] += cnt[i];

    i64 sum = a.sum() * (n - 1);
    i64 ex = 0;

    ITR(v, a) {
        debug(v, M - v, cnt[M - v]);
        ex += cnt[M - v] - (v >= M - v);
    }
    ex /= 2;
    debug(sum, ex);

    print(sum - ex * M);
}
