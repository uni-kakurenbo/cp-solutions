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
    i32 n; input >> n;
    valarray<i32> a(n); input >> a;
    a -= 1;
    valarray<i32> inv(a);
    REP(i, n) inv[a[i]] = i;

    vector<spair<i32>> ans;

    auto swap = [&](i32 i, i32 j) {
        std::swap(a[i], a[j]);
        inv[a[j]] = j;
        inv[a[i]] = i;
    };

    REP(i, n) {
        if(a[i] != i) {
            ans.emplace_back(i + 1, inv[i] + 1);
            swap(i, inv[i]);
        }

        debug(a, inv);
    }

    print(ans.size());
    print(ans);
}
