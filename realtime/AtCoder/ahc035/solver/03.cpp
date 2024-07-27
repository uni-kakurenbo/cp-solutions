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
    14, 15, 20, 13, 8, 9, 21, 19, 7, 2, 16, 26, 12, 1, 3, 10, 22, 27, 25, 18, 6,
    0, 4, 28, 24, 32, 17, 11, 23, 33, 31, 5, 29, 34, 30, 35
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
