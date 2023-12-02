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

#include "numeric/boundary_seeker.hpp"

void solve() {
    // 縮める: 辺上の点をすべて動かす

    int n, k; input >> n >> k;
    valarray<i64> x(n), y(n);
    input >> lib::views::zip(x, y);

    map<i64,int> xs, ys;
    REP(i, n) {
        ++xs[x[i]];
        ++ys[y[i]];
    }

    while(k >= 0) {
        array<int> costs;
        {
            auto mx = std::ranges::prev(xs.end());
            auto my = std::ranges::prev(xs.end());
            i64 lx = mx->first - std::ranges::prev(mx)->first;
            i64 ly = my->first - std::ranges::prev(my)->first;
            if(lx < ly) {
                len * mx->second;
            }
        }
    }
}
