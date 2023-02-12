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
#include <algorithm>

#include "random/xorshift.hpp"
#include "random/generator.hpp"


namespace lib {


using size_type = std::int16_t;
using day_type = std::int16_t;

using cost_type = std::int32_t;


struct graph {
    struct edge {
        size_type from, to;
        cost_type cost;

        edge(const size_type u, const size_type v, const cost_type w) : from(u), to(v), cost(w) {}
    };

  private:
    std::vector<edge> _data;

  public:
    inline auto edges() const noexcept { return this->_data; }

    inline void add_edge(const size_type u, const size_type v, const cost_type w) noexcept {
        this->_data.emplace_back(u, v, w);
    }
};


struct input {
    size_type V, E;
    day_type D, K;

    graph G;

    template<class istream> input(istream *const in) noexcept {
        *in >> this->V >> this->E >> this->D >> this->K;
        for(size_type i=0; i<this->E; ++i) {
            size_type u, v; cost_type w;
            *in >> u >> v >> w;
            this->G.add_edge(u, v, w);
        }
    }
};


} // namespace lib

lib::random_engine<lib::xorshift> rnd;

signed main() {
    lib::input in(&std::cin);

    std::vector<lib::day_type> days;
    days.reserve(in.D * in.K);

    for(lib::day_type d=0; d<in.D; ++d) {
        for(lib::day_type k=0; k<in.K; ++k) {
            days.push_back(d);
        }
    }

    std::shuffle(days.begin(), days.end(), rnd);

    for(lib::size_type e=0; e<in.E; ++e) {
        std::cout << days[e] + 1 << " ";
    }
    std::cout << std::endl;

    return EXIT_SUCCESS;
}
