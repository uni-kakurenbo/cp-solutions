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
    std::vector<atcoder::fenwick_tree<i32>> H;

    state() : H(D) {
        ITR(a, h, lib::views::zip(A, H)) {
            h = atcoder::fenwick_tree<i32>(N);

            std::vector<i32> t(N + 1);
            REP(i, N) t[i + 1] = std::clamp(t[i] + lib::div_ceil(a[i], W), i + 1, W - (N - i - 1));
            REP(i, N) h.add(i, t[i + 1] - t[i]);
        }
    }

    void swap(i32 d, i32 i, i32 j) {
        // i32 Hi = H[d].sum(i, i + 1);
        // i32 Hj = H[d].sum(j, j + 1);

        // H[d].add(i, Hj - Hi);
        // H[d].add(j, Hi - Hj);
    }

    i32 height(i32 d, i32 i) {
        return hline(d, i + 1) - hline(d, i);
    }

    i32 hline(i32 d, i32 i) {
        if(i == 0) return 0;
        if(i == N) return W;
        return std::clamp(H[d].sum(0, i), i, W - (N - i));
    }


    auto dump() {
        std::ostringstream res;

        REP(d, D) {
            REP(i, N) {
                res << hline(d, i) << lib::SPC;
                res << 0 << lib::SPC;
                res << hline(d, i + 1) << lib::SPC;
                res << W << lib::LN;
            }
        }

        return res.str();
    }


    i32 calc_score(const i32 d) {
        if(d >= D) return 0;

        i32 res = 0;

        if(d > 0) {
            std::vector<i32> prev(N - 1), cur(N - 1), diff;
            REP(i, N - 1) {
                prev[i] = hline(d - 1, i + 1);
                cur[i] = hline(d, i + 1);
            }

            std::ranges::set_symmetric_difference(prev, cur, std::back_inserter(diff));
            res += W * diff.size();
        }


        REP(i, N) {
            i32 p = A[d][i], q = W * height(d, i);
            if(p > q) res += 100 * (p - q);
        }

        // debug(d, res);
        return res;
    }

    auto calc_score() {
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

        int itr_count = 0;
        int accepted_count = 0;

        while(!timer.expired()) {
            i32 p = lib::randi32() % 2;

            i32 d = lib::randi32() % D;

            i32 i = lib::randi32() % N;
            i32 j = (i + 1 + lib::randi32() % (N - 1)) % N;
            // debug(d, i, j);

            i32 h = lib::randi32() % (lib::randi32() % (W / N) + 1) + 1;

            if(p) state.swap(d, i, j);
            else {
                state.H[d].add(i, h), state.H[d].add(j, -h);
            }

            spair<i32> new_score = { state.calc_score(d), state.calc_score(d + 1) };
            // debug(new_score);

            i32 diff = new_score.first - score[d];
            if(d + 1 < D) diff += new_score.second - score[d + 1];

            if(diff <= 0) {
                ++accepted_count;

                score[d] = new_score.first;
                if(d + 1 < D) score[d + 1] = new_score.second;

                // if(d == 0) {
                //     REP(i, N) std::cerr << state.H[0].sum(0, i + 1) << " ";
                //     std::cerr << "\n";
                // }
            }
            else {
                if(p) state.swap(d, i, j);
                else state.H[d].add(i, -h), state.H[d].add(j, h);
            }

            ++itr_count;
        }

        std::cerr << "iteration: " << itr_count << "\n";
        std::cerr << "accepted: " << accepted_count << "\n";
        std::cerr << "score: " << lib::sum(score) << "\n";

        debug(score);
        // REP(d, D) {
        //     REP(i, N) std::cerr << state.H[d].sum(i, i + 1) << " ";
        //     std::cerr << "\n";
        // }
        print(state.dump());
    }
}
