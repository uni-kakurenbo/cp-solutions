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

#include "data_structure/lazy_segment_tree.hpp"
#include "action/range_add.hpp"

void solve() {
    i32 n, q; input >> n >> q;
    lib::lazy_segment_tree<lib::actions::range_add<i64>> data(({
        vector<i32> init(n); input >> init;
        init;
    }));
    debug(data);

    i64 ans = 0;
    REP(i, 1, n) ans += std::abs(data[i].val().val() - data[i - 1].val().val());

    REP(q) {
        i32 l, r, v; input >> l >> r >> v; --l;
        if(l >= 1) ans -= std::abs(data[l].val().val() - data[l - 1].val().val());
        if(r < n) ans -= std::abs(data[r].val().val() - data[r - 1].val().val());
        data(l, r) += v;
        if(l >= 1) ans += std::abs(data[l].val().val() - data[l - 1].val().val());
        if(r < n) ans += std::abs(data[r].val().val() - data[r - 1].val().val());
        print(ans);
    }
}
