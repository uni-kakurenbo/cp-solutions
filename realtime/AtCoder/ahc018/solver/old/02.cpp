/*
 * @uni_kakurenbo
 * https://github.com/uni-kakurenbo/competitive-programming-workspace
 *
 * CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja
 */
/* #language C++ GCC */

#include <cstdlib>
#include <cstdint>
#include <cassert>

#include <iostream>

#include <vector>
#include <queue>
#include <unordered_set>
#include <unordered_map>
#include <set>
#include <bitset>

#include <algorithm>
#include <utility>
#include <cmath>
#include <chrono>

#include "internal/dev_assert.hpp"

#include "snippet/fast_io.hpp"
#include "snippet/iterations.hpp"
#include "snippet/aliases.hpp"

#include "graph/manhattan_minimum_spanning_tree.hpp"


#ifdef LOCAL_JUDGE

#include<debug>
#define debug(...) debugger::debug(debugger::split(#__VA_ARGS__), 0, __LINE__, __VA_ARGS__)
#define DEBUG(...) do { debugger::DEBUG(nullptr, "\033[3;35m#" + to_string(__LINE__) + "\033[m  "); debugger::DEBUG(__VA_ARGS__); debugger::DEBUG(nullptr, "\033[m\n"); } while(0);

constexpr bool DEVENOPMEMT_MODE = true;

#else

#define debug(...) { ; }
#define DEBUG(...) { ; }

constexpr bool DEVENOPMEMT_MODE = false;

#endif


namespace lib {

struct uncopyable {
    constexpr uncopyable(){}
    uncopyable(const uncopyable&) = delete;
    uncopyable& operator=(const uncopyable&) = delete;
};

struct xorshift : private uncopyable {
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

struct xorshift64 : private uncopyable {
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


template<class Engine> struct random_engine : private uncopyable {
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

    template<class T = double> inline T real() const {
        return static_cast<T>(this->engine() + 0.5) / (1.0 + this->max());
    }
};


struct timer : private uncopyable {
    using time = std::int32_t;
    using progress_type = double;

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

using size_t = int;
using cost_t = int;

constexpr size_t N = 200;
constexpr size_t S = N*N;

enum class response { not_broken, broken, finish, invalid };

struct point {
    size_t row = -1, col = -1;

    point() {}
    point(size_t i, size_t j) : row(i), col(j) {}
    point(size_t id) : row(id/N), col(id%N) {}

    size_t dist_m(const point& other) const { return std::abs(this->row - other.row) + std::abs(this->col - other.col); }

    bool valid() const { return 0 <= row && row < N and 0 <= col && col < N; }
    explicit operator bool() const { return this->valid(); }
    size_t id() const { return row * N + col; }

    std::pair<size_t,size_t> _debug() const { return { this->row, this->col }; }
};

struct field : private uncopyable {
    cost_t C = -1, total_cost = 0;
    size_t W, K;
    std::bitset<S> broken;
    std::vector<point> sources, targets;

    field() {}
    void input() {
        dev_assert(this->C < 0);

        size_t _;
        std::cin >> _ >> this->W >> this->K >> this->C;

        this->sources.resize(this->W), this->targets.resize(this->K);

        ITRR(source, this->sources) {
            size_t i, j; std::cin >> i >> j;
            source = { i, j };
        }
        ITRR(target, this->targets) {
            size_t i, j; std::cin >> i >> j;
            target = { i, j };
        }
    }

    void set_broken(const size_t i, const size_t j) { this->broken.set(i*N + j); }
    void set_broken(const point p) { this->broken.set(p.id()); }

    response excavate(const point p, const cost_t c) { return this->excavate(p.row, p.col, c); }
    response excavate(const size_t i, const size_t j, const cost_t p) {
        this->total_cost += this->C + p;
        std::cout << i << " " << j << " " << p << std::endl;
        int res; std::cin >> res;
        switch(res) {
          case 0:
            return response::not_broken;
          case 1:
            this->set_broken(i, j);
            return response::broken;
          case 2:
            this->set_broken(i, j);
            return response::finish;
          default:
            return response::invalid;
        }
    }
};

} // namespace lib

struct solver : lib::uncopyable {
    lib::field *const F;
    std::vector<std::pair<lib::point,lib::point>> plan;

    solver(lib::field *const F) : F(F) {}

    void solve() {
        schedule();
        ITR(s, t, this->plan) this->move(s, t);
        assert(false);
    }

    void schedule() {
        const lib::size_t W = this->F->W, K = this->F->K;

        auto point = [this,W](lib::size_t i) -> lib::point& {
            if(i < W) return this->F->sources[i];
            else return this->F->targets[i-W];
        };

        std::vector<lib::size_t> xs(W+K), ys(W+K);
        REP(i, W+K) {
            xs[i] = point(i).row;
            ys[i] = point(i).col;
        }

        auto mst = lib::manhattan_mst_edges(xs, ys);
        ITR(i, j, k, mst) {
            debug(i, j, k);
            this->plan.emplace_back(point(i), point(j));
        }
    }

    void move(lib::point start, lib::point goal) {
        std::cout << "# move from (" << start.row << "," << start.col << ") to (" << goal.row << "," << goal.col << ")" << std::endl;

        if(start.row < goal.row) {
            for(lib::size_t i = start.row; i < goal.row; i++) {
                destruct(i, start.col);
            }
        }
        else {
            for(lib::size_t i = start.row; i > goal.row; i--) {
                destruct(i, start.col);
            }
        }

        if(start.col < goal.col) {
            for(lib::size_t j = start.col; j <= goal.col; j++) {
                destruct(goal.row, j);
            }
        }
        else{
            for (lib::size_t j = start.col; j >= goal.col; j--) {
                destruct(goal.row, j);
            }
        }
    }

    void destruct(size_t i, size_t j) {
        const int power = 100;

        while(not this->F->broken.test(i*lib::N + j)) {
            lib::response result = this->F->excavate(i, j, power);
            if (result == lib::response::finish) {
                std::cerr << "Total Cost: " << this->F->total_cost << std::endl;
                exit(0);
            } else if (result == lib::response::invalid) {
                std::cerr << "Invalid: (" << i << ", " << j << ")" << std::endl;
                exit(1);
            }
        }

    }
};

signed main() {
    lib::field F; F.input();

    solver sol(&F);

    sol.solve();
}
