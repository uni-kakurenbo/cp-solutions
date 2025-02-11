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

using point = uni::point<i64>;

void solve() {
    i32 n, q; input >> n >> q;
    vector<point> ps(n); input >> ps;
    debug(ps);
    ITRR(p, ps) p.rotate_quarter();

    point xmin(INF32, 0), xmax(-INF32, 0), ymin(0, INF32), ymax(0, -INF32);
    REP(i, n) {
        if(ps[i].x() < xmin.x()) xmin = ps[i];
        if(ps[i].y() < ymin.y()) ymin = ps[i];
        if(ps[i].x() > xmax.x()) xmax = ps[i];
        if(ps[i].y() > ymax.y()) ymax = ps[i];
    }

    REP(q) {
        i32 i; input >> i; --i;
        print(
            uni::max(
                uni::chebyshev_distance(ps[i], xmin),
                uni::chebyshev_distance(ps[i], xmax),
                uni::chebyshev_distance(ps[i], ymin),
                uni::chebyshev_distance(ps[i], ymax)
            )
        );
    }
}
