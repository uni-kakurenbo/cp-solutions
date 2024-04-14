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
    i32 $ = 1;
    // std::cin >> $;
    for(i32 _ = 0; _ < $; ++_) {
        debug_("Case: #" + std::to_string(_));
        solve();
    }
    return 0;
}

#include "utility/timer.hpp"
#include "random/adaptor.hpp"
#include "random/engine.hpp"


i32 N, M, K;

constexpr i32 MOD = 998244353;


struct stamp_t {
    std::vector<int> ids;
    std::array<std::array<int, 3>, 3> data;

    inline void read(int id) {
        ids = { id };
        REP(i, 3) REP(j, 3) input >> data[i][j];
    }

    inline void merge(const stamp_t& other) {
        ids.insert(ids.end(), ALL(other.ids));
        REP(i, 3) REP(j, 3) {
            data[i][j] += other.data[i][j];
            data[i][j] %= MOD;
        }
    }
};

struct grid_t {
    std::vector<std::vector<i32>> data;

    i64 score;
    int pushed_count = 0;

    inline void init_score() {
        score = 0;
        REP(i, N) REP(j, N) score += data[i][j];
    }

    inline void push(const int i, const int j, const stamp_t& s) {
        assert(0 <= i && i + 2 < N);
        assert(0 <= j && j + 2 < N);

        pushed_count += s.ids.size();

        REP(di, 3) REP(dj, 3) {
            score -= data[i + di][j + dj];

            data[i + di][j + dj] += s.data[di][dj];
            data[i + di][j + dj] %= MOD;

            score += data[i + di][j + dj];
        }
    }

    inline i64 calc_push_diff(const int i, const int j, const stamp_t& s) {
        assert(0 <= i && i + 2 < N);
        assert(0 <= j && j + 2 < N);

        i64 diff = 0;

        REP(di, 3) REP(dj, 3) {
            diff -= data[i + di][j + dj];
            diff += (data[i + di][j + dj] + s.data[di][dj]) % MOD;
        }

        return diff;
    }

    inline auto calc_best_increment(const int i, const int j, const std::vector<stamp_t>& stamps) {
        std::pair<int, i64> res = { -1, -INF64 };

        REP(s, std::ranges::size(stamps)) {
            const auto diff = calc_push_diff(i, j, stamps[s]);
            if(chmax(res.second, diff)) {
                res.first = s;
            }
        }

        return res;
    }
};

grid_t A;


std::vector<stamp_t> S;


void init() {
    input >> N >> M >> K;
    debug(N, M, K);

    A.data.resize(N);
    ITRR(row, A.data) {
        row.resize(N);
        input >> row;
    }
    A.init_score();
    debug(A.data, A.score);

    S.resize(M);
    REP(i, M) {
        S[i].read(i);
        debug(S[i].data);
    }
}


lib::random_adaptor<lib::random_engine_32bit> rng;

void greedy_00() {
    {
        REP(i, M) {
            REP(j, M) {
                auto copy = S[j];
                copy.merge(S[i]);
                S.emplace_back(copy);
            }
        }

        std::ranges::shuffle(S, rng);
    }

    {
        auto n = S.size();
        REP(i, n) {
            REP(j, n / 2) {
                auto copy = S[j];
                copy.merge(S[i]);
                S.emplace_back(copy);
            }
        }
    }

    debug(S.size());

    std::vector<std::tuple<i32, i32, i32>> history;

    while(true) {
        spair<int> pos;
        i64 ind = -1;
        i64 max_diff = 0;

        REP(i, N - 2) REP(j, N - 2) {
            const auto best = A.calc_best_increment(i, j, S);
            if(chmax(max_diff, best.second)) {
                pos = { i, j };
                ind = best.first;
            }
        }

        debug(pos, ind, max_diff);

        if(ind < 0) break;
        if(K  - A.pushed_count < std::ranges::ssize(S[ind].ids)) break;

        A.push(pos.first, pos.second, S[ind]);
        history.emplace_back(ind, pos.first, pos.second);
        debug(A.score);
    }


    {
        std::vector<std::tuple<int, int, int>> output;
        ITR(ind, i, j, history) {
            ITR(k, S[ind].ids) {
                output.emplace_back(k, i, j);
            }
        }

        print(output.size());
        ITR(row, output) print(row);
    }
}


void solve() {
    lib::timer timer(1800);

    init();

    greedy_00();
}
