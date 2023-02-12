/*
 * @uni_kakurenbo
 * https://github.com/uni-kakurenbo/competitive-programming-workspace
 *
 * CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja
 */
/* #language C++ GCC */

#include <cstdlib>
#include <cstdint>

#include <iostream>

#include <vector>
#include <queue>
#include <unordered_set>
#include <unordered_map>
#include <set>

#include <algorithm>
#include <utility>
#include <cmath>
#include <chrono>


#ifdef LOCAL_JUDGE

#include<debug>
#define debug(...) debugger::debug(debugger::split(#__VA_ARGS__), 0, __LINE__, __VA_ARGS__)
#define DEBUG(...) do { debugger::DEBUG(nullptr, "\033[3;35m#" + to_string(__LINE__) + "\033[m  "); debugger::DEBUG(__VA_ARGS__); debugger::DEBUG(nullptr, "\033[m\n"); } while(0);

#define dev_assert(...) assert(__VA_ARGS__)

constexpr bool DEVELOPMEMT_MODE = true;

#else

#define debug(...) { ; }
#define DEBUG(...) { ; }
#define dev_assert(...) { ; }

constexpr bool DEVELOPMEMT_MODE = false;

#endif


namespace lib {


using size_type = std::int16_t;
using pos_type = std::int32_t;
using day_type = std::int16_t;

using cost_type = std::int32_t;
using score_type = std::int64_t;

constexpr cost_type COST_INF = 2000000000;

template<class T> T hypot2(const T x, const T y) { return x*x + y*y; }

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

    template<class T = double> inline T real() const {
        return static_cast<T>(this->engine() + 0.5) / (1.0 + this->max());
    }
};


struct timer {
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

struct point {
    pos_type x = -1, y = -1;
};

struct graph {
    struct edge {
        const size_type u, v;
        const cost_type cost;

        edge(const size_type u, const size_type v, const cost_type w) noexcept : u(u), v(v), cost(w) {}

        inline size_type to(const size_type from) const noexcept {
            dev_assert(from == this->u or from == this->v);
            return from == this->u ? this->v : this->u;
        }
    };

  private:
    std::vector<point> _point;
    std::vector<edge> _edges;
    std::vector<std::vector<size_type>> _adjacencies;

  public:
    graph(const size_type v = 0) noexcept : _point(v), _adjacencies(v) {}

    inline size_type size() const noexcept { return this->_adjacencies.size(); }

    inline point& get_node(const size_type id) noexcept { return this->_point[id]; }
    inline const point& get_node(const size_type id) const noexcept { return this->_point[id]; }

    inline const edge& get_edge(const size_type id) const noexcept { return this->_edges[id]; }

    inline const auto& adjacencies(const size_type node) const noexcept { return this->_adjacencies[node]; }

    inline void add_edge(const size_type u, const size_type v, const cost_type w) noexcept {
        this->_adjacencies[v].emplace_back(this->_edges.size());
        this->_adjacencies[u].emplace_back(this->_edges.size());
        this->_edges.emplace_back(u, v, w);
    }

    inline auto compute_costs(const size_type s, const std::unordered_set<size_type>& ignored_edges = {}) const noexcept {
        using state = std::pair<cost_type,size_type>;

        std::priority_queue<state,std::vector<state>,std::greater<state>> que;

        std::vector<cost_type> costs(this->size(), COST_INF);

        que.emplace(0, s), costs[s] = 0;

        while(not que.empty()) {
            const auto [d, u] = que.top(); que.pop();

            if(costs[u] < d) continue;

            for(const auto& e : this->_adjacencies[u]) {
                if(ignored_edges.count(e)) continue;

                const auto v = this->_edges[e].to(u);
                const auto w = this->_edges[e].cost;

                if(costs[v] <= d + w) continue;

                costs[v] = d + w;
                que.emplace(costs[v], v);
            }
        }

        return costs;
    }

    inline auto compute_cost_matrix(const std::unordered_set<size_type>& ignored_edges = {}) const noexcept {
        std::vector<std::vector<cost_type>> costs;
        costs.reserve(this->size());

        for(size_type v=0; v<this->size(); ++v) {
            costs.emplace_back(this->compute_costs(v, ignored_edges));
        }

        return costs;
    }
};


struct input {
    size_type V, E;
    day_type D, K;

    graph G;

    template<class istream> input(istream *const in) noexcept {
        *in >> this->V >> this->E >> this->D >> this->K;
        this->G = graph(this->V);

        for(size_type i=0; i<this->E; ++i) {
            size_type u, v; cost_type w;
            *in >> u >> v >> w;
            this->G.add_edge(u-1, v-1, w >> 5);
        }

        for(size_type i=0; i<this->V; ++i) {
            *in >> this->G.get_node(i).x >> this->G.get_node(i).y;
            this->G.get_node(i).x -= 500, this->G.get_node(i).y -= 500;
        }
    }
};

lib::random_engine<lib::xorshift> random;


struct solution {
  private:
    size_type _D;

  public:
    std::vector<std::unordered_set<size_type>> edges;

    score_type score = std::numeric_limits<lib::score_type>::max();
    std::vector<score_type> scores;

    solution(const day_type D) noexcept : _D(D), edges(D), scores(D, std::numeric_limits<lib::score_type>::max()) {}

    inline std::vector<day_type> build(const size_type E) const noexcept {
        std::vector<day_type> res(E);

        for(day_type d=0; d<this->_D; ++d) {
            for(const size_type edge : edges[d]) {
                res[edge] = d;
            }
        }

        return res;
    }

    inline bool operator<(const solution& other) const noexcept { return this->score < other.score; }
};

} // namespace lib


signed main() {
    lib::timer timer(5950);

    lib::input in(&std::cin);

    lib::solution solution(in.D);

    {
        std::unordered_set<lib::size_type> edges;
        for(lib::size_type e=0; e<in.E; ++e) edges.insert(e);

        for(lib::day_type d=0; d<in.D; ++d) {

            auto edge = lib::random(in.E);
            auto node = in.G.get_edge(edge).v;
            const auto goal = in.G.get_node(lib::random(in.V));

            lib::size_type p_edge = -1, p_node = -1;
            for(lib::day_type i=0; i<in.E/in.D; ++i) {
                solution.edges[d].insert(edge);
                edges.erase(edge);
                const auto& adjs = in.G.adjacencies(node);
                auto n_edge = 0;
                auto n_node = 0;

                const lib::pos_type min_d = std::numeric_limits<lib::pos_type>::max();
                for(lib::size_type e=0; e<adjs.size(); ++e) {
                    const auto t = in.G.get_edge(adjs[e]).to(node);
                    const auto d = lib::hypot2(in.G.get_node(t).x - goal.x, in.G.get_node(t).y - goal.y);
                    if(t != p_node and d < min_d) n_edge = adjs[e], n_node = t;
                }

                p_edge = edge, p_node = node;
                edge = n_edge, node = n_node;
            }
            solution.edges[d].insert(edge);
            edges.erase(edge);
        }

        // debug(edges);
    }

    std::cerr << "Initial solution: internal score: " << solution.score << "\n";

    {
        const std::vector<lib::day_type> days = solution.build(in.E);
        for(lib::size_type e=0; e<in.E; ++e) {
            std::cout << days[e] + 1 << " ";
        }
        std::cout << std::endl;
    }

    std::cerr << "Best internal score: " << solution.score << "\n";

    return EXIT_SUCCESS;
}
