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
#include "output.hpp"

Output _print;
#define print _print
/* #endregion */

#include "grid.hpp"
#include "val_array.hpp"
#include "iterable/compression.hpp"
#include "iterable/accumulation.hpp"

#include <atcoder/modint>
using namespace atcoder;

using mint = modint998244353;

signed main() {
    int n; cin >> n;
    UnfoldedGrid<int,ValArray<int>> A(5, n);
    A.read();

    Compression<int,ValArray<int>> comp(ALL(A));

    Grid<int> cnts(5, comp.max()+1);
    REP(i, 5) REP(j, n) ++cnts(i, comp[i*n+j]);

    debug(cnts);

    vector<Accumulation<int>> cumf(5), cumb(5);
    REP(i, 5) {
        cumf[i] = { ALL(cnts[i]) };
        cumb[i] = { RALL(cnts[i]) };
        reverse(ALL(cumb[i]));
    }

    debug(cumf, cumb);

    Grid<int> P = {
        {0,  0,   0,  0,  0},
        {0,  0,   0,  0,  1},
        {0,  0,   0,  1,  1},

        {-1,  0,  0,  0,  0},
        {-1,  0,  0,  0,  1},
        {-1,  0,  0,  1,  1},

        {-1, -1,  0,  0,  0},
        {-1, -1,  0,  0,  1},
        {-1, -1,  0,  1,  1},
    };

    mint ans = 0;
    FOR(t, 0, comp.max()) {
        debug(t, comp(t));
        ITRR(p, P) {
            do {
                mint prod = 1;
                REP(i, 5) {
                    if(p[i] == 0) {
                        prod *= cnts[i][t];
                        continue;
                    }
                    prod *= (p[i] < 0 ? cumf[i][t] : cumb[i][t+1]);
                }
                if(prod.val() > 0) debug(prod, t, p);
                ans += prod * comp(t);
            } while(next_permutation(ALL(p)));
        }
    }

    print(ans);

    return 0;
}
