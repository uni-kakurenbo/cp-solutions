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


void solve() {
    int n, h, w; input >> n >> h >> w;
    vector<i64> a(n), b(n); input >> lib::views::zip(a, b);

    std::vector<int> p(n); std::iota(ALL(p), 0);

    do {
        REP(x, 1U << n) {
            lib::grid<int> grid(h, w);

            FOR(i, n ) {
                int ii = -1, jj = -1;
                REPD(i, h) REPD(j, w) {
                    if(grid[i][j] == 0) {
                        ii = i, jj = j;
                    }
                }

                if(ii == -1) {
                    debug(p, std::bitset<7>(x));
                    debug(grid);
                    print.yes();
                    return;
                }

                if(i == n) break;

                int u = a[p[i]], v = b[p[i]];
                if(lib::bit(x, i)) std::swap(u, v);

                if(ii + u > h or jj + v > w) break;

                REP(s, ii, ii + u) REP(t, jj, jj + v) {
                    if(grid(s, t) != 0) goto end;
                    grid(s, t) = 1;
                }
            }
            end:;
        }
    } while(std::next_permutation(ALL(p)));

    print.no();
}
