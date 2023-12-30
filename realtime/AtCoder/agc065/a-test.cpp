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

void solve() {
    int n, k; input >> n >> k;
    valarray<i64> a(n); input >> a;
    a.sort();

    i64 max = -1;

    do {
        // DEBUG("-----");
        // debug(a);
        valarray<i64> diff(n - 1);
        REP(i, n-1) diff[i] = a[i+1] - a[i];
        // debug(diff);
        ITRR(v, diff) v = lib::mod(v, k);
        // debug(diff);
        // debug(max, diff.sum());
        if(max <= diff.sum()) {
            chmax(max, diff.sum());
            debug(a);
            debug(max, diff);
        }
        // debug(chmax(max, diff.sum()), max == diff.sum());
    } while(std::ranges::next_permutation(a).found);

    print(max);
}
