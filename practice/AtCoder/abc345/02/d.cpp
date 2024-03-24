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
    vector<int> a(n), b(n); input >> lib::views::zip(a, b);

    vector<int> p(n); std::iota(ALL(p), 0);

    do {
        REP(x, 1U << n) {
            auto c = lib::order_by(a, p), d = lib::order_by(b, p);
            REP(i, n) if(lib::bit(x, i)) std::swap(c[i], d[i]);

            auto ok = [&]{
                lib::grid<int> grid(h, w);
                int ind = 0;
                REP(i, h) REP(j, w) {
                    if(grid(i, j)) continue;
                    if(ind >= n) return false;
                    REP(ii, i, i + c[ind]) REP(jj, j, j + d[ind]) {
                        if(!grid.is_valid(ii, jj)) return false;
                        if(grid(ii, jj)) return false;
                        grid(ii, jj) = true;
                    }
                    ++ind;
                }
                return true;
            }();

            if(ok) {
                print.yes();
                return;
            }
        }
    } while(std::next_permutation(ALL(p)));

    print.no();
}
