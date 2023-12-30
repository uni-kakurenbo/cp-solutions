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
    valarray<i64> a(k); input >> a;

    multiset<i64> v;
    REP(i, n) {
        v.insert(i);
        v.insert(i);
    }
    ITR(x, a) v.remove(x - 1);
    valarray<i64> u(ALL(v));
    lib::adjacent_difference diff(ALL(u));
    debug(u, diff);

    i64 ans = INF64;

    vector<i64> l(1);
    debug(diff.size());
    REP(i, 0, std::ssize(diff), 2) l.push_back(l.back() + diff[i]);

    vector<i64> r(1);
    REPD(i, k%2, std::ssize(diff), 2) r.push_back(r.back() + diff[i]);
    debug(l, r);
    assert(l.size() == r.size());

    REP(i, l.size()) {
        i64 cur = 0;
        cur += l[i];
        cur += r[r.size()-i-1];
        debug(cur);
        chmin(ans, cur);
    }

    print(ans);
}
