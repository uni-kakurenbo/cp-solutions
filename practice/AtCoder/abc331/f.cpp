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


#include "data_structure/segment_tree.hpp"
#include "algebraic/rolling_hash.hpp"
#include "algebraic/combined.hpp"

void solve() {
    int n, q; input >> n >> q;
    string s; input >> s;


    lib::segment_tree<
        lib::algebraic::combined<
            lib::algebraic::rolling_hash<false>,
            lib::algebraic::rolling_hash<true>
        >
    > hash(s);


    REP(q) {
        int t; input >> t;
        if(t == 1) {
            int x; char c; input >> x >> c; --x;
            hash[x] = c;
        }
        if(t == 2) {
            int l, r; input >> l >> r; --l;
            debug(hash(l, r).fold());
            print.yesno(hash(l, r).fold()->first == hash(l, r).fold()->second);
        }

        debug(hash);
    }
}
