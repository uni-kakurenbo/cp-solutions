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

#include "template/warnings.hpp"

constexpr i64 M = 11;

void solve() {
    i64 n, d; input >> n >> d;
    vector<i64> x(n), y(n); input >> uni::views::zip(x, y);

    i64 x_min = x.min();
    i64 y_min = y.min();
    x -= x_min, y -= y_min;


    auto f = [](auto& v) {
        uni::map<i64, i64> res;
        uni::multiset<i64> under, over(ALL(v));

        i64 sum = 0;
        ITR(t, v) {
            assert(-M <= t);
            sum += abs(-M - t);
        }

        FOR(t, -M + 1, M) {
            sum -= over.size();

            auto cnt = over.count(t);
            over.erase(t);

            sum += under.size();
            debug(t, sum, over, under);

            REP(cnt) under.insert(t);
            res[sum]++;
        }

        return res;
    };

    auto xs = f(x);
    auto ys = f(x);

    i64 sum = 0;

    ITR(v, c, ys) {
        sum += xs.upper_bound(d - v) - xs.lower_bound(d - v);
    }

    print(sum);
}
