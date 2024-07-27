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

i32 N, M, T;
i32 H;

#include "template/warnings.hpp"

const i32 ORDER[36] = {
    14, 15, 21, 20,
    19, 13, 7, 8, 9, 10, 16, 22, 28, 27, 26, 25,
    24, 18, 12, 6, 0, 1, 2, 3, 4, 5, 11, 17, 23, 29, 35, 34, 33, 32, 31, 30
};

void solve() {
    input >> N >> M >> T;
    H = 2 * N * (N - 1);

    uni::grid<i32> X(H, M);
    vector<i32> ids(H); std::iota(ALL(ids), 0);

    auto f = [&](const auto& v) {
        i64 res = 0;
        ITR(x, v) res += std::pow(x, 2.4);
        return res;
    };

    REP(T) {
        input >> X;

        ids.sort([&](auto i, auto j) {
            return f(X[i]) > f(X[j]);
        });
        debug(ids);

        uni::grid<i32> P(N, N);
        REP(i, N * N) {
            P(ORDER[i] / N, ORDER[i] % N) = ids[i];
        }

        ITR(row, P) print(row);
        print.flush();
    }
}
