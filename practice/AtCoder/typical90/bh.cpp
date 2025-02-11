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

#include "iterable/longest_increasing_subsequence.hpp"

void solve() {
    i32 n; input >> n;
    vector<i32> a(n); input >> a;

    uni::lis<true, i32> forward(a), backward(uni::reversed(a));

    REP(i, n - 1) chmax(forward.positions[i + 1], forward.positions[i]);
    REP(i, n - 1) chmax(backward.positions[i + 1], backward.positions[i]);

    debug(forward.positions, backward.positions);

    i32 ans = 0;

    REP(i, n) {
        chmax(ans, forward.positions[i] + backward.positions[n - i - 1] + 1);
    }

    print(ans);
}
