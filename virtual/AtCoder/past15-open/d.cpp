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

#include "data_structure/lazy_segment_tree.hpp"
#include "action/range_set_range_min.hpp"

void solve() {
    i64 a, b, c, d, r; input >> a >> b >> c >> d >> r;

    lib::lazy_segment_tree<lib::actions::range_set_range_min<int>> can(a + c + r + 10, 0);

    int p = a, q = a + r;
    REP(x, 0, a + c + r, d) {
        if(x > b) {
            p = c, q = c + r;
        }

        if(x < q) {
            can(lib::max(p, x), lib::min(a + c + r + 10, q)) += true;
        }
    }
    debug(can);

    print.yesno(can(c, c + r).fold().val() > 0);
}
