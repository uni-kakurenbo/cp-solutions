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

i32 W, D, N;
std::vector<std::vector<i32>> A;


namespace sol {


struct state {
    std::vector<std::vector<i32>> P, H;

    state() : P(D), H(D) {
        ITRR(p, P) p.resize(N), std::iota(ALL(p), 0);

        ITR(a, h, p, lib::views::zip(A, H, P)) {
            h.resize(N + 1);
            REP(i, N) h[i + 1] = std::min(W - (N - i - 1), h[i] + lib::div_ceil(a[p[i]], W));
            h[N] = W;
        }
    }

    void update(i32 d) {
        auto& h = H[d];
        auto& a = A[d];
        auto& p = P[d];

        REP(i, N) h[i + 1] = std::min(W - (N - i - 1), h[i] + lib::div_ceil(a[p[i]], W));
        h[N] = W;
    }


    auto dump() const {
        std::ostringstream res;

        REP(d, D) {
            std::vector<i32> rev(N);
            REP(i, N) rev[P[d][i]] = i;

            REP(i, N) {
                res << H[d][rev[i]] << lib::SPC;
                res << 0 << lib::SPC;
                res << H[d][rev[i] + 1] << lib::SPC;
                res << W << lib::LN;
            }
        }

        return res.str();
    }


    i32 calc_score(const i32 d) const {
        if(d >= D) return 0;

        i32 res = 0;

        if(d > 0) {
            std::vector<i32> diff;
            std::ranges::set_symmetric_difference(H[d - 1], H[d], std::back_inserter(diff));
            res += W * diff.size();
        }


        REP(i, N) {
            i32 p = A[d][i], q = W * (H[d][P[d][i] + 1] - H[d][P[d][i]]);
            if(p > q) res += 100 * (p - q);
        }

        // debug(d, res);
        return res;
    }

    auto calc_score() const {
        std::vector<i32> res(D);
        REP(d, D) res[d] = calc_score(d);
        return res;
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
        auto score = state.calc_score();
        debug(lib::sum(score));

        while(!timer.expired()) {
            i32 d = lib::randi32() % D;

            i32 i = lib::randi32() % N;
            i32 j = (i + 1 + lib::randi32() % (N - 1)) % N;
            // debug(d, i, j);

            std::swap(state.P[d][i], state.P[d][j]);
            state.update(d);

            spair<i32> new_score = { state.calc_score(d), state.calc_score(d + 1) };
            // debug(new_score);

            i32 diff = new_score.first - score[d];
            if(d + 1 < D) diff += new_score.second - score[d + 1];

            if(diff <= 0) {
                // debug(diff);
                score[d] = new_score.first;
                if(d + 1 < D) score[d + 1] = new_score.second;
                // break;
            }
            else {
                std::swap(state.P[d][i], state.P[d][j]);
                state.update(d);
            }
        }

        debug(state.P, state.H);
        debug(score, lib::sum(score));
        print(state.dump());
    }
}
