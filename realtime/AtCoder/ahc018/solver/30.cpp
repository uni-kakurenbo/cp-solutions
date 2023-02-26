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

#include <type_traits>

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


template<class T> T hypot2(const T x, const T y) { return x*x + y*y; }

struct point {
    size_t row = -1, col = -1;

    point() {}
    point(size_t i, size_t j) : row(i), col(j) {}
    explicit point(size_t id) : row(id/N), col(id%N) {}

    inline size_t dist_m(const point other) const { return std::abs(this->row - other.row) + std::abs(this->col - other.col); }
    inline size_t dist_e(const point other) const { return hypot2(this->row - other.row, this->col - other.col); }

    inline point& operator+=(const point other) { this->row += other.row; this->col += other.col; return *this; }
    inline point& operator-=(const point other) { this->row -= other.row; this->col -= other.col; return *this; }

    template<class T, std::enable_if_t<std::is_arithmetic_v<T>>* = nullptr>
    inline point& operator+=(const T x) { this->row += x, this->col += x; return *this; }

    template<class T, std::enable_if_t<std::is_arithmetic_v<T>>* = nullptr>
    inline point& operator-=(const T x) { this->row -= x, this->col -= x; return *this; }

    template<class T, std::enable_if_t<std::is_arithmetic_v<T>>* = nullptr>
    inline point& operator*=(const T x) { this->row *= x, this->col *= x; return *this; }

    template<class T, std::enable_if_t<std::is_arithmetic_v<T>>* = nullptr>
    inline point& operator/=(const T x) { this->row /= x, this->col /= x; return *this; }

    template<class T> inline point operator-(const T other) const { auto res = *this; return res -= other; }
    template<class T> inline point operator+(const T other) const { auto res = *this; return res += other; }
    template<class T> inline point operator*(const T other) const { auto res = *this; return res *= other; }
    template<class T> inline point operator/(const T other) const { auto res = *this; return res /= other; }

    inline bool operator==(const point other) const { return this->row == other.row && this->col == other.col; }
    inline bool operator!=(const point other) const { return this->row != other.row || this->col != other.col; }

    inline bool operator<(const point other) const { return this->col == other.col ? this->row < other.row : this->col < other.col; }

    inline bool valid() const { return 0 <= this->row && this->row < N and 0 <= this->col && this->col < N; }
    inline explicit operator bool() const { return this->valid(); }
    inline size_t id() const { return row * N + col; }

    inline point& clamp() { this->row = std::clamp(this->row, 0, lib::N-1), this->col = std::clamp(this->col, 0, lib::N-1); return *this; }

    inline pair<size_t> _debug() const { return { this->row, this->col }; }
};

size_t cross(const point o, const point a, const point b) {
    return (a.col - o.col) * (b.row - o.row) - (a.row - o.row) * (b.col - o.col);
};

template<class T> T average(const T a, const T b) { return (a + b) >> 1; }
template<class T> T average(const std::initializer_list<T> list) { return std::accumulate(list) / list.size(); }


struct field : private uncopyable {
    cost_t C = -1, total_cost = 0;
    size_t W, K;
    std::bitset<S> broken, reached;
    std::vector<point> sources, targets;

    inline bool is_source(size_t k) { return k < this->W; };
    inline bool is_target(size_t k) { return k >= this->W; };

    // 0 <= k < W: source, W <= k: target
    inline point& get_point(size_t k) {
        if(k < this->W) return this->sources[k];
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

        REP(i, this->W) this->reached.set(this->get_point(i).id());
    }

    inline void set_broken(const size_t i, const size_t j) { this->broken.set(i*N + j); }
    inline void set_broken(const point p) { this->broken.set(p.id()); }

    bool is_reached(const point p) {
        std::bitset<lib::S> seen;

        auto dfs = [&](auto&& dfs, const point cur) mutable -> bool {
            if(!cur) return false;
            if(this->reached.test(cur.id())) return true;
            if(not this->broken.test(cur.id())) return false;
            if(seen.test(cur.id())) return false;

            seen.set(cur.id());

            dev_assert(this->broken.test(cur.id()));

            bool res = false;
            ITR(di, dj, DIRS4) {
                const point next = cur + point{ di, dj };
                res |= dfs(dfs, next);
            }

            return this->reached[cur.id()] = res;
        };

        return dfs(dfs, p);
    }

    inline bool excavate(const point p, const cost_t c) { return this->excavate(p.row, p.col, c); }
    bool excavate(const size_t i, const size_t j, const cost_t p) {
        this->total_cost += this->C + p;
        std::cout << i << " " << j << " " << p << std::endl;
        int res; std::cin >> res;
        switch(res) {
          case 0:
            return false;

          case 1:
            this->set_broken(i, j);
            return true;

          case 2:
            this->set_broken(i, j);
            std::cerr << "Total Cost: " << this->total_cost << std::endl;
            exit(0);

          default:
            std::cerr << "Invalid: (" << i << ", " << j << ")" << std::endl;
            exit(1);
        }
    }
};

} // namespace lib

struct solver : lib::uncopyable {
    using size_t = lib::size_t;
    using cost_t = lib::cost_t;

    using point = lib::point;
    struct section : point {
        using point::point;
        section(const point p) : point(p) {}
    };


    lib::field *const F;

    size_t D = 11, H = (lib::N + D - 1) / D;

    std::vector<size_t> connect_order;
    std::vector<cost_t> levels;

    size_t prediction[lib::S] = {};

    cost_t standard_power;

    bool samplabe = true;

    solver(lib::field *const F) : F(F), levels(H*H), standard_power(15 * std::sqrt(this->F->C)) {}

    void solve() {
        this->schedule();

        // std::vector<cost_t> costs(this->F->K);
        // REP(i, this->F->K) costs[i] = this->find_source(this->F->get_point(i));
        // debug(costs);

        // std::sort(ALL(this->connect_order), [&costs](const size_t i, const size_t j) { return costs[i] < costs[j]; });

        // this->samplabe = false;

        ITR(i, this->connect_order) this->connect(this->F->get_point(i));

        assert(false);
    }

    bool is_valid(const section t) const { return 0 <= t.row && t.row < this->H and 0 <= t.col && t.col < this->H; }
    size_t get_id(const section t) const { return t.row * this->H + t.col; }

    section to_section(const size_t p) const { return { p / this->H, p % this->H }; }

    section get_section(const point p) const {
        return { p.row / this->D, p.col / this->D };
    }

    point get_leader(const section t) const { return (t * this->D + this->D / 2).clamp(); }
    point get_leader(const point p) const { return this->get_leader(this->get_section(p)); }

    cost_t level(const section t) {
        const point p = this->get_leader(t);
        const size_t id = this->get_id(t);

        if(not this->samplabe) return this->levels[id] == 0 ? 15000 : this->levels[id];
        if(this->levels[id] > 0) return this->levels[id];

        lib::cost_t bounds[] = { 50, 200 };

        lib::cost_t prev = 0;
        REP(bound, std::begin(bounds), std::end(bounds)) {
            this->F->excavate(p, *bound - prev);
            if(this->F->broken.test(p.id())) return this->levels[id] = *bound;
            prev = *bound;
        }

        return this->levels[id] = 15000;
    }

    void schedule() {
        const lib::size_t W = this->F->W, K = this->F->K;

        std::vector costs(W+K, std::vector<lib::cost_t>(W+K));
        REP(i, W+K) REP(j, i+1, W+K) {
            costs[i][j] = costs[j][i] = this->F->get_point(i).dist_m(this->F->get_point(j));
        }
        debug(costs);

        std::vector<lib::size_t> dists(W+K, std::numeric_limits<lib::size_t>::max());
        {
            using state = std::pair<lib::cost_t,lib::size_t>;

            std::priority_queue<state,std::vector<state>,std::greater<state>> que;

            REP(i, W) que.emplace(0, i), dists[i] = 0;

            while(not que.empty()) {
                auto [ d, p ] = que.top(); que.pop();
                if(dists[p] < d) continue;

                REP(q, W, W+K) {
                    if(!lib::point{q}) continue;

                    lib::cost_t cost = costs[p][q];

                    if(dists[q] <= d + cost) continue;

                    dists[q] = d + cost;
                    que.emplace(dists[q], q);
                }
            }
        }

        this->connect_order.resize(this->F->K);
        std::iota(ALL(this->connect_order), this->F->W);

        std::sort(ALL(this->connect_order), [&dists](const int i, const int j) { return dists[i] < dists[j]; });
    }

    void connect(point start) {
        std::vector<point> path;
        this->find_source(start, &path);

        debug(start, path);

        ITR(p, path) {
            auto next_point = [p](const lib::point cur) {
                lib::size_t min_dist = std::numeric_limits<lib::size_t>::max();
                lib::point next;
                ITR(di, dj, DIRS4) {
                    lib::point cand = { cur.row + di, cur.col + dj};
                    if(chmin(min_dist, p.dist_e(cand))) next = cand;
                }
                return next;
            };

            while(start != p) {
                std::cout << "# connect from (" << start.row << "," << start.col << ") to (" << p.row << "," << p.col << ")" << std::endl;
                this->destruct(start);
                start = next_point(start);
            }
            this->destruct(start);
        }
    }

    cost_t find_source(const point start, std::vector<point> *const path = nullptr) {
        const section s = this->get_section(start);

        struct node {
            size_t id, prev = -1;
            cost_t total_cost = 0, estimated_cost = 1 << 30;
            node(const size_t id = -1) : id(id) {}

            bool operator>(const node& other) const noexcept { return this->estimated_cost > other.estimated_cost; }
        };

        auto estimate = [this](const size_t v) {
            point p = this->get_leader(this->to_section(v));
            if(this->F->is_reached(p)) return 0;

            cost_t dist = std::numeric_limits<cost_t>::max();

            auto apply = [this,&dist,p](const point q) mutable {
                if(not this->F->is_reached(q)) return;
                chmin(dist, p.dist_m(q));
            };

            REP(i, this->H * this->H) apply(this->get_leader(this->to_section(i)));
            REP(i, this->F->W + this->F->K) apply(this->F->get_point(i));

            return dist*dist;
        };

        std::unordered_map<size_t,node> nodes;
        std::priority_queue<node,std::vector<node>,std::greater<node>> que;

        nodes[this->get_id(s)] = this->get_id(s);
        que.emplace(this->get_id(s));

        while(not que.empty()) {
            node u = que.top(); que.pop();
            const section p = this->to_section(u.id);

            ITR(di, dj, DIRS4) {
                const section q = p + section{ di, dj };
                const size_t v = this->get_id(q);

                if(not this->is_valid(q)) continue;

                auto found = [&](const point t) mutable -> bool {
                    if(not this->F->is_reached(t)) return false;

                    const section g = this->get_section(t);

                    if(q != g) return false;

                    if(path) {
                        while(true) {
                            path->push_back(this->get_leader(this->to_section(u.id)));
                            if(u.prev < 0) break;
                            u = nodes[u.prev];
                        }
                        if(not this->F->is_reached(path->back())) path->pop_back();
                        std::reverse(path->begin(), path->end());
                        path->push_back(t);
                    }

                    return true;
                };

                REP(i, this->H * this->H) if(found(this->get_leader(this->to_section(i)))) return u.total_cost;
                REP(i, this->F->W + this->F->K) if(found(this->F->get_point(i))) return u.total_cost;

                const cost_t w = this->F->is_reached(this->get_leader(q)) ? 0 : this->level(q);
                const cost_t cost = nodes[u.id].total_cost + w;

                if(q == s) continue;
                if(nodes.count(v) and nodes[v].estimated_cost <= cost + estimate(v)) {
                    continue;
                }

                nodes[v].id = v, nodes[v].prev = u.id;
                nodes[v].total_cost = cost;
                nodes[v].estimated_cost = cost + estimate(v);

                que.push(nodes[v]);
            }
        }

        assert(false);
    }

    int destruct(const point p) {
        if(this->F->broken.test(p.id())) return 1;

        cost_t power = std::min(this->standard_power, this->level(this->get_section(p)));

        while(not this->F->broken.test(p.id())) {
            this->F->excavate(p, power);
        }

        return 0;
    }
};

signed main() {
    lib::field F; F.input();

    solver sol(&F);

    sol.solve();
}
