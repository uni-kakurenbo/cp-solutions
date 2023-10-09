/*
 * @uni_kakurenbo
 * https://github.com/uni-kakurenbo/competitive-programming-workspace
 *
 * CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja
 */
/* #language C++ 20 GCC */
/* #region template */
#include <bits/stdc++.h>

#include "template.hpp"
/* #endregion */

void solve();

signed main() {
    debug(__cplusplus);
    int $ = 1;
    std::cin >> $;
    for(int _ = 0; _ < $; ++_) {
        DEBUG("Case: #" + std::to_string(_));
        solve();
    }
    return 0;
}

bool impl(string x, string y) {
    int n = x.size();

    int cnt = 0;

    {
        int ax = 0, cx = 0;
        int ay = 0;
        REP(i, n) {
            ax += x[i] == 'A';
            cx += x[i] == 'C';
            ay += y[i] == 'A';
            if(ax < ay) {
                if(cx > 0) cx--, ay--, cnt++;
                else return false;
            }
            debug(i, ax, cx, ay);
        }
    }

    {
        int bx = 0, cx = 0;
        int by = 0;
        REPD(i, n) {
            bx += x[i] == 'B';
            cx += x[i] == 'C';
            by += y[i] == 'B';
            if(bx < by) {
                if(cx > 0) cx--, by--, cnt++;
                else return false;
            }
            debug(i, bx, cx, by);
        }
    }

    debug(cnt);

    return cnt <= std::ranges::count(x, 'C');
}

void solve() {
    int n; cin >> n;
    string x, y; cin >> x >> y;

    string s, t;
    REP(i, n) {
        if(y[i] == 'C') {
            if(x[i] != 'C') {
                print("No");
                return;
            }
            if(not impl(s, t)) {
                print("No");
                return;
            };
            s = "", t = "";
            continue;
        }
        s += x[i], t += y[i];
    }
    if(not impl(s, t)) {
        print("No");
        return;
    }

    print("Yes");
}
