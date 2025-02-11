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

#include "geometry/convex_hull.hpp"

#include "template/warnings.hpp"
void solve() {
    i32 n; input >> n;
    uni::polygon<point> ps(n); input >> ps;

    auto hull = ps.convex_hull<false, true>();

    i64 borders = 0;
    i64 area2 = hull.doubled_area();

    REP(i, 1, hull.size()) {
        borders += std::gcd(hull[i - 1].x() - hull[i].x(), hull[i - 1].y() - hull[i].y());
    }
    debug(area2 - borders);

    i64 inner = 1 + (area2 - borders) / 2;
    print(inner + borders - ps.ssize());
}
