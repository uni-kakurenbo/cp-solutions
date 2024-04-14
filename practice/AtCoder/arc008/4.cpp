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

#include "data_structure/dynamic_segment_tree.hpp"
#include "algebraic/affine.hpp"

void solve() {
    i64 n, m; input >> n >> m;

    lib::dynamic_segment_tree<lib::algebraic::affine<double, true>> data(n);

    double min = 1, max = 1;

    REP(m) {
        i64 p;
        double a, b;
        input >> p >> a >> b; --p;

        data[p] = { a, b };

        auto prod = data.fold();
        double val = prod->first + prod->second;

        chmin(min, val);
        chmax(max, val);

        debug(prod, data);
    }

    print(min, max);
}
