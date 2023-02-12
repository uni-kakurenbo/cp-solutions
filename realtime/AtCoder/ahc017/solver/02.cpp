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

#include <algorithm>
#include <utility>
#include <chrono>

#include "random/xorshift.hpp"
#include "random/generator.hpp"


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
using day_type = std::int16_t;

using cost_type = std::int32_t;
using score_type = std::int64_t;

constexpr cost_type COST_INF = 1000000000;


struct timer {
    using time = std::int32_t;
    using Progress = double;

  private:
    const time time_limit = 0;
    const Progress progress_duration = 0;

    std::chrono::system_clock::time_point clock_start, clock_end;

  public:

    timer(const time time_limit = 0) noexcept : time_limit(time_limit),
        progress_duration(
            static_cast<Progress>(
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
    inline Progress progress() const noexcept {
        return (std::chrono::system_clock::now() - this->clock_start).count() / this->progress_duration;
    }
};

struct graph {
    struct edge {
        size_type u, v;
        cost_type cost;

        size_type used_count = 0;

        edge(const size_type u, const size_type v, const cost_type w) noexcept : u(u), v(v), cost(w) {}

        inline size_type to(const size_type from) const noexcept {
            dev_assert(from == this->u or from == this->v);
            return from == this->u ? this->v : this->u;
        }
    };


  private:
    std::vector<edge> _edges;
    std::vector<std::vector<size_type>> _adjacencies;

  public:
    graph(const size_type v = 0) noexcept : _adjacencies(v) {}

    inline size_type size() const noexcept { return this->_adjacencies.size(); }

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
            this->G.add_edge(u-1, v-1, w);
        }
    }
};


struct evaluator {
  private:
    const input* _in;

  public:
    const std::vector<std::vector<cost_type>> initial_costs;

    evaluator(const input* in) noexcept : _in(in), initial_costs(in->G.compute_cost_matrix()) {}

    score_type compute_score(const std::vector<day_type> schedule) const noexcept {
        std::vector<std::unordered_set<size_type>> ignored_edges(this->_in->D);

        for(size_type e=0; e<this->_in->E; ++e) ignored_edges[schedule[e]].emplace(e);

        score_type sum = 0;

        for(day_type d=0; d<this->_in->D; ++d) {
            auto costs = this->_in->G.compute_cost_matrix(ignored_edges[d]);

            for(size_type i=0; i<this->_in->V; ++i) for(size_type j=i+1; j<this->_in->V; ++j) {
                dev_assert(costs[i][j] == costs[j][i]);
                dev_assert(this->initial_costs[i][j] == this->initial_costs[j][i]);

                sum += costs[i][j] - this->initial_costs[i][j];
            }
        }

        return sum;
    }

    score_type to_display_score(const score_type score) const noexcept {
        return score * 2000 / (this->_in->D * this->_in->V * (this->_in->V - 1));
    }
};


} // namespace lib

lib::random_engine<lib::xorshift> rnd;



signed main() {
    lib::input in(&std::cin);
    lib::evaluator evaluator(&in);

    lib::timer timer(5500);

    std::vector<lib::day_type> solution;
    lib::score_type min_score = std::numeric_limits<lib::score_type>::max();

    lib::timer::time unit_time = 0;

    while(timer.remaining() >= unit_time) {
        lib::timer time_count;

        std::vector<lib::day_type> days;
        days.reserve(in.D * in.K);

        for(lib::day_type d=0; d<in.D; ++d) {
            for(lib::day_type k=0; k<in.K; ++k) {
                days.push_back(d);
            }
        }

        std::shuffle(days.begin(), days.end(), rnd);


        lib::score_type score = evaluator.compute_score(days);
        debug(score);

        if(score < min_score) {
            min_score = score;
            solution = std::move(days);
        }

        auto time = time_count.elapsed();
        if(time > unit_time) unit_time = time;
    }

    for(lib::size_type e=0; e<in.E; ++e) {
        std::cout << solution[e] + 1 << " ";
    }
    std::cout << std::endl;

    debug(min_score, evaluator.to_display_score(min_score));

    return EXIT_SUCCESS;
}
