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
    valarray<i64> a(n); input >> a;
    int m; input >> m;
    valarray<i64> b(m); input >> b;
    int l; input >> l;
    valarray<i64> c(l); input >> c;

    lib::set<int> can;
    REP(i, n) REP(j, m) REP(k, l) can.insert(a[i] + b[j] + c[k]);

    int q; input >> q;
    REP(q) {
        int x; input >> x;
        print.yesno(can.contains(x));
    }
}
