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
    // std::cin >> $;
    for(int _ = 0; _ < $; ++_) {
        DEBUG("Case: #" + std::to_string(_));
        solve();
    }
    return 0;
}

void solve() {
    int n; std::cin >> n;
    string r, c; std::cin >> r >> c;

    lib::valarray<int> x(n), y, z;
    std::iota(ALL(x), 0);
    z = y = x;

    do {
        do {
            do {
                lib::grid<char,string> G(n, n, '.');

                bool ng = false;
                REP(i, n) {
                    if(x[i] == y[i]) BREAK(ng = true);
                    if(y[i] == z[i]) BREAK(ng = true);
                    if(z[i] == x[i]) BREAK(ng = true);
                    G[i][x[i]] = 'A';
                    G[i][y[i]] = 'B';
                    G[i][z[i]] = 'C';
                }
                if(ng) continue;

                REP(i, n) REP(j, n) {
                    if(G[i][j] == '.') continue;
                    if(G[i][j] != r[i]) ng = true;
                    break;
                }
                if(ng) continue;
                REP(i, n) REP(j, n) {
                    if(G[j][i] == '.') continue;
                    if(G[j][i] != c[i]) ng = true;
                    break;
                }
                if(ng) continue;
                print.yes();
                print(lib::join(G, "\n"));
                return;
            } while(std::next_permutation(ALL(z)));
        } while(std::next_permutation(ALL(y)));
    } while(std::next_permutation(ALL(x)));
    print.no();
}
