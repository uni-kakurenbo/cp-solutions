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

#include "hash/hashed_set.hpp"

void solve() {
    int n; input >> n;
    valarray<i64> a(n), b(n); input >> a >> b;

    lib::hashed_set<int> u, v;

    valarray<i64> hash_a(n), hash_b(n);
    REP(i, n) {
        u.insert(a[i]), v.insert(b[i]);
        hash_a[i] = u.get();
        hash_b[i] = v.get();
    }

    int q; input >> q;
    REP(q) {
        int x, y; input >> x >> y; --x, --y;
        print.yesno(hash_a[x] == hash_b[y]);
    }
}
