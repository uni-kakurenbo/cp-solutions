/*
 * @uni_kakurenbo
 * https://github.com/uni-kakurenbo/competitive-programming-workspace
 *
 * CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja
 */
/* #language C++ 20 GCC */
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
#include "data_structure/adaptor/set.hpp"

using mint = uni::modint998244353;

void solve() {
    i32 n, h; input >> n >> h;
    vector<i64> x(n); input >> x;

    uni::disjoint_set ds(n);

    vector<spair<i64>> y;
    ITR(j, v, x | uni::views::enumerate) y.emplace_back(v, j);
    y.sort();

    debug(y);

    vector<mint> ans(n);

    auto merge = [&](auto&& merge, i32 p) -> void {
        auto lower = y.lower_bound(std::make_pair(x[p], 0));
        if(lower != y.begin()) {
            --lower;
            if(!ds.same(p, lower->second)) {
                ds.merge(p, lower->second);
                merge(merge, lower->second);
            }
        }
        auto upper = y.upper_bound(std::make_pair(x[p], 0));
        if(upper != y.end()) {
            if(!ds.same(p, upper->second)) {
                ds.merge(p, lower->second);
                merge(merge, upper->second);
            }
        }
    };

    REP(i, n) {
        merge(merge, i);
        if(ds.same(i, n - 1)) {
            ans[i] = ds.size();
        }
    }
}
