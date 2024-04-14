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


struct state {
    std::vector<std::vector<i32>> P, H;

    i32 area_cost = 0, move_cost = 0;
    i32 additional_cost = 0;

    state() : P(D), H(D) {
        ITRR(p, P) {
            p.resize(N);
            std::iota(ALL(p), 0);
        }

        REP(d, D) {
            H[d].resize(N + 1, W);
            H[d][0] = 0;
            REP(i, N - 1) set_line(d, i + 1, H[d][i] + W / N);
        }

        calc_cost();
        debug(area_cost, move_cost);
    }

    inline i32 cost() const { return area_cost + move_cost + additional_cost; }
    inline i32 real_cost() const { return area_cost + move_cost; }


    inline spair<i32> calc_area_cost(i32 d, i32 i) const {
        assert(0 <= d && d < D);
        assert(0 <= i && i < N);

        const i32 area = W * (H[d][i + 1] - H[d][i]);
        return {
            std::max(INT32_C(0), 100 * (A[d][P[d][i]] - area)),
            std::abs(100 * (A[d][P[d][i]] - area))
        };
    }

    inline spair<i32> calc_move_cost(i32 d, i32 i) const {
        i32 real = 0;
        i32 additional = 0;

        if(d > 0) {
            if(auto itr = std::ranges::lower_bound(H[d - 1], H[d][i]); itr != H[d - 1].end()) {
                if(*itr != H[d][i]) real += 2 * W;
                additional += *itr - H[d][i];
                additional += *std::ranges::prev(itr) - H[d][i];
            }
        }

        if(d < D - 1) {
            if(auto itr = std::ranges::lower_bound(H[d + 1], H[d][i]); itr != H[d + 1].end()) {
                if(*itr != H[d][i]) real += 2 * W;
                additional += *itr - H[d][i];
                additional += *std::ranges::prev(itr) - H[d][i];
            }
        }

        return { real, additional };
    }


    inline tuple<i32, i32, i32> swap(i32 d, i32 i, i32 j) {
        assert(0 <= d && d < D);
        assert(0 <= i && i < N);

        i32 area_cost_diff = 0;
        i32 additional_cost_diff = 0;

        {
            auto [ real, additional ] = calc_area_cost(d, i);
            area_cost_diff -= real;
            additional_cost_diff -= additional;
        }
        {
            auto [ real, additional ] = calc_area_cost(d, j);
            area_cost_diff -= real;
            additional_cost_diff -= additional;
        }

        std::swap(P[d][i], P[d][j]);

        {
            auto [ real, additional ] = calc_area_cost(d, i);
            area_cost_diff += real;
            additional_cost_diff += additional;
        }
        {
            auto [ real, additional ] = calc_area_cost(d, j);
            area_cost_diff += real;
            additional_cost_diff += additional;
        }

        return { area_cost_diff, 0, additional_cost_diff };
    }


    inline void set_line(i32 d, i32 i, i32 pos) {
        assert(0 <= d && d < D);
        assert(0 < i && i < N);
        H[d][i] = std::clamp(pos, H[d][i - 1] + 1, H[d][i + 1] - 1);
    }

    tuple<i32, i32, i32> move_line(i32 d, i32 i, i32 pos) {
        assert(0 <= d && d < D);
        assert(0 < i && i < N);

        i32 move_cost_diff = 0;
        i32 area_cost_diff = 0;
        i32 additional_cost_diff = 0;

        {
            auto [ real, additional ] = calc_area_cost(d, i - 1);
            area_cost_diff -= real;
            additional_cost_diff -= additional;
        }
        {
            auto [ real, additional ] = calc_area_cost(d, i);
            area_cost_diff -= real;
            additional_cost_diff -= additional;
        }
        {
            auto [ real, additional ] = calc_move_cost(d, i);
            move_cost_diff -= real;
            additional_cost_diff -= additional;
        }

        set_line(d, i, pos);

        {
            auto [ real, additional ] = calc_area_cost(d, i - 1);
            area_cost_diff += real;
            additional_cost_diff += additional;
        }
        {
            auto [ real, additional ] = calc_area_cost(d, i);
            area_cost_diff += real;
            additional_cost_diff += additional;
        }
        {
            auto [ real, additional ] = calc_move_cost(d, i);
            move_cost_diff += real;
            additional_cost_diff += additional;
        }

        return { area_cost_diff, move_cost_diff, additional_cost_diff };
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
            if(p > q) area_cost += 100 * (p - q);
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

        while(!timer.expired()) {
            const i32 d = lib::randi32() % D;

            const i32 i = lib::randi32() % (N - 1) + 1;
            const i32 j = (i + 1 + lib::randi32() % (N - 1)) % N;
            const auto prev = state.H[d][i];

            i32 area_cost_diff, move_cost_diff, additional_cost_diff;

            int t = lib::randi32() % 5 + 1;

            if(t == 0) {
                std::tie(area_cost_diff, move_cost_diff, additional_cost_diff) = state.swap(d, i, j);
            }
            else {
                const i32 p = lib::randi32() % 10;

                i32 h = 0;

                if(p == 0) {
                    const i32 nd =
                        d == 0 ? 1 :
                        d == D - 1 ? D - 2 :
                        d + 2 * (lib::randi32() % 2) - 1;
                    h = *std::ranges::upper_bound(state.H[nd], state.H[nd][i]);
                }
                if(p == 1) {
                    const i32 nd =
                        d == 0 ? 1 :
                        d == D - 1 ? D - 2 :
                        d + 2 * (lib::randi32() % 2) - 1;
                    h = *std::ranges::prev(std::ranges::lower_bound(state.H[nd], state.H[nd][i]));
                }
                if(p >= 2) {
                    h = lib::randi32() % (state.H[d][i + 1] - state.H[d][i - 1]) + state.H[d][i - 1];
                }

                // debug(h);

                std::tie(area_cost_diff, move_cost_diff, additional_cost_diff) = state.move_line(d, i, h);
            }

            debug(t, area_cost_diff, move_cost_diff, additional_cost_diff, area_cost_diff + move_cost_diff + additional_cost_diff);

            if(area_cost_diff + move_cost_diff + additional_cost_diff <= 0) {
                // debug(area_cost_diff + move_cost_diff);
                ++accepted_count;

                state.area_cost += area_cost_diff;
                state.move_cost += move_cost_diff;

                // debug(d, p, prev, h);

                // debug(area_cost_diff, move_cost_diff);
                // debug(state.cost());
            }
            else {
                if(t == 0) state.swap(d, i, j);
                else state.set_line(d, i, prev);
            }

            ++itr_count;
        }

        debug(state.P, state.H);

        std::cerr << "iteration: " << itr_count << "\n";
        std::cerr << "accepted: " << accepted_count << "\n";
        std::cerr << "cost: " << state.cost() << "\n";
        std::cerr << "real cost: " << state.real_cost() << "\n";

        // REP(d, D) {
        //     REP(i, N) std::cerr << state.H[d].sum(i, i + 1) << " ";
        //     std::cerr << "\n";
        // }
        print(state.dump());
    }
}
