/*
 * @uni_kakurenbo
 * https://github.com/uni-kakurenbo/competitive-programming-workspace
 *
 * CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja
 */
/* #language C++ GCC */

#include <cstdlib>
#include <cassert>
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

    inline const auto& edges() const noexcept { return this->_edges; }
    inline const edge& get_edge(const size_type id) const noexcept { return this->_edges[id]; }

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

    inline std::unordered_set<size_type> find_detour(const size_type target) const noexcept {
        struct node {
            size_type id, edge = -1;
            cost_type total_cost = 0, estimated_cost = COST_INF;

            node(const size_type id = -1) : id(id) {}

            bool operator>(const node& other) const noexcept { return this->estimated_cost > other.estimated_cost; }
        };

        const size_type s = this->_edges[target].u, t = this->_edges[target].v;

        auto estimate = [this,&t](const size_type v) {
            size_type dx = this->_point[v].x - this->_point[t].x;
            size_type dy = this->_point[v].y - this->_point[t].y;
            return dx*dx + dy*dy;
            return 0;
        };

        std::unordered_map<size_type,node> nodes;
        std::priority_queue<node,std::vector<node>,std::greater<node>> open;

        open.emplace(s);

        while(not open.empty()) {
            const node u = open.top(); open.pop();

            // debug(s, t, u.id, u.total_cost);
            if(u.id == t) {
                // debug(u.total_cost);

                std::unordered_set<size_type> detour;

                size_type cur = u.edge;
                size_type v = u.id;
                while(cur >= 0) {
                    detour.insert(cur);
                    v = this->_edges[cur].to(v);
                    cur = nodes[v].edge;
                }

                return detour;
            }

            // if(f[u] < d) continue;

            for(const auto& e : this->_adjacencies[u.id]) {
                if(e == target) continue;

                const auto v = this->_edges[e].to(u.id);
                const auto w = this->_edges[e].cost;

                const cost_type cost = nodes[u.id].total_cost + w;;

                if(v == s) continue;
                if(nodes.count(v) and nodes[v].estimated_cost <= cost + estimate(v)) {
                    continue;
                }

                nodes[v].id = v;
                nodes[v].edge = e;
                nodes[v].total_cost = cost;
                nodes[v].estimated_cost = cost + estimate(v);

                open.push(nodes[v]);
            }
        }

        assert(false);
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


struct evaluator {
  private:
    const input& _in;

  public:
    std::vector<std::unordered_set<size_type>> detours;

    evaluator(const input& in) noexcept : _in(in), detours(in.E) { this->generate_detours(); }

    inline void generate_detours() noexcept {
        detours.resize(this->_in.E);
        for(size_type edge=0; edge<this->_in.E; ++edge) {
            this->detours[edge] = this->_in.G.find_detour(edge);
        }
    }

    score_type inline compute_sampled_day_score(const std::unordered_set<size_type>& ignored_edges) const noexcept {
        score_type sum = 0;
        for(const auto edge : ignored_edges) {
            for(const auto det : this->detours[edge]) {
                sum += ignored_edges.count(det);
            }
        }
        return sum;
    }

    score_type compute_sampled_score(const solution& schedule) const noexcept {
        score_type sum = 0;

        for(day_type d=0; d<this->_in.D; ++d) {
            sum += this->compute_sampled_day_score(schedule.edges[d]);
        }

        return sum;
    }

    score_type compute_sampled_score(const solution& schedule, std::vector<score_type> *const scores) const noexcept {
        score_type sum = 0;

        for(day_type d=0; d<this->_in.D; ++d) {
            sum += scores->operator[](d) = this->compute_sampled_day_score(schedule.edges[d]);
        }

        return sum;
    }

};

struct modifier {
    using neighbor_type = size_type;

  private:
    const input& _in;
    const evaluator& _eval;

  public:
    modifier(const input& in, const evaluator& eval) : _in(in), _eval(eval) {}

    inline neighbor_type choose(const timer::progress_type &progress) const {
        return 1;
    }

    inline void apply(solution *const days, const neighbor_type neighbor) const {
        day_type d0, d1;

        top:

        d0 = random(this->_in.D), d1 = (d0 + 1 + random(this->_in.D - 1)) % this->_in.D;

        if(neighbor == 0) {
            if(
                static_cast<day_type>(days->edges[d1].size()) + 1 > this->_in.K or
                static_cast<day_type>(days->edges[d0].size()) <= 0
            ) {
                goto top;
            }

            auto e = std::next(days->edges[d0].begin(), random(days->edges[d0].size()));
            days->edges[d1].insert(*e), days->edges[d0].erase(e);
        }

        if(neighbor == 1) {
            if(
                static_cast<day_type>(days->edges[d0].size()) <= 0 or
                static_cast<day_type>(days->edges[d1].size()) <= 0
            ) {
                goto top;
            }

            auto e0 = std::next(days->edges[d0].begin(), random(days->edges[d0].size()));
            days->edges[d1].insert(*e0), days->edges[d0].erase(e0);

            auto e1 = std::next(days->edges[d1].begin(), random(days->edges[d1].size()));
            days->edges[d0].insert(*e1), days->edges[d1].erase(e1);
        }

        for(const day_type day : { d0, d1 }) {
            const score_type diff = this->_eval.compute_sampled_day_score(days->edges[day]) - days->scores[day];
            days->scores[day] += diff;
            days->score += diff;
        }
    }
};

struct annealer {
  private:
    template<class data> struct state {
      private:
        data _current, _best, _saved;

      public:
        state(const data &init) : _current(init), _best(init), _saved(init) {}

        inline data& current() { return this->_current; }
        inline const data& best() const { return this->_best; }
        inline const data& saved() const { return this->_saved; }

        inline void update_best() {
            if(this->_current < this->_best) {
                this->_best = this->_current;
                if constexpr(DEVELOPMEMT_MODE) {
                    debug(this->_best.score);
                }
            }
        }
        inline void save() {  this->_saved = this->_current; }
        inline void rollback() { this->_current = std::move(this->_saved); }
    };

    const modifier &modify;

    double start_temp, end_temp, temp_change;

  public:
    annealer(const modifier &modify, const double start_temp, const double end_temp)
        : modify(modify), start_temp(start_temp), end_temp(end_temp), temp_change(end_temp - start_temp)
    {}

    solution anneal(solution const &days, const timer &timer) {
        state<solution> state(days);

        int loops = 0;
        while(true) {
            if(timer.expired()) {
                std::cerr << "Annealing: Iterations: " << loops << std::endl;
                break;
            }
            ++loops;

            const auto progress = timer.progress();
            const double temp = this->start_temp + this->temp_change * progress;
            // debug(progress, temp);

            state.save();

            const auto neighboor = this->modify.choose(progress);
            this->modify.apply(&state.current(), neighboor);

            const score_type score_diff = state.saved().score - state.current().score;
            // debug(score_diff);

            const double appling_probability = score_diff > 0 ? 1 : std::exp(score_diff / temp);
            if(appling_probability > random.real()) state.update_best();
            else state.rollback();
        }

        return state.best();
    }
};

} // namespace lib


signed main() {
    lib::timer timer(5950);

    lib::input in(&std::cin);

    lib::evaluator evaluator(in);

    lib::solution initial_solution(in.D);

    constexpr lib::size_type INITIAL_SOLUTION_SIZE = 1;

    debug(in.D, in.K);

    {
        std::vector<lib::day_type> days;
        days.reserve(in.D * in.K);

        for(lib::day_type d=0; d<in.D; ++d) {
            for(lib::day_type k=0; k<in.K; ++k) {
                days.push_back(d);
            }
        }

        for(lib::size_type i=0; i<INITIAL_SOLUTION_SIZE; ++i) {
            lib::timer time_count;

            std::shuffle(days.begin(), days.end(), lib::random);

            lib::solution temp_solution(in.D);
            for(lib::size_type e=0; e<in.E; ++e) {
                temp_solution.edges[days[e]].insert(e);
            }
            temp_solution.score = evaluator.compute_sampled_score(temp_solution);

            if(temp_solution < initial_solution) {
                initial_solution = std::move(temp_solution);
            }
        }

        evaluator.compute_sampled_score(initial_solution, &initial_solution.scores);
        debug(initial_solution.scores);
    }

    std::cerr << "Initial solution: internal score: " << initial_solution.score << "\n";

    lib::modifier modifier(in, evaluator);
    lib::annealer annealer(modifier, 0, 0);

    lib::solution solution = annealer.anneal(initial_solution, timer);
    // lib::solution solution = initial_solution;

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
