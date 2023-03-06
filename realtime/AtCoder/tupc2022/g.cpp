/*
 * @uni_kakurenbo
 * https://github.com/uni-kakurenbo/competitive-programming-workspace
 *
 * CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja
 */
/* #language C++ GCC */
/* #region template */
#include <bits/stdc++.h>
// using namespace std;

#include "template.hpp"
/* #endregion */

signed main() {
    int n; std::cin >> n;

    std::vector<int> v(100, 100);

    REP(m, 50) {
        debug(m);
        REP(i, (ll)std::pow(n, m)) {
            std::vector<int> a(m);
            REP(j, m) a[j] = i/(ll)std::pow(n, m-j-1) % n;
            // debug(a);
            bool f = true;
            REP(p, n) REP(q, p+1, n) {
                bool g = false;
                REP(j, m-1) {
                    if((p == a[j] and q == a[j+1]) or (p == a[j+1] and q == a[j])) {
                        g |= true;
                    }
                    if(g) break;
                }
                f &= g;
                if(!f) break;
            }
            if(f) {
                if(v > a) {
                    v = a;
                }
            }
        }
        if(v.size() < 100) break;
    }

    debug(v);

    return 0;
}
