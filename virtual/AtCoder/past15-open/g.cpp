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
        DEBUG("Case: #" + std::to_string(_));
        solve();
    }
    return 0;
}

void solve() {
    int n, m; input >> n >> m;
    valarray<vector<spair<int>>> P(m);
    valarray<int> k(m);

    REP(i, m) {
        input >> k[i];
        vector<spair<int>> row;
        REP(k[i]) {
            int a, b; input >> a >> b, --a;
            row.emplace_back(a, b);
        }
        P[i] = row;
    }
    debug(P, k);

    auto ok = [&](int v) {
        return std::ranges::all_of(
            std::views::iota(0, m),
            [&](int i) {
                return std::ranges::any_of(
                    std::views::iota(0, k[i]),
                    [&](int j) {
                        auto [ a, b ] = P[i][j];
                        // debug(v, i, j);
                        return ((v >> a) & 1) == b;
                    }
                );
            }
        );
    };

    print.yesno(std::ranges::any_of(std::views::iota(0, 1 << n), ok));
}
