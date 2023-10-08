/*
 * @uni_kakurenbo
 * https://github.com/uni-kakurenbo/competitive-programming-workspace
 *
 * CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja
 */
/* #language C++ 20 GCC */
/* #region template */
#include <bits/stdc++.h>

#include "template.hpp"
/* #endregion */

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
    i64 xp, yp, xt, yt, xg, yg; input(xp, yp, xt, yt, xg, yg);
    debug(xp, yp, xt, yt, xg, yg);

    auto d = [&](i64 x0, i64 y0, i64 x1, i64 y1) {
        return std::abs(x0 - x1) + std::abs(y0 - y1);
    };

    auto xx = [&](i64 ix, i64 iy, i64 tx, i64 ty) {
        i64 pans = 0;
        if(xg == tx) {
            // do nothing
        }
        else if(xg < tx) {
            pans += d(tx + 1, ty, ix, iy);
            if(iy == ty and ix < tx) pans += 2;
            ix = xg + 1;
            iy = ty;
        }
        else {
            pans += d(tx - 1, ty, ix, iy);
            if(iy == ty and tx < ix) pans += 2;
            ix = xg - 1;
            iy = ty;
        }
        pans += std::abs(tx - xg);
        tx = xg;
        return std::make_tuple(pans, ix, iy, tx, ty);
    };

    auto yy = [&](i64 ix, i64 iy, i64 tx, i64 ty) {
        i64 pans = 0;
        if(yg == ty) {
            // do nothing
        }
        else if(yg < ty) {
            pans += d(tx, ty + 1, ix, iy);
            if(ix == tx and iy < ty) pans += 2;
            iy = yg + 1;
            ix = tx;
        }
        else {
            pans += d(tx, ty - 1, ix, iy);
            if(ix == tx and ty < iy) pans += 2;
            iy = yg - 1;
            ix = tx;
        }
        pans += std::abs(ty - yg);
        ty = yg;
        return std::make_tuple(pans, ix, iy, tx, ty);
    };

    i64 ans = INF64;
    {
        i64 pans = 0, x, y, tx, ty;
        std::tie(pans, x, y, tx, ty) = xx(xp, yp, xt, yt);
        pans += std::get<0>(yy(x, y, tx, ty));
        chmin(ans, pans);
    }
    {
        i64 pans = 0, x, y, tx, ty;
        std::tie(pans, x, y, tx, ty) = yy(xp, yp, xt, yt);
        pans += std::get<0>(xx(x, y, tx, ty));
        chmin(ans, pans);
    }
    print(ans);
}
