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

#include "numeric/leveler.hpp"
#include "iterable/count_inversion.hpp"

void solve() {
    i32 n; input >> n;
    valarray<i32> l(n), r(n); input >> uni::views::zip(l, r);
    l -= 1;

    valarray p = r - l;
    uni::leveler<i32> level(p);

    ld sum = 0;

    REP(x, level.sup()) {
        auto v = level.revert(x);
        v += l;

        sum += uni::inversion<>::count(v);
    }

    debug(sum, level.sup());
    debug(sum / level.sup());
}
