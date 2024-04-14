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

#include "data_structure/disjoint_set_union.hpp"

void solve() {
    i32 h, w; input >> h >> w;
    i32 q; input >> q;

    lib::grid<int> grid(h, w);
    lib::dsu ds(h * w);

    REP(q) {
        i32 t; input >> t;
        if(t == 1) {
            i32 r, c; input >> r >> c; --r, --c;
            grid(r, c) = 1;
            ITR(rr, cc, grid.vicinities4(r, c)) {
                if(grid(rr, cc)) ds.merge(grid.id(r, c), grid.id(rr, cc));
            }
        }
        if(t == 2) {
            i32 ra, ca, rb, cb; input >> ra >> ca >> rb >> cb; --ra, --ca, --rb, --cb;
            print.yesno(grid(ra, ca) && grid(rb, cb) && ds.same(grid.id(ra, ca), grid.id(rb, cb)));
        }
    }
}
