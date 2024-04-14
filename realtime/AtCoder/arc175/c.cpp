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
        debug_("Case: #" + std::to_string(_));
        solve();
    }
    return 0;
}

void solve() {
    int n; input >> n;
    valarray<i64> l(n), r(n); input >> lib::views::zip(l, r);

    valarray<i64> a(n, -1);

    REP(i, 1, n) {
        if(r[i - 1] <= l[i]) {
            a[i - 1] = r[i - 1];
            a[i] = l[i];
        }
        else if(l[i - 1] >= r[i]) {
            a[i - 1] = l[i - 1];
            a[i] = r[i];
        }
    }

    i64 cur = -1;

    REP(i, n) {
        if(a[i] >= 0) cur = a[i];
        if(a[i] == -1) {
            cur = std::clamp(cur, l[i], r[i]);
            a[i] = cur;
        }
    }

    print(a);


    debug(a);
}
