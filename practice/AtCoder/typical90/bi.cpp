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
    int q; input >> q;

    std::deque<int> deq;

    REP(q) {
        int t, x; input >> t >> x;
        if(t == 1) {
            deq.push_front(x);
        }
        if(t == 2) {
            deq.push_back(x);
        }
        if(t == 3) {
            print(deq[x-1]);
        }
    }
}
