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

#include "template/warnings.hpp"
void solve() {
    i32 n; input >> n;
    vector<spair<i64>> ps(n); input >> ps;
    ITRR(x, y, ps) y *= -1;
    debug(ps);
    vector<i32> inds(n); std::iota(ALL(inds), 0);

    inds.sort([&](i32 i, i32 j) { return ps[i] > ps[j]; });
    i32 max = -INF32;
    vector<i32> ans;
    ITR(i, inds) {
        debug(ps[i]);
        if(chmax(max, ps[i].second)) {
            ans.push_back(i);
        }
    }

    ans.sort();
    print(ans.size());
    print(ans + 1);
}
