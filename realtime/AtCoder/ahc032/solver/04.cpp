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
    std::vector<int> genome;
    std::array<std::array<int, 3>, 3> data;

    inline void read(int id) {
        genome = { id };
        REP(i, 3) REP(j, 3) input >> data[i][j];
    }

    inline void merge(const stamp_t& other) {
        {
            genome.insert(genome.end(), ALL(other.genome));
        }

        REP(i, 3) REP(j, 3) {
            data[i][j] += other.data[i][j];
            data[i][j] %= MOD;
        }
    }

    template<class Grid>
    inline auto calc_best_increment(const Grid& grid) {
        std::pair<spair<int>, i64> res = { { -1, -1 }, -INF64 };

        FOR(i, N - 3) FOR(j, N - 3) {
            if(chmax(res.second, grid.calc_push_diff(i, j, *this))) {
                res.first = { i, j };
            }
        }

        return res;
    }
};


std::vector<stamp_t> S;


lib::random_adaptor<lib::random_engine_32bit> rng;

template<class T>
using gnu_multiset = __gnu_pbds::tree<T, __gnu_pbds::null_type, std::less<T>, __gnu_pbds::rb_tree_tag, __gnu_pbds::tree_order_statistics_node_update>;

struct grid_t {
    std::vector<std::vector<i32>> data;
    gnu_multiset<std::tuple<int, int, int, u32>> history;

    i64 score;
    int pushed_count = 0;

    inline void init_score() {
        score = 0;
        REP(i, N) REP(j, N) score += data[i][j];
    }

    inline void push(const int i, const int j, const int id) {
        assert(0 <= id && id < std::ranges::ssize(S));
        const auto& s = S[id];

        assert(0 <= i && i + 2 < N);
        assert(0 <= j && j + 2 < N);

        history.insert({ i, j, id, lib::randi32() });

        pushed_count += s.genome.size();

        REP(di, 3) REP(dj, 3) {
            score -= data[i + di][j + dj];

            data[i + di][j + dj] += s.data[di][dj];
            data[i + di][j + dj] %= MOD;

            score += data[i + di][j + dj];
        }
    }


    inline void revert(const int i, const int j, const int id) {
        assert(0 <= id && std::ranges::ssize(S));
        const auto& s = S[id];

        assert(0 <= i && i + 2 < N);
        assert(0 <= j && j + 2 < N);

        auto itr = history.lower_bound({ i, j, id, 0 });
        // debug(i, j, id, history, *itr);
        assert(itr != history.end());
        history.erase(itr);
        // debug(history);

        pushed_count -= s.genome.size();

        REP(di, 3) REP(dj, 3) {
            score -= data[i + di][j + dj];

            data[i + di][j + dj] = lib::mod(data[i + di][j + dj] - s.data[di][dj], MOD);

            score += data[i + di][j + dj];
        }
    }


    inline i64 calc_push_diff(const int i, const int j, const stamp_t& s) const {
        assert(0 <= i && i + 2 < N);
        assert(0 <= j && j + 2 < N);

        i64 diff = 0;

        REP(di, 3) REP(dj, 3) {
            diff -= data[i + di][j + dj];
            diff += (data[i + di][j + dj] + s.data[di][dj]) % MOD;
        }

        return diff;
    }

    inline auto calc_best_increment(const int i, const int j) {
        std::pair<int, i64> res = { -1, -INF64 };

        std::vector<int> samples;
        REP(500) samples.push_back(rng(std::ranges::size(S)));

        ITR(s, samples) {
            if(i + 2 >= N) continue;
            if(j + 2 >= N) continue;
            if(K - pushed_count < std::ranges::ssize(S[s].genome)) continue;

            const auto diff = calc_push_diff(i, j, S[s]);
            if(chmax(res.second, diff)) {
                res.first = s;
            }
        }

        return res;
    }
};

grid_t A;

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


void anneal_00(lib::timer& timer) {
    {
        REP(i, M) {
            REP(j, M) {
                auto copy = S[j];
                copy.merge(S[i]);
                S.emplace_back(copy);
            }
        }

        std::ranges::shuffle(S, rng);

        // std::ranges::sort(
        //     S,
        //     [&](const auto& a, const auto& b) {
        //         i64 p = 0, i64 q = 0;
        //         REP(i, 3) REP(j, 3) {
        //             p.
        //         }
        //     };
        // );
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

    grid_t state = A;

    while(true) {
        spair<int> pos;
        i64 ind = -1;
        i64 max_diff = 0;

        REP(i, S.size()) {
            const auto best = S[i].calc_best_increment(state);
            if(chmax(max_diff, best.second)) {
                pos = best.first;
                ind = i;
                max_diff = best.second;
            }
        }

        debug(pos, ind, max_diff);

        if(ind < 0) break;
        if(K - state.pushed_count < std::ranges::ssize(S[ind].genome)) break;

        state.push(pos.first, pos.second, ind);
        debug(state.score);
    }
    std::cerr << "initial score: " << state.score << "\n";

    // S.insert(S.end(), ALL(T));
    const int W = std::ranges::ssize(S);

    debug(S.size());

    int c0 = 0, c1 = 0, c2 = 0;
    int a0 = 0, a1 = 0, a2 = 0;

    auto res = state;
    {

        int itr_count = 0;
        int accepted_count = 0;

        double start_temp = 100000000, end_temp = 100;


        while(!timer.expired()) {
            const i64 prev_score = state.score;

            int t = rng(30);

            int k, i, j;
            int p;

            if(t == 0) {
                ++c0;
                ++a0;
                i = rng(N - 2), j = rng(N - 2);

                auto best = state.calc_best_increment(i, j);
                k = best.first;

                if(k < 0) continue;

                state.push(i, j, k);
            }

            if(t == 1) {
                ++c1;
                ++a1;
                [[maybe_unused]] int _;
                std::tie(i, j, k, _) = *state.history.find_by_order(rng(state.history.size()));
                if(k < 0) continue;
                state.revert(i, j, k);
            }

            if(t >= 2) {
                ++c2;
                ++a2;
                [[maybe_unused]] int _;
                std::tie(i, j, k, _) = *state.history.find_by_order(rng(state.history.size()));
                if(k < 0) continue;
                state.revert(i, j, k);

                p = state.calc_best_increment(i, j).first;
                if(p < 0) continue;
                state.push(i, j, p);
            }


            const i64 score_diff = state.score - prev_score;

            bool accept = score_diff >= 0;

            const double progress = timer.progress();

            if(!accept) {
                const double temp = start_temp + (end_temp - start_temp) * progress;
                const double prob = std::exp(score_diff / temp);
                // debug(score_diff, prob);

                accept = prob > lib::randd();
            }

            if(accept) {
                // std::cerr << state.score << "\n";
                // std::cerr << progress << "\n";
                ++accepted_count;
            }
            else {
                if(t == 0) state.revert(i, j, k), --a0;
                if(t == 1) state.push(i, j, k), --a1;
                if(t >= 2) {
                    state.revert(i, j, p);
                    state.push(i, j, k);
                    --a2;
                }
            }

            if(progress >= 0.8 && res.score < state.score) {
                res = state;
                debug(res.score);
            }

            ++itr_count;
        }

        std::cerr << "iteration: " << itr_count << "\n";
        std::cerr << "c0: " << c0 << ", c1: " << c1 << ", c2: " << c2 << "\n";
        std::cerr << "accepted: " << accepted_count << "\n";
        std::cerr << "a0: " << a0 << ", a1: " << a1 << ", a2: " << a2 << "\n";
        std::cerr << "score: " << res.score << "\n";
    }

    {
        int cnt = 0;
        std::vector<std::tuple<int, int, int>> output;
        ITR(i, j, k, _, res.history) {
            ITR(k, S[k].genome) {
                output.emplace_back(k, i, j);
                ++cnt;
            }
        }
        assert(cnt <= K);

        print(output.size());
        ITR(row, output) print(row);
    }
}


void solve() {
    lib::timer timer(19500);

    init();

    anneal_00(timer);
}
