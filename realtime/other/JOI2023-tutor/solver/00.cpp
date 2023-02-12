/*
 * @uni_kakurenbo
 * https://github.com/uni-kakurenbo/competitive-programming-workspace
 *
 * CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja
 */
/* #language C++ GCC */
/* #region template */
#include <bits/stdc++.h>
using namespace std;

#include "template.hpp"
/* #endregion */

#include "random/xorshift.hpp"
#include "random/generator.hpp"
namespace sol {

struct xorshift {
    using result_type = std::uint32_t;

    static constexpr result_type MIN = std::numeric_limits<result_type>::min();
    static constexpr result_type MAX = std::numeric_limits<result_type>::max();

    static constexpr result_type min() { return MIN; }
    static constexpr result_type max() { return MAX; }

    inline void seed(unsigned int seed) { this->w = seed; }

    constexpr xorshift() {};
    constexpr xorshift(const std::uint32_t seed) : w(seed) {};

    inline std::uint32_t operator()() {
        std::uint32_t t;

        t = x ^ (x << 11);
        x = y; y = z; z = w;
        return w = (w ^ (w >> 19)) ^ (t ^ (t >> 8));
    }

  private:
    std::uint32_t x = 123456789;
    std::uint32_t y = 362436069;
    std::uint32_t z = 521288629;
    std::uint32_t w = 88675123;
};

struct xorshift64 {
    using result_type = std::uint64_t;

    static constexpr result_type MIN = std::numeric_limits<result_type>::min();
    static constexpr result_type MAX = std::numeric_limits<result_type>::max();

    static constexpr result_type min() { return MIN; }
    static constexpr result_type max() { return MAX; }

    inline void seed(unsigned int seed) { this->x = seed; }

    constexpr xorshift64() {};
    constexpr xorshift64(const std::uint64_t seed) : x(seed) {};

    inline std::uint64_t operator()() {
        x = x ^ (x << 13), x = x ^ (x <<  7), x = x ^ (x << 17);
        return x;
    }

  private:
    std::uint64_t x = 3141592653589793238UL;
};


template<class Engine> struct random_engine {
    using result_type = typename Engine::result_type;
    using signed_result_type = typename std::make_signed_t<result_type>;

  private:
    mutable Engine engine;

  public:
    static constexpr result_type MIN = Engine::min();
    static constexpr result_type MAX = Engine::max();

    static constexpr result_type min() { return MIN; }
    static constexpr result_type max() { return MAX; }

    constexpr random_engine(unsigned long seed = 3141592653UL) { this->engine.seed(seed); };

    inline result_type operator()() const {
        return this->engine();
    }

    inline result_type operator()(result_type max) const {
        if(max == 0) return 0;
        return (*this)() % max;
    }
    inline signed_result_type operator()(signed_result_type min, signed_result_type max) const {
        dev_assert(min <= max);
        return min + (*this)(max - min);
    };

    template<class T = ld> inline T real() const {
        return static_cast<T>(this->engine() + 0.5) / (1.0 + this->max());
    }
};


struct timer {
    using time = std::int32_t;
    using progress_type = ld;

  private:
    const time time_limit = 0;
    const progress_type progress_duration = 0;

    std::chrono::system_clock::time_point clock_start, clock_end;

  public:

    timer(const time time_limit = 0) noexcept : time_limit(time_limit),
        progress_duration(
            static_cast<progress_type>(
                std::chrono::duration_cast<std::chrono::system_clock::duration>(
                    std::chrono::milliseconds(time_limit)
                ).count()
            )
        )
    {
        this->reset();
    }

    inline time limit() noexcept { return this->time_limit; }

    inline timer* reset() noexcept {
        this->clock_start = std::chrono::system_clock::now();
        this->clock_end = clock_start + std::chrono::milliseconds(this->time_limit);
        return this;
    }

    inline time elapsed() const noexcept {
        return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - this->clock_start).count();
    }
    inline time remaining () const noexcept {
        return time_limit - this->elapsed();
    }

    inline bool expired() const noexcept { return this->elapsed() > time_limit; }
    inline progress_type progress() const noexcept {
        return (std::chrono::system_clock::now() - this->clock_start).count() / this->progress_duration;
    }
};

lib::random_engine<lib::xorshift> random;

constexpr int N = 400;

struct grid {
    vector<vector<int>> data;
    grid(const int n) : data(n, vector<int>(n, 0)) {}
    template<class stream> inline void read(stream *const in) {
        ITRR(row, data) ITRR(v, row) {
            char c; *in >> c;
            v = c - '0';
        }
    }
    inline const auto& operator[](int i) const { return data[i]; }
    inline auto& operator[](int i) { return data[i]; }
    auto _debug() const { return this->data; }
};

struct point {
    int x, y;
};

struct rectangle{
    int a, b, c, d;
    rectangle(int a, int b, int c, int d) : a(a), b(b), c(c), d(d) {}
    tuple<int,int,int,int> _debug() const { return { a, b, c, d }; }
};

using solution = vector<rectangle>;

struct evaluator {
    grid G;
    int A = 0;
    evaluator(const grid& G) : G(G) {
        REP(i, N) REP(j, N) this->A += this->G[i][j];
    };

    ld score(const solution& sol) {
        grid H(N);
        ITR(a, b, c, d, sol) {
            FOR(i, a, c) FOR(j, b, d) {
                H[i][j] = true;
            }
        }

        int B = 0, C = 0;
        REP(i, N) REP(j, N) {
            B += H[i][j];
            C += G[i][j] and H[i][j];
        }

        // debug(A, B, C);

        return 100000 * (ld)C / sqrt((ld)A * B);
    }
};


struct modifier {
  public:
    inline void apply(solution *const sol) noexcept {
        int rnd = random(sol->size());
        int rnd2 = random(4);
        if(rnd2 == 0) {
            sol->operator[](rnd).a += random(-1, 2);
            sol->operator[](rnd).a = clamp(sol->operator[](rnd).a, 0, N-1);
        }
        if(rnd2 == 1) {
            sol->operator[](rnd).b += random(-1, 2);
            sol->operator[](rnd).b = clamp(sol->operator[](rnd).b, 0, N-1);
        }
        if(rnd2 == 2) {
            sol->operator[](rnd).c += random(-1, 2);
            sol->operator[](rnd).c = clamp(sol->operator[](rnd).c, 0, N-1);
        }
        if(rnd2 == 3) {
            sol->operator[](rnd).d += random(-1, 2);
            sol->operator[](rnd).d = clamp(sol->operator[](rnd).d, 0, N-1);
        }
    }
};


struct annealer {
  private:
    template<class data> struct state {
      private:
        pair<data,ld> _current, _best, _saved;

      public:
        state(const pair<data,ld> &init) : _current(init), _best(init), _saved(init) {}

        inline auto& current() { return this->_current; }
        inline const auto& best() const { return this->_best; }
        inline const auto& saved() const { return this->_saved; }

        inline void update_best() {
            if(this->_current.second > this->_best.second) {
                this->_best = this->_current;
                debug(this->_best.second);
            }
        }
        inline void save() {  this->_saved = this->_current; }
        inline void rollback() { this->_current = std::move(this->_saved); }
        // inline void save() { logger->print_answer(this->_current), this->_saved = this->_current; }
    };

    evaluator &eval;
    modifier &mod;

    ld start_temp, end_temp, temp_change;

  public:
    annealer(evaluator &eval, modifier &mod, const ld start_temp, const ld end_temp)
        : eval(eval), mod(mod), start_temp(start_temp), end_temp(end_temp), temp_change(end_temp - start_temp)
    {}

    solution anneal(solution const &board, const timer &timer) {
        state<solution> state({ board, eval.score(board) });

        int count = 0;
        while(true) {
            count++;
            if(timer.expired()) {
                std::cerr << "Annealing: Iterations: " << count << std::endl;
                break;
            }

            const auto progress = timer.progress();
            const ld temp = this->start_temp + this->temp_change * progress;
            // debug(progress, temp);

            state.save();

            this->mod.apply(&state.current().first);
            state.current().second = this->eval.score(state.current().first);

            ld score_change = state.current().second - state.saved().second;

            const ld appling_probability = score_change > 0 ? 1 : std::exp(score_change / temp);
            if(appling_probability > random.real()) state.update_best();
            else state.rollback();
        }

        return state.best().first;
    }
};

}

signed main() {
    ifstream in("case.txt");
    if(!in) {
        debug("error");
        return 1;
    }

    sol::grid G(sol::N);
    G.read(&in);

    sol::evaluator eval(G);

    sol::solution solution = {
        { 98, 98, 261, 132 },
        { 132, 130, 280, 152 },
        { 150, 153, 290, 176 },
        { 168, 113, 234, 249 },
        { 188, 88, 249, 198 },
        { 225, 47, 264, 185 },
        { 252, 32, 329, 48 },
        { 292, 32, 313, 76 },
        { 80, 340, 100, 360 },
        { 0, 100, 0, 100}
    };

    // REP(i, 10) {
    //     solution.emplace_back(sol::random(sol::N), sol::random(sol::N), sol::random(sol::N), sol::random(sol::N));
    // }
    debug(solution);
    debug(eval.score(solution));

    sol::modifier mod;
    sol::annealer annealer(eval, mod, 500, 100);
    sol::timer timer(30000);
    solution = annealer.anneal(solution, timer);

    print(solution.size());
    REP(i, solution.size()) {
        print(solution[i].a, solution[i].b, solution[i].c, solution[i].d);
    }
    debug(eval.score(solution));

    return 0;
}
