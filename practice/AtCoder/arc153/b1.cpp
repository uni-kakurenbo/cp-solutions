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

signed main() {
    int h, w; cin >> h >> w;
    lib::grid<char,string> G(h, w); input >> G;

    int q; cin >> q;
    int i = 0, j = 0;
    REP(q) {
        int a, b; cin >> a >> b;
        if(i < a) i = a - i - 1;
        else i = a + h - i - 1;
        if(j < b) j = b - j - 1;
        else j = b + w - j - 1;
        debug(i, j);
    }

    vector<int> s(h), t(w);
    if(q%2) {
        REP(k, h) s[(i-- + h)%h] = k;
        REP(k, w) t[(j-- + w)%w] = k;
    }
    else {
        REP(k, h) s[i++%h] = k;
        REP(k, w) t[j++%w] = k;
    }
    debug(s, t);

    REP(i, h) {
        REP(j, w) print << G(s[i], t[j]);
        print();
    }

    return 0;
}
