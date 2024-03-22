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

#include "data_structure/dynamic_set.hpp"

void solve() {
    int q; input >> q;

    lib::dynamic_set<lib::i32, lib::treap_context<lib::i32>> data;

    REP(q) {
        int t; input >> t;
        if(t == 1) {
            i32 x; input >> x;
            data.insert(x);
        }
        if(t == 2) {
            i32 x; input >> x; --x;
            auto v = data[x];
            print(v);
            data.erase(v);
        }
        debug(data);
    }
}
