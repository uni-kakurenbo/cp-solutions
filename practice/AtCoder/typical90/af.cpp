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
    int n; input >> n;
    lib::grid<int> a(n); input >> a;

    int m; input >> m;
    lib::set<spair<int>> ng;
    REP(m) {
        int x, y; input >> x >> y; --x, --y;
        ng.emplace(x, y), ng.emplace(y, x);
    }

    i64 ans = INF64;

    vector<int> ind(n); std::iota(ALL(ind), 0);
    do {
        [&]{
            i64 time = 0;

            REP(i, 1, n) {
                if(ng.contains({ ind[i - 1], ind[i] })) {
                    return;
                }
            }
            REP(i, n) time += a[ind[i]][i];

            chmin(ans, time);
        }();
    } while(std::ranges::next_permutation(ind).found);

    print(lib::to_optional_if_or_over(ans, INF64).value_or(-1));
}
