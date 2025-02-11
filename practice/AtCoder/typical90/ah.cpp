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
    i32 n, k; input >> n >> k;
    vector<i32> a(n); input >> a;

    map<i32, i32> cnt;

    i64 ans = 0;

    i32 l = 0, r = 0;
    while(l < n) {
        if(r == n || cnt.ssize() > k) {
            if(--cnt[a[l]] == 0) cnt.erase(a[l]);
            ++l;
        }
        else {
            ++cnt[a[r++]];
        }
        if(cnt.ssize() <= k) chmax(ans, r - l);
    }

    print(ans);
}
