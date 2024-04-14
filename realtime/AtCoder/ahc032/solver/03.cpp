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

        assert(0 <= i && i + s.h - 1 < N);
        assert(0 <= j && j + s.w - 1 < N);

        history.insert({ i, j, id, lib::randi32() });

        pushed_count += s.genome.size();

        REP(di, s.h) REP(dj, s.w) {
            score -= data[i + di][j + dj];

            data[i + di][j + dj] += s.data[di][dj];
            data[i + di][j + dj] %= MOD;

            score += data[i + di][j + dj];
        }
    }


    inline void revert(const int i, const int j, const int id) {
        assert(0 <= id && std::ranges::ssize(S));
        const auto& s = S[id];

        assert(0 <= i && i + s.h - 1 < N);
        assert(0 <= j && j + s.w - 1 < N);

        auto itr = history.lower_bound({ i, j, id, 0 });
        // debug(i, j, id, history, *itr);
        assert(itr != history.end());
        history.erase(itr);
        // debug(history);

        pushed_count -= s.genome.size();

        REP(di, s.h) REP(dj, s.w) {
            score -= data[i + di][j + dj];

            data[i + di][j + dj] = lib::mod(data[i + di][j + dj] - s.data[di][dj], MOD);

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

    inline auto calc_best_increment(const int i, const int j) {
        std::pair<int, i64> res = { -1, -INF64 };

        std::vector<int> samples;
        REP(1000) samples.push_back(rng(std::ranges::size(S)));

        ITR(s, samples) {
            if(i + S[s].h - 1 >= N) continue;
            if(j + S[s].w - 1 >= N) continue;
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
    // std::vector<stamp_t> T;
    // {
    //     REP(i, M) {
    //         REP(j, M) {
    //             REP(di, 3) REP(dj, 3) {
    //                 auto copy = S[j];
    //                 copy.merge(di, dj, S[i]);
    //                 T.emplace_back(copy);
    //             }
    //         }
    //     }
    // }


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
        REP(i, n / 2) {
            REP(j, n / 2) {
                auto copy = S[j];
                copy.merge(0, 0, S[i]);
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
        if(K  - state.pushed_count < std::ranges::ssize(S[ind].genome)) break;

        state.push(pos.first, pos.second, ind);
        debug(state.score);
    }
    std::cerr << "initial score: " << state.score << "\n";

    // S.insert(S.end(), ALL(T));
    const int W = std::ranges::ssize(S);

    debug(S.size());

    auto res = state;
    {

        int itr_count = 0;
        int accepted_count = 0;

        double start_temp = 100000000, end_temp = 100;


        while(!timer.expired()) {
            const i64 prev_score = state.score;

            int t = rng(2);
            if(state.pushed_count >= K - 3) {
                t = 1;
            }
            if(state.history.empty()) {
                t = 0;
            }

            int k, i, j;

            if(t == 0) {
                i = rng(N - 2), j = rng(N - 2);

                auto best = state.calc_best_increment(i, j);
                k = best.first;

                state.push(i, j, k);
            }

            if(t == 1) {
                [[maybe_unused]] int _;
                std::tie(i, j, k, _) = *state.history.find_by_order(rng(state.history.size()));
                state.revert(i, j, k);
            }

            const i64 score_diff = state.score - prev_score;
            if(t == 0) {
                // debug(score_diff, d);
            }

            bool accept = score_diff > 0;

            const double progress = timer.progress();

            if(!accept) {
                const double temp = start_temp + (end_temp - start_temp) * progress;
                const double prob = std::exp(score_diff / temp);
                // debug(score_diff, prob);

                accept = prob > lib::randd();
            }

            if(accept) {
                ++accepted_count;

                // progress >= 0.8 && ;
                if(res.score < state.score) {
                    res = state;
                    debug(res.score);
                }
            }
            else {
                if(t == 0) state.revert(i, j, k);
                if(t == 1) state.push(i, j, k);
            }

            ++itr_count;
        }

        std::cerr << "iteration: " << itr_count << "\n";
        std::cerr << "accepted: " << accepted_count << "\n";
        std::cerr << "score: " << res.score << "\n";
    }

    {
        std::vector<std::tuple<int, int, int>> output;
        ITR(i, j, k, _, res.history) {
            ITR(k, d, S[k].genome) {
                output.emplace_back(k, i + d.first, j + d.second);
            }
        }

        print(output.size());
        ITR(row, output) print(row);
    }
}


void solve() {
    lib::timer timer(1900);

    init();

    anneal_00(timer);
}
