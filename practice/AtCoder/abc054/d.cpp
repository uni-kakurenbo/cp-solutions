/*
 * @uni_kakurenbo
 * https://github.com/uni-kakurenbo/competitive-programming-workspace
 *
 * CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja
 */
/* #language C++ GCC */
/* #region template */
#include <bits/stdc++.h>

#include "template.hpp"
/* #endregion */

void solve();

signed main() {
    int $ = 1;
    // std::cin >> $;
    for(int _ = 0; _ < $; ++_) {
        DEBUG("Case: #" + std::to_string(_));
        solve();
    }
    return 0;
}

using medicine = tuple<int,int,int>;

inline medicine operator+(const medicine& p, const medicine& q) {
    return { std::get<0>(p) + std::get<0>(q), std::get<1>(p) + std::get<1>(q), std::get<2>(p) + std::get<2>(q) };
}

void solve() {
    int n, ma, mb; cin >> n >> ma >> mb;
    valarray<medicine> abc(n); input >> abc;
    debug(abc);

    vector<medicine> p, q;
    REP(i, n) {
        if(i%2) p.push_back(abc[i]);
        else q.push_back(abc[i]);
    }

    i64 ans = INF64;

    map<i64,i64> s, t;
    s.set_default(INF64), t.set_default(INF64);

    REP(x, 1, 1 << p.size()) {
        medicine now;
        REP(i, p.size()) if((x >> i) & 1) now = now + p[i];
        i64 m = std::get<0>(now) * mb - std::get<1>(now) * ma;
        if(m == 0) chmin(ans, std::get<2>(now));
        else chmin(s[m], std::get<2>(now));
    }
    REP(x, 1, 1 << q.size()) {
        medicine now;
        REP(i, q.size()) if((x >> i) & 1) now = now + q[i];
        i64 m = std::get<0>(now) * mb - std::get<1>(now) * ma;
        if(m == 0) chmin(ans, std::get<2>(now));
        else chmin(t[m], std::get<2>(now));
    }
    debug(s, t);

    ITR(v, c, s) {
        debug(v, c);
        if(t.contains(-v)) chmin(ans, c + t[-v]);
    }

    print(lib::to_optional_if_or_over(ans, INF64).value_or(-1));
}
