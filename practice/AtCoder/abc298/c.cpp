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
        // debug_("Case: #" + std::to_string(_));
        solve();
    }
    return 0;
}


void solve() {
    int n, q; input >> n >> q;

    vector<lib::multiset<int>> cards(n);
    std::array<lib::set<int>, 200000> boxes;

    // debugger::dump_wrapper{}(cards[0]);
    REP(q) {
        int t; input >> t;
        if(t == 1) {
            int i, j; input >> i >> j;
            cards[j - 1].insert(i);
            boxes[i - 1].insert(j);
        }
        if(t == 2) {
            int i; input >> i; --i;
            print(cards[i]);
        }
        if(t == 3) {
            int i; input >> i; --i;
            print(boxes[i]);
        }

        debug(cards);
    }
}
