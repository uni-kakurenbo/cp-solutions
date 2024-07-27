/*
 * @uni_kakurenbo
 * https://github.com/uni-kakurenbo/competitive-programming-workspace
 *
 * CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja
 */
/* #language C++ 20 GCC */
// #define DEBUGGER_ENABLED

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

#include "data_structure/wavelet_matrix.hpp"
#include "numeric/boundary_seeker.hpp"

#include "template/warnings.hpp"

void solve() {
    i32 n, q; input >> n >> q;
    vector<i64> a(n); input >> a;
    auto base = a.min() ;
    a -= base;

    uni::wavelet_matrix<i64>::compressed wm(a);
    debug(wm);

    REP(q) {
        i128 b, k; input >> b >> k;
        b -= base;

        auto ok = [&](i128 v) {
            auto cnt = wm.count_in_range(uni::max(0, b - v), uni::min(INF64 / 2, b + v));
            // debug(v, b - v, b + v, cnt);
            return cnt < k;
        };

        uni::boundary_seeker<i128> seeker(ok);
        print(seeker.bound(-1, INF64 / 2) + 1);
    }
}
