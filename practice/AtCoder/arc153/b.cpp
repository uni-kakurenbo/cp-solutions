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

#include "data_structure/actable_dynamic_sequence.hpp"
#include "data_structure/red_black_tree.hpp"
#include "action/null.hpp"

void solve() {
    int h, w; cin >> h >> w;
    lib::grid<char, string> G(h, w); input >> G;

    lib::actable_dynamic_sequence<lib::actions::null<int>> s(std::views::iota(0, h)), t(std::views::iota(0, w));
    debug(s, t);

    int q; cin >> q;
    REP(q) {
        int a, b; cin >> a >> b;
        s.reverse(0, a), s.reverse(a, h);
        t.reverse(0, b), t.reverse(b, w);
        debug(s, t);
    }

    REP(i, h) {
        REP(j, w) print << G(s[i].val().val(), t[j].val().val());
        print();
    }

    return;
}
