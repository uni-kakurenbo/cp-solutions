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
    lib::grid<int> G(3, 3); input >> G;
    debug(G);

    valarray<int> a(9); std::iota(ALL(a), 0);
    constexpr long all = lib::factorial(9L);

    int cnt = 0;
    do {
        debug(a);

        int row[3] = {0}, col[3] = {0}, x = 0, y = 0;
        std::set<int> row_st[3], col_st[3], x_st, y_st;

        ITR(p, a) {
            int i = p / 3, j = p % 3;

            row[i]++, col[j]++;
            if(i == j) x++;
            if(2-i == j) y++;

            if(
                (row[i] == 3 and row_st[i].size() == 1) or
                (col[j] == 3 and col_st[j].size() == 1) or
                (x == 3 and x_st.size() == 1) or
                (y == 3 and y_st.size() == 1)
            ) {
                cnt++;
                break;
            }

            row_st[i].insert(G[i][j]);
            col_st[j].insert(G[i][j]);
            if(i == j) x_st.insert(G[i][j]);
            if(2-i == j) y_st.insert(G[i][j]);

            debug(row, col, x, y);
        }
    } while(std::next_permutation(ALL(a)));

    debug(cnt, all);
    print(1 - (ld)cnt / all);
}
