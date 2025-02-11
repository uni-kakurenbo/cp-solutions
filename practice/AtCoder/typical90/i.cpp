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

using point = uni::point<double>;

constexpr auto M_2PI = 2 * M_PI;

void solve() {
    i32 n; input >> n;
    vector<point> ps(n); input >> ps;

    double ans = 0;

    ITR(p, ps) {
        vector<double> args;
        ITR(q, ps) {
            if(p == q) continue;
            args.push_back((p - q).argument());
        }
        args.sort();

        ITR(v, args) {
            auto x = v + M_PI;
            if(x > M_2PI) x -= M_2PI;
            auto itr = std::ranges::lower_bound(args, x);

            FOR(d, -1, 0) {
                if(itr + d == args.end()) continue;
                auto r = std::abs(*(itr + d) - v);

                chmax(ans, std::min(r, M_2PI - r));
            }
        }
    }

    print(ans * 180 / M_PI);
}
