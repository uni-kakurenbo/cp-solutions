/*
 * @uni_kakurenbo
 * https://github.com/uni-kakurenbo/competitive-programming-workspace
 *
 * CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja
 */
/* #language C++ 23 GCC */
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

#include "data_structure/disjoint_set.hpp"

#include "template/warnings.hpp"
void solve() {
    i32 h, w, k; input >> h >> w >> k;
    vector<i64> r(k), c(k); input >> uni::views::zip(r, c);

    uni::map<spair<i64>, i32> rev;
    REP(i, k) {
        rev[{ r[i], c[i] }] = i;
    }

    uni::disjoint_set ds(k + 2);

    REP(i, k) {
        if(r[i] == 1 || c[i] == w) {
            ds.merge(i, k);
        }
        if(c[i] == 1 || r[i] == h) {
            ds.merge(i, k + 1);
        }

        REP(d, 8) {
            auto [dr, dc] = uni::DIRS8[d];
            auto nr = r[i] + dr, nc = c[i] + dc;

            if(rev.contains({ nr, nc })) {
                ds.merge(i,rev[{ nr, nc }]);
            }
        }
    }

    print.yesno(!ds.same(k, k + 1));
}
