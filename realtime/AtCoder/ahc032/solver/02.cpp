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


struct grid_t;


struct stamp_t {
    std::vector<std::pair<int, spair<int>>> genome;
    int h = 3, w = 3;
    std::array<std::array<int, 5>, 5> data;

    inline void read(int id) {
        genome = { { id, { 0, 0 } } };
        REP(i, 3) REP(j, 3) input >> data[i][j];
    }

    inline void merge(const int di, const int dj, const stamp_t& other) {
        assert(0 <= di && di < 3);
        assert(0 <= dj && dj < 3);
        assert(other.h == 3);
        assert(other.w == 3);

        {
            auto g = other.genome;
            ITRR(id, p, g) p.first += di, p.second += dj;
            genome.insert(genome.end(), ALL(g));
        }

        REP(i, 3) REP(j, 3) {
            data[i + di][j + dj] += other.data[i][j];
            data[i + di][j + dj] %= MOD;
        }
        h += di;
        w += dj;
    }

    template<class Grid>
    inline auto calc_best_increment(const Grid& grid) {
        std::pair<spair<int>, i64> res = { { -1, -1 }, -INF64 };

        FOR(i, N - h) FOR(j, N - w) {
            if(chmax(res.second, grid.calc_push_diff(i, j, *this))) {
                res.first = { i, j };
            }
        }

        return res;
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
        assert(0 <= i && i + s.h - 1 < N);
        assert(0 <= j && j + s.w - 1 < N);

        pushed_count += s.genome.size();

        REP(di, s.h) REP(dj, s.w) {
            score -= data[i + di][j + dj];

            data[i + di][j + dj] += s.data[di][dj];
            data[i + di][j + dj] %= MOD;

            score += data[i + di][j + dj];
        }
    }

    inline i64 calc_push_diff(const int i, const int j, const stamp_t& s) const {
        assert(0 <= i && i + s.h - 1 < N);
        assert(0 <= j && j + s.w - 1 < N);

        i64 diff = 0;

        REP(di, s.h) REP(dj, s.w) {
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
    std::vector<stamp_t> T;
    {
        REP(i, M) {
            REP(j, M) {
                REP(di, 3) REP(dj, 3) {
                    auto copy = S[j];
                    copy.merge(di, dj, S[i]);
                    T.emplace_back(copy);
                }
            }
        }
    }


    {
        REP(i, M) {
            REP(j, M) {
                auto copy = S[j];
                copy.merge(0, 0, S[i]);
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
                copy.merge(0, 0, S[i]);
                S.emplace_back(copy);
            }
        }
    }

    S.insert(S.end(), ALL(T));

    debug(S.size());

    std::vector<std::tuple<i32, i32, i32>> history;

    while(true) {
        spair<int> pos;
        i64 ind = -1;
        i64 max_diff = 0;

        REP(i, S.size()) {
            const auto best = S[i].calc_best_increment(A);
            if(chmax(max_diff, best.second)) {
                pos = best.first;
                ind = i;
                max_diff = best.second;
            }
        }

        debug(pos, ind, max_diff);

        if(ind < 0) break;
        if(K  - A.pushed_count < std::ranges::ssize(S[ind].genome)) break;

        A.push(pos.first, pos.second, S[ind]);
        history.emplace_back(ind, pos.first, pos.second);
        debug(A.score);
    }


    {
        std::vector<std::tuple<int, int, int>> output;
        ITR(ind, i, j, history) {
            ITR(k, d, S[ind].genome) {
                output.emplace_back(k, i + d.first, j + d.second);
            }
        }

        print(output.size());
        ITR(row, output) print(row);
    }
}


void solve() {
    // lib::timer timer(1800);

    init();

    greedy_00();
}
