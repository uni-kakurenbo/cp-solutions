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

#include <atcoder/twosat>

void solve() {
    int h, w; input >> h >> w;
    lib::grid<int> a(h, w), b(h, w); input >> a >> b;

    REP(bit, 30) {
        atcoder::two_sat sat(h + w);
        REP(i, h) REP(j, w) {
            if(b(i, j) < 0) continue;
            if(((a(i, j) >> bit) & 1) == ((b(i, j) >> bit) & 1)) {
                sat.add_clause(i, false, h + j, true);
                sat.add_clause(i, true, h + j, false);
            }
            else {
                sat.add_clause(i, false, h + j, false);
                sat.add_clause(i, true, h + j, true);
            }
        }
        if(not sat.satisfiable()) {
            print.no();
            return;
        }
    }

    print.yes();
}
