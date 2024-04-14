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

void solve() {
    int n, q; input >> n >> q;
    lib::dynamic_sequence<int> a(({
        vector<int> v(n); input >> v;
        v;
    }));
    debug(a);

    REP(q) {
        int t, x, y; input >> t >> x >> y; --x, --y;
        if(t == 1) {
            int temp = a[x];
            a[x] = a[y].val();
            a[y] = temp;
        }
        if(t == 2) {
            a.rotate_right();
        }
        if(t == 3) {
            print(a[x]);
        }
    }
}
