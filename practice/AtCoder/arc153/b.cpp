/*
 * @uni_kakurenbo
 * https://github.com/uni-kakurenbo/competitive-programming-workspace
 *
 * CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja
 */
/* #language C++ GCC */
/* #region template */
#include <bits/stdc++.h>
using namespace std;

#include "template.hpp"
/* #endregion */

#include "grid.hpp"

#include "data_structure/implicit_treap.hpp"
#include "data_structure/range_action/null.hpp"

signed main() {
    int h, w; cin >> h >> w;
    lib::grid<char,string> G(h, w); G.read();

    lib::implicit_treap<lib::actions::null<int>> s, t;

    REP(i, h) s.push_back(i);
    REP(i, w) t.push_back(i);
    debug(s, t);

    int q; cin >> q;
    REP(q) {
        int a, b; cin >> a >> b;
        s.reverse(0, a), s.reverse(a, h);
        t.reverse(0, b), t.reverse(b, w);
        debug(s, t);
    }

    REP(i, h) {
        REP(j, w) print << G(s[i], t[j]);
        print();
    }

    return 0;
}
