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
    int n, t; input >> n >> t;
    valarray<int> a(t);
    valarray<i64> b(t);
    input >> lib::views::zip(a, b);
    a -= 1;

    valarray<i64> point(n);
    lib::map<i64, int> cnt;
    cnt[0] = n;

    REP(i, t) {
        cnt[point[a[i]]]--;
        if(cnt[point[a[i]]] == 0) cnt.erase(point[a[i]]);

        point[a[i]] += b[i];
        cnt[point[a[i]]]++;

        print(cnt.size());
    }
}
