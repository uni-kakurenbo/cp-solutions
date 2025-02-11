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

#include "numeric/boundary_seeker.hpp"
#include "data_structure/dynamic_set.hpp"
#include "action/range_sum.hpp"
#include "data_structure/wavelet_matrix.hpp"

#include "template/warnings.hpp"
void solve() {
    i64 n, m, k; input >> n >> m >> k;
    vector<i64> a(n); input >> a;
    auto s = a.sum();
    auto rem = k - s;
    debug(rem);

    auto b = a; b.sort();
    b *= -1;
    uni::inverse inv(b);
    uni::accumulation cum(b);

    // uni::wavelet_matrix wm(a);
    // uni::dynamic_set<uni::actions::range_sum<i64>> st;
    // ITR(v, a) st.insert(-v);

    REP(i, n) {
        debug(i);
        // debug(st);

        auto ok = [&](i64 v) {
            auto r = rem - v;
            auto q = a[i] + v;
            auto iv = inv[-a[i]][0];

            auto bnd = b.lower_bound(-q) - b.begin();
            debug(iv, bnd);

            auto ok2 = [&](i32 j) {
                i64 f = (j - bnd) * (q + 1) + (cum(bnd, j) - b[iv] * (j > iv));
                debug(j, f);
                return f <= r;
                // return true;
            };

            uni::boundary_seeker<i64> seek(ok2);
            // auto res = wm(0, i).count_over(query) + wm(i + 1, n).count_over(query);
            auto res = seek.bound(bnd, n);
            if(res > iv) res -= 1;

            debug(v, r, res);
            return res < m;
        };

        uni::boundary_seeker<i64> seeker(ok);
        print(seeker.bound_or(rem, -1, -1));
    }
}
