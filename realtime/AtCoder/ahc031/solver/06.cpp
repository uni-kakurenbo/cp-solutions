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
#include <atcoder/fenwicktree>

i32 W, D, N;
std::vector<std::vector<i32>> A;


namespace sol {


template<
    std::forward_iterator I0, std::sentinel_for<I0> S0,
    std::forward_iterator I1, std::sentinel_for<I1> S1
>
i32 count_diff(I0 first0, S0 last0, I1 first1, S1 last1) {
    i32 res = 0;

    while(first0 != last0 && first1 != last1) {
        if(*first0 < *first1) {
            ++res;
            // *__result = *first0;
            ++first0;
            // ++__result;
        }
        else if (*first1 < *first0) {
            ++first1;
        }
        else {
            ++first0;
            ++first1;
        }
    }

    res += std::ranges::distance(std::move(first0), std::move(last0));

    return res;
}


struct state {
    std::vector<std::vector<i32>> P, H;

    i32 area_cost = 0, move_cost = 0;

    state() : P(D), H(D) {
        ITRR(p, P) {
            p.resize(N);
            std::iota(ALL(p), 0);
        }

        REP(d, D) {
            H[d].resize(N + 1, W);
            H[d][0] = 0;
            REP(i, N - 1) set_line(d, i + 1, H[d][i] + lib::div_ceil(A[d][i], W));
        }

        calc_cost();
        debug(area_cost, move_cost);
    }

    inline i32 cost() const { return area_cost + move_cost; }


    inline i32 calc_area_cost(i32 d, i32 i) const {
        assert(0 <= d && d < D);
        assert(0 <= i && i < N);

        const i32 area = W * (H[d][i + 1] - H[d][i]);
        return std::abs(100 * (A[d][P[d][i]] - area));
    }

    inline i32 calc_move_cost(i32 d) const {
        i32 cnt = 0;

        if(d > 0) cnt += count_diff(ALL(H[d - 1]), ALL(H[d]));
        if(d + 1 < D) cnt += count_diff(ALL(H[d + 1]), ALL(H[d]));

        return cnt * 2 * W;
    }


    inline spair<i32> swap(i32 d, i32 i, i32 j) {
        assert(0 <= d && d < D);
        assert(0 <= i && i < N);

        i32 area_cost_diff = 0;

        area_cost_diff -= calc_area_cost(d, i);
        area_cost_diff -= calc_area_cost(d, j);

        std::swap(P[d][i], P[d][j]);

        area_cost_diff += calc_area_cost(d, i);
        area_cost_diff += calc_area_cost(d, j);

        return { area_cost_diff, 0 };
    }


    inline void set_line(i32 d, i32 i, i32 pos) {
        assert(0 <= d && d < D);
        assert(0 < i && i < N);
        H[d][i] = std::clamp(pos, H[d][i - 1] + 1, H[d][i + 1] - 1);
    }

    spair<i32> move_line(i32 d, i32 i, i32 j, i32 pos) {
        assert(0 <= d && d < D);
        assert(0 < i && i < j && j <= N);

        i32 move_cost_diff = 0;
        i32 area_cost_diff = 0;

        move_cost_diff -= calc_move_cost(d);
        FOR(k, i, j) area_cost_diff -= calc_area_cost(d, k - 1);

        REP(k, i, j) set_line(d, k, H[d][k] + pos);

        FOR(k, i, j) area_cost_diff += calc_area_cost(d, k - 1);
        move_cost_diff += calc_move_cost(d);

        return { area_cost_diff, move_cost_diff };
    }


    auto dump() const {
        std::ostringstream res;

        REP(d, D) {
            REP(i, N) {
                std::vector<i32> rev(N); std::iota(ALL(rev), 0);
                REP(i, N) rev[P[d][i]] = i;

                res << H[d][rev[i]] << lib::SPC;
                res << 0 << lib::SPC;
                res << H[d][rev[i] + 1] << lib::SPC;
                res << W << lib::LN;
            }
        }

        return res.str();
    }


    void calc_cost(const i32 d) {
        if(d > 0) {
            std::vector<i32> prev(N - 1), cur(N - 1), diff;
            REP(i, N - 1) {
                prev[i] = H[d - 1][i + 1];
                cur[i] = H[d][i + 1];
            }

            std::ranges::set_symmetric_difference(prev, cur, std::back_inserter(diff));
            move_cost += W * diff.size();
        }


        REP(i, N) {
            i32 p = A[d][i], q = W * (H[d][P[d][i] + 1] - H[d][P[d][i]]);
            area_cost += 100 * std::abs(p - q);
        }
    }

    inline void calc_cost() {
        REP(d, D) calc_cost(d);
    }
};

} // namespace sol



void solve() {
    lib::timer timer(2800);

    input >> W >> D >> N;
    debug(W, D, N);

    A.resize(D);
    ITRR(a, A) a.resize(N), input >> a;
    debug(A);

    {
        sol::state state;

        debug(state.cost());
        debug(state.H);

        int itr_count = 0;
        int accepted_count = 0;

        double start_temp = 1000, end_temp = 10;

        sol::state res = state;

        while(!timer.expired()) {
            const i32 d = lib::randi32() % D;

            i32 i, j;

            int t = lib::randi32() % 2;
            if(t == 0) {
                i = lib::randi32() % N;
                j = (i + 1 + lib::randi32() % (N - 1)) % N;

                assert(i != j);
                assert(0 <= i && i < N);
                assert(0 <= j && j < N);
            }
            else {
                i = lib::randi32() % (N - 1) + 1;
                j = (i + lib::randi32() % (N - 2)) % (N - 1) + 1;
                if(i > j) std::swap(i, j);

                assert(i != j);
                assert(0 < i && i < j && j <= N);
            }

            i32 h = lib::randi32() % (W / N) - (W / (2 * N));

            std::vector<i32> prev;

            i32 area_cost_diff = 0, move_cost_diff = 0;

            if(t == 0) {
                auto [ area, move ] = state.swap(d, i, j);
                area_cost_diff += area, move_cost_diff += move;
            }
            else {
                prev.resize((j - i + 1));
                auto begin = std::ranges::begin(state.H[d]);
                std::ranges::copy(begin + i, begin + j + 1, std::ranges::begin(prev));

                auto [ area, move ] = state.move_line(d, i, j + 1, h);
                area_cost_diff += area, move_cost_diff += move;
            }

            const i32 score_diff = area_cost_diff + move_cost_diff;

            bool accept = score_diff <= 0;

            const double progress = timer.progress();

            if(!accept) {
                const double temp = start_temp + (end_temp - start_temp) * progress;
                const double prob = std::exp(-score_diff / temp);

                // debug(score_diff, temp, prob);

                accept = prob > lib::randd();
            }

            if(accept) {
                ++accepted_count;

                state.area_cost += area_cost_diff;
                state.move_cost += move_cost_diff;

                // progress >= 0.8 && ;
                if(state.cost() < res.cost()) {
                    res = state;
                    debug(res.cost());
                }
            }
            else {
                if(t == 0) state.swap(d, i, j);
                else {
                    std::ranges::copy(ALL(prev), std::ranges::begin(state.H[d]) + i);
                }
            }

            ++itr_count;
        }

        debug(res.P, res.H);

        std::cerr << "iteration: " << itr_count << "\n";
        std::cerr << "accepted: " << accepted_count << "\n";
        std::cerr << "cost: " << res.cost() << "\n";

        // REP(d, D) {
        //     REP(i, N) std::cerr << state.H[d].sum(i, i + 1) << " ";
        //     std::cerr << "\n";
        // }
        print(res.dump());
    }
}
