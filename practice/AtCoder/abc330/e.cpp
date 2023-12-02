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

#include "data_structure/adapter/set.hpp"

void solve() {
    int n, q; input >> n >> q;
    valarray<i64> a(n); input >> a;

    lib::multiset_adapter set(n + 2);

    ITRR(v, a) chmin(v, n + 1);
    ITR(v, a) set.insert(v);
    debug(set);

    REP(q) {
        int i, x; input >> i >> x; --i;
        chmin(x, n + 1);

        set.remove(a[i]);
        set.insert(a[i] = x);

        print(set.mex());
        debug(set);
    }
}
