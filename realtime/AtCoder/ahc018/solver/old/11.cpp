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
#include <fstream>

#include <vector>
#include <array>
#include <queue>
#include <unordered_set>
#include <unordered_map>
#include <set>
#include <bitset>
#include <initializer_list>

#include <algorithm>
#include <numeric>
#include <utility>
#include <cmath>
#include <chrono>

#include "internal/dev_assert.hpp"

#include "snippet/fast_io.hpp"
#include "snippet/iterations.hpp"
#include "snippet/aliases.hpp"

#include "data_structure/disjoint_set_union.hpp"
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


template<class T> T hypot2(const T x, const T y) { return x*x + y*y; }

template<class T> T average(const T a, const T b) { return (a + b) >> 1; }
template<class T> T average(const std::initializer_list<T> list) { return std::accumulate(list) / list.size(); }


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

template<class T> using pair = std::pair<T,T>;

enum class response { not_broken, broken, finish, invalid };

struct point {
    size_t row = -1, col = -1;

    point() {}
    point(size_t i, size_t j) : row(i), col(j) {}
    point(size_t id) : row(id/N), col(id%N) {}

    inline size_t dist_m(const point other) const { return std::abs(this->row - other.row) + std::abs(this->col - other.col); }
    inline size_t dist_e(const point other) const { return hypot2(this->row - other.row, this->col - other.col); }

    inline point& operator-=(const point other) { this->row -= other.row; this->col -= other.col; return *this; }
    inline point& operator+=(const point other) { this->row += other.row; this->col += other.col; return *this; }

    inline point operator-(const point other) const { auto res = *this; return res -= other; }
    inline point operator+(const point other) const { auto res = *this; return res += other; }

    inline bool operator==(const point other) const { return this->row == other.row && this->col == other.col; }
    inline bool operator!=(const point other) const { return this->row != other.row || this->col != other.col; }

    inline bool valid() const { return 0 <= this->row && this->row < N and 0 <= this->col && this->col < N; }
    inline explicit operator bool() const { return this->valid(); }
    inline size_t id() const { return row * N + col; }

    inline pair<size_t> _debug() const { return { this->row, this->col }; }
};

struct field : private uncopyable {
    cost_t C = -1, total_cost = 0;
    size_t W, K;
    std::bitset<S> broken;
    std::vector<point> sources, targets;

    inline bool is_source(size_t k) { return k < this->W; };
    inline bool is_target(size_t k) { return k >= this->W; };

    // 0 <= k < W: source, W <= k: target
    inline lib::point& get_point(size_t k) {
        if(k < W) return this->sources[k];
        else return this->targets[k-W];
    };

    field() {}
    inline void input() {
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

    inline void set_broken(const size_t i, const size_t j) { this->broken.set(i*N + j); }
    inline void set_broken(const point p) { this->broken.set(p.id()); }

    inline response excavate(const point p, const cost_t c) { return this->excavate(p.row, p.col, c); }
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

    std::vector<std::vector<lib::size_t>> plan;
    std::vector<lib::point> samples;

    std::size_t prediction[lib::S] = {};

    std::vector<bool> reached;

    lib::pair<lib::cost_t> costs[lib::S] = {};

    lib::cost_t power = 50;

    solver(lib::field *const F) : F(F), plan(F->W + F->K), reached(F->W + F->K) {}

    void solve() {
        this->sample_strength();
        this->predict_strength();

        this->schedule();

        this->connect();

        assert(false);
    }

    void sample_strength() {
        const lib::size_t interval = 20;
        const lib::size_t dv = interval * std::sqrt(3)/2, dh = interval;

        int row = 0;
        REP(i, 0, lib::N, dv) {
            REP(j, 0, lib::N, dh) {
                lib::point p = { i + dv, j + (1 + row%2) * dh/2 };
                if(!p) continue;
                this->samples.push_back(p);
                const int res = this->destruct(p, 10 * std::sqrt(this->F->C), 500);
                if(res == 2) this->costs[p.id()].second = 3000;
                debug(i, j, p, this->costs[p.id()]);
            }
            row += 1;
        }
    }

    void predict_strength() {
        REP(i, lib::S) {
            const lib::point p = i;
            ld w = 0, s = 0;
            ITR(sample, this->samples) {
                if(i == sample.id()) {
                    this->prediction[i] = this->costs[i].second;
                    goto end;
                }

                w += this->costs[sample.id()].second * 1.0 / p.dist_e(sample);
                s += 1.0 / p.dist_e(sample);
            }
            this->prediction[i] = w / s;
            end:;
        }

        // REP(i, lib::S) {
        //     const
        //     REP()
        //     this->prediction[i] = w / s;
        // }

        std::ofstream prediction_log(".pred");
        dev_assert(prediction_log.good());

        REP(i, lib::N) {
            REP(j, lib::N) {
                prediction_log << this->prediction[lib::point{ i, j }.id()] << " ";
            }
            prediction_log << "\n";
        }
    }

    void connect() {
        std::queue<std::size_t> que;

        REP(i, this->F->W) que.push(i), this->reached[i] = true;

        while(not que.empty()) {
            const lib::size_t s = que.front(); que.pop();
            const auto p = this->F->get_point(s);
            ITR(t, this->plan[s]) {
                if(this->reached[t]) continue;
                const auto q = this->F->get_point(t);
                debug(s, t, p, q);
                this->move(p, q);
                this->reached[t] = true;
                que.push(t);
            }
        }
    }

    void schedule() {
        const lib::size_t W = this->F->W, K = this->F->K;

        std::vector<lib::size_t> xs(W+K), ys(W+K);
        REP(i, W+K) {
            xs[i] = this->F->get_point(i).row;
            ys[i] = this->F->get_point(i).col;
        }

        auto mst = lib::manhattan_mst_edges(xs, ys);
        ITR(i, j, k, mst) {
            if(this->F->is_source(i) and this->F->is_source(j)) continue;
            this->plan[i].push_back(j), this->plan[j].push_back(i);
        }
    }

    void move(lib::point start, const lib::point goal) {
        std::cout << "# move from (" << start.row << "," << start.col << ") to (" << goal.row << "," << goal.col << ")" << std::endl;

        std::vector<lib::point> path;

        {
            using state = std::pair<lib::cost_t,lib::size_t>;

            std::priority_queue<state,std::vector<state>,std::greater<state>> que;
            std::array<lib::size_t,lib::S> dists; dists.fill(std::numeric_limits<lib::size_t>::max());
            std::array<lib::size_t,lib::S> prev; prev.fill(-1);

            que.emplace(0, start.id()), dists[start.id()] = 0;

            while(not que.empty()) {
                auto [ d, p ] = que.top(); que.pop();

                if(p == goal.id()) {
                    while(true) {
                        path.push_back(lib::point{p});
                        if(!lib::point{prev[p]}) break;
                        p = prev[p];
                    }
                    break;
                }

                if(dists[p] < d) continue;

                ITR(di, dj, DIRS4) {
                    auto q = lib::point{p} + lib::point{ di, dj };
                    if(!q) continue;

                    lib::cost_t cost = 0;
                    if(not this->F->broken.test(q.id())) cost = this->prediction[q.id()];

                    if(dists[q.id()] <= d + cost) continue;

                    dists[q.id()] = d + cost;
                    prev[q.id()] = p;

                    que.emplace(dists[q.id()], q.id());
                }
            }
        }
        // std::reverse(ALL(path));
        // debug(path);

        ITR(p, path) this->destruct(p, 10 * std::sqrt(this->F->C));
    }


    int destruct(const lib::point p, lib::cost_t power = -1, const lib::cost_t limit = 10000) {
        if(this->F->broken.test(p.id())) return 1;

        // lib::cost_t expected_strength = this->predict_strength(p);

        // dev_assert(10 <= expected_strength && expected_strength <= 5000);
        // std::cout << "# expected: " << expected_strength << std::endl;

        // if(power < 0) power = this->prediction[p.id()];

        while(not this->F->broken.test(p.id())) {
            if(this->costs[p.id()].second > limit) return 2;

            lib::response result = this->F->excavate(p, power);

            this->costs[p.id()].first = this->costs[p.id()].second;
            this->costs[p.id()].second += power;

            if (result == lib::response::finish) {
                std::cerr << "Total Cost: " << this->F->total_cost << std::endl;
                exit(0);
            }
            if (result == lib::response::invalid) {
                std::cerr << "Invalid: (" << p.row << ", " << p.col << ")" << std::endl;
                exit(1);
            }

            // power /= 10;
            // chmax(power, 50);
        }

        std::cout << "# expected: (" << this->costs[p.id()].first << ", " << this->costs[p.id()].second << "]" << std::endl;

        return 0;
    }
};

signed main() {
    lib::field F; F.input();

    solver sol(&F);

    sol.solve();
}
