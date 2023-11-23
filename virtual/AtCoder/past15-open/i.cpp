/*
 * @uni_kakurenbo
 * https://github.com/uni-kakurenbo/competitive-programming-workspace
 *
 * CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja
 */
/* #language C++ 20 GCC */
#include "template/standard.hpp"

void solve();

signed main() {
    debug(__cplusplus);
    int $ = 1;
    // std::cin >> $;
    for(int _ = 0; _ < $; ++_) {
        DEBUG("Case: #" + std::to_string(_));
        solve();
    }
    return 0;
}

#include "numeric/divisor_multiple_transform.hpp"

void solve() {
    int n, k; input >> n >> k;
    valarray<int> a(n); input >> a;

    std::valarray<int> cnt(a.max());
    ITRR(v, a) ++cnt[v-1];
    debug(cnt);
    lib::multiple_transform::zeta(ALL(cnt));
    debug(cnt);

    REPD(i, a.max()) {
        if(cnt[i] >= k) {
            print(i + 1);
            return;
        }
    }
}
