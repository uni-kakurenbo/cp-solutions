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

i64 N, M, T;
i64 H;

#include "template/warnings.hpp"

const i64 ORDER[36] = {
    14, 15, 21, 20,
    19, 13, 7, 8, 9, 10, 16, 22, 28, 27, 26, 25,
    24, 18, 12, 6, 0, 1, 2, 3, 4, 5, 11, 17, 23, 29, 35, 34, 33, 32, 31, 30
};

void solve() {
    input >> N >> M >> T;
    H = 2 * N * (N - 1);

    uni::grid<i64> X(H, M);
    vector<i64> ids(H); std::iota(ALL(ids), 0);

    auto f = [&](const auto& v) {
        i64 res = 0;
        ITR(x, v) res += std::pow(x, 2.4);
        return res;
    };

    auto g = [&](const auto& V) {
        i64 ds = 0;
        REP(i, N) REP(j, N) {
            ITR(ni, nj, V.vicinities4(i, j)) {
                ds += std::pow(std::max(V(i, j), V(ni, nj)), 2.4);
            }
        }
        return ds;
    };

    i64 R = 1;
    REP(t, T) {
        input >> X;
        if(t == 0) {
            uni::vector<i64> Rs(M);
            REP(i, H) REP(j, M) chmax(Rs[j], X[i][j]);
            R = Rs.sum();
            debug(Rs, R);
        }

        debug(X);
        REP(i, H) X[i] *= 1000000L / R;
        debug(X);

        ids.sort([&](auto i, auto j) {
            return f(X[i]) > f(X[j]);
        });
        debug(ids);

        uni::grid<i64> P(N, N);
        // auto sP = g(P);

        REP(i, N * N) {
            P(ORDER[i] / N, ORDER[i] % N) = ids[i];
        }

        // REP(10000) {
        //     auto Q = P;

        //     spair<i64> p0, p1;
        //     do {
        //         do {
        //             p0 = std::make_pair(uni::randi32() % N, uni::randi32() % N);
        //         } while(std::ranges::count(ORDER | std::views::take(4), P.id(p0)) > 0);
        //         do {
        //             p1 = std::make_pair(uni::randi32() % N, uni::randi32() % N);
        //         } while(std::ranges::count(ORDER | std::views::take(4), P.id(p1)) > 0);
        //     } while(p0 == p1);

        //     std::swap(Q(p0), Q(p1));
        //     auto sQ = g(Q);

        //     if(sQ > sP) {
        //         debug(sQ, sP);
        //         sP = sQ;
        //         P = std::move(Q);
        //     }
        // }

        ITR(row, P) print(row);
        print.flush();
    }
}
