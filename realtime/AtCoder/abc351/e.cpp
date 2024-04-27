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

using point = uni::point<i64>;

void solve() {
    i32 n; input >> n;
    vector<point> ps(n); input >> ps;
    array<vector<point>, 2> qs;

    ITR(p, ps) {
        i64 v = p.x() + p.y();
        qs[v % 2].push_back(p);
    }
    ITRR(p, qs[1]) p -= point(1, 0);

    REP(d, 2) {
        ITRR(p, qs[d]) {
            i64 x = (p.x() + p.y()) / 2;
            i64 y = (p.x() - p.y()) / 2;
            p = { x, y };
        }

    }
    debug(qs);

    auto distsum = [&](auto& vs) {
        vs.sort();

        i64 res = 0, sum = 0;
        REP(i, vs.ssize()) {
            res += (vs[i] * i - sum);
            sum += vs[i];
        }

        return res;
    };

    i64 ans = 0;

    REP(d, 2) {
        vector<i64> xs, ys;
        ITR(p, qs[d]) {
            xs.push_back(p.x());
            ys.push_back(p.y());
        }

        ans += distsum(xs);
        ans += distsum(ys);
    }

    print(ans);
}
