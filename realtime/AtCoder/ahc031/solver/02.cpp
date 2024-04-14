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
        return std::max(INT32_C(0), 100 * (A[d][P[d][i]] - area));
    }

    inline i32 calc_move_cost(i32 d, i32 i) const {
        i32 res = 0;

        if(d > 0) {
            if(not std::ranges::binary_search(H[d - 1], H[d][i])) {
                res += 2 * W;
            }
        }
        if(d < D - 1) {
            if(not std::ranges::binary_search(H[d + 1], H[d][i])) {
                res += 2 * W;
            }
        }

        return res;
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

    spair<i32> move_line(i32 d, i32 i, i32 pos) {
        assert(0 <= d && d < D);
        assert(0 < i && i < N);

        i32 move_cost_diff = 0;
        i32 area_cost_diff = 0;

        area_cost_diff -= calc_area_cost(d, i - 1) + calc_area_cost(d, i);
        move_cost_diff -= calc_move_cost(d, i);

        set_line(d, i, pos);

        area_cost_diff += calc_area_cost(d, i - 1) + calc_area_cost(d, i);
        move_cost_diff += calc_move_cost(d, i);

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

            const auto prev = state.H[d][i];

            i32 area_cost_diff, move_cost_diff;

            int t = lib::randi32() % 5;

            if(t == 0) {
                std::tie(area_cost_diff, move_cost_diff) = state.swap(d, i, j);
            }
            else {
                std::tie(area_cost_diff, move_cost_diff) = state.move_line(d, i, h);
            }

            if(area_cost_diff + move_cost_diff <= 0) {
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

        // REP(d, D) {
        //     REP(i, N) std::cerr << state.H[d].sum(i, i + 1) << " ";
        //     std::cerr << "\n";
        // }
        print(state.dump());
    }
}
