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

void solve() {
    i32 n, m; input >> n >> m;
    valarray<i32> as(m), bs(m); input >> uni::views::zip(as, bs);
    as -= 1, bs -= 1;

    uni::set<i32> use;
    uni::set<spair<i32>> ans;

    ITR(a, b, uni::views::zip(as, bs)) {
        use.insert(uni::mod(a + b, n));
        ans.emplace(a, b);
    }
    debug(use);

    {
        for(i32 i = 0; use.size() < m; ++i) {
            if(use.contains(i)) continue;
            use.insert(i);
        }
    }

    ITR(v, use) {
        REP(i, n) {
            REP(j, m) {
                ans.emplace(i, uni::mod(v - i, n));
            }
        }
    }
    debug(ans, ans.size());
    assert(ans.ssize() == n * m);

    print(ans.size());
    ITR(a, b, ans) print(a + 1, b + 1);
}
