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
#include "utility/timer.hpp"

using mint = lib::static_modint_64bit<(1UL << 61) - 1>;
using point = lib::point<mint>;

void solve() {
    lib::timer timer(1000);
    int n; input >> n;

    valarray<point> xy(n);
    valarray<i64> score(n);

    ITRR(v, xy) {
        mint x, y; input >> x >> y;
        v = { x, y };
    }

    auto div = [&](mint x, mint y) -> mint {
        if(y == 0) return INF64;
        return x / y;
    };

    // REP(i, n) {
    //     lib::unordered_map<i64, i64> mp;

    //     REP(j, n) {
    //         if(i == j) continue;
    //         mp[div(xy[i].y() - xy[j].y(), xy[i].x() - xy[j].x()).val()] += 1;
    //     }

    //     ITR(v, c, mp) {
    //         score[i] += c - 1;
    //     }
    // }

    // debug(score);

    i64 ans = 0;

    vector<int> ind(n); std::iota(ALL(ind), 0);

    DEBUG {
        REP(i, n) REP(j, i+1, n) {
            debug(i, j);
            debug(div(xy[i].y() - xy[j].y(), xy[i].x() - xy[j].x()));
        }
    }

    while(!timer.expired()) {
        std::shuffle(ALL(ind), lib::randi32);
        debug(ind);

        valarray<bool> used(n);
        i64 pro = 0;

        REP(_i, n) {
            bool found = false;
            int i = ind[_i];
            if(used[i]) continue;
            REP(_j, _i, n) {
                int j = ind[_j];
                if(i == j) continue;
                if(used[j]) continue;
                REP(_k, _j, n) {
                    int k = ind[_k];

                    if(i == k) continue;
                    if(j == k) continue;
                    if(used[k]) continue;

                    mint a = div(xy[i].y() - xy[j].y(), xy[i].x() - xy[j].x());
                    mint b = div(xy[i].y() - xy[k].y(), xy[i].x() - xy[k].x());

                    if(a != b && a != -b) {
                        // debug(i, j, k);
                        // debug(xy[i], xy[j], xy[k]);
                        used[i] = used[j] = used[k] = true;
                        found = true;
                        pro += 1;
                        break;
                    }
                }
                if(found) break;
            }
        }

        chmax(ans, pro);
    }

    print(ans);
}
