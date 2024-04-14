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

#include "data_structure/dynamic_sequence.hpp"
#include "data_structure/dynamic_sequence.hpp"
#include "data_structure/red_black_tree.hpp"

void solve() {
    int n; input >> n;
    string s; input >> s;

    lib::dynamic_sequence<char, lib::persistent_red_black_tree_context<lib::i32>> data(s);

    int q; input >> q;
    REP(q) {
        int l, r, p; input >> l >> r >> p;
        data.insert(p, data(l, r).clone());
        if(data.size() >= n) data = data(0, n).clone();
        debug(data);
    }

    print(data.to<std::string>());
}
