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

void solve() {
    int n, q; input >> n >> q;
    string s; input >> s;

    valarray<int> sum(n + 1);
    REP(i, n-1) {
        sum[i+1] = sum[i];
        if(s[i] == s[i+1]) sum[i+1] += 1;
    }
    debug(sum);

    REP(q) {
        int l, r; input >> l >> r; --l, --r;
        print(sum[r] - sum[l]);
    }
}
