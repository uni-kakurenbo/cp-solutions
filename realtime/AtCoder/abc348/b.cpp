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

#include "include/geometries.hpp"

using point = lib::point<i128>;

void solve() {
    int n; input >> n;
    vector<point> ps(n); input >> ps;

    vector<int> inds(n); std::iota(ALL(inds), 0);
    REP(i, n) {
        inds.sort();
        inds.stable_sort([&](int p, int q) {
            return lib::squared_distance(ps[p], ps[i]) > lib::squared_distance(ps[q], ps[i]);
        });
        print(inds[0] + 1);
    }
}
