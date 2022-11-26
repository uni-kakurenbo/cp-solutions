/*
 * @uni_kakurenbo
 * https://github.com/uni-kakurenbo/competitive-programming-workspace
 *
 * CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja
 */
/* #language C++ GCC */
/* #region template */
#include "template.hpp"
#include "output.hpp"

Output _print;
#define print _print
/* #endregion */

#include <iostream>
#include <string>
#include <valarray>
#include <algorithm>
#include <cmath>
#include <random>

#include <atcoder/dsu>

#include "iterable/counter.hpp"
#include "iterable/adjacent_difference.hpp"

struct Graph {
  protected:
    int V;
    int E;
    std::valarray<bool> _data;
    std::valarray<int> _degrees;

    inline int pair_tp_id(const int i, const int j) const {
        assert(0 <= i and i < j and j < this->V);
        return this->E - (this->V - i)*(this->V - i - 1)/2 + j - i - 1;
    }

  public:
    Graph(const int V = 0) : V(V), E(V*(V-1)/2) { _data.resize(this->E, 0), _degrees.resize(this->V, 0); }

    int size() const { return this->V; }

    void add_edge(const int i, const int j) {
        this->_data[this->pair_tp_id(i, j)] = true;
        ++this->_degrees[i], ++this->_degrees[j];
    }

    bool has_edge(const int i, const int j) const {
        return this->_data[this->pair_tp_id(i, j)];
    }
    int degree(const int v) const {
        return this->_degrees[v];
    }
    auto degrees() const { return this->_degrees; }

    void from_string(const std::string &H) {
        int i = 0, j = 1;
        ITR(h, H) {
            if(h == '1') this->add_edge(i, j);
            ++j;
            if(j >= this->V) {
                ++i;
                j = i+1;
            }
        }
    }

    std::string to_string() const {
        std::string res;
        REP(i, this->V) REPF(j, i+1, this->V) {
            res += this->_data[this->pair_tp_id(i, j)] ? "1" : "0";
        }
        assert((int)res.size() == this->E);
        return res;
    }
};

std::mt19937 engine(998244353);

struct Solver {
  protected:
    int M;
    float eps;
    int V;
    bool specialize = false;
    int threshold = -1;

    constexpr static int BOOST_SIZE = 3;
    int boost_min = 101, boost_max = -1;
    int boost_count = 0;

    std::valarray<int> degrees_sums;
    std::valarray<int> lower_boundaries;

  public:
    Solver(const int M, const float eps) : M(M), eps(eps) {
        if(this->eps == 0) {
            this->specialize = true;
            this->V = std::ceil((1.0 + std::sqrt(1.0 + 8*M)) / 2);
            const int E = V*(V-1)/2;
            assert(E >= M);
        }
        else {
            this->V = this->M;// + 1/eps;

            if(this->eps >= 0.18) chmax(this->V, 70);
            if(this->eps >= 0.20) chmax(this->V, 80);
            if(this->eps >= 0.22) chmax(this->V, 90);
            if(this->eps >= 0.24) chmax(this->V, 100);

            this->V = std::clamp(this->V, 1, 100);

            this->degrees_sums.resize(this->V);
            this->lower_boundaries.resize(this->M);

            this->threshold = this->V / 2;
            debug(this->M, this->V, this->threshold);

            if constexpr (BOOST_SIZE > 0) {
                const int can_boost = (this->V - this->M) / (2 * BOOST_SIZE);

                if(can_boost > 0) {
                    this->boost_min = this->M/2 - can_boost/2;
                    this->boost_max = this->M/2 + can_boost/2;
                }

                debug(can_boost, this->boost_min, this->boost_max);
            }
        }
    }

    int vertexes() const { return this->V; }

    std::string generate(const int _k) {
        int k = _k;
        if(this->specialize) {
            const int E = this->V*(this->V-1)/2;
            return std::string(k, '1') + std::string(E-k, '0');
        }
        else {
            // if(this->boost_min <= k and k < this->boost_max) {
            //     this->boost_count = this->boost_max;
            //     // this->boost_count += 2 * BOOST_SIZE;
            //     // k += boost_count - BOOST_SIZE;
            //     // this->lower_boundaries[_k] = k - BOOST_SIZE;
            //     k += boost_count;
            //     this->lower_boundaries[_k] = k;
            // }
            // else {
            //     k += boost_count;
            //     this->lower_boundaries[_k] = k;
            // }
            k += this->boost_count;
            this->lower_boundaries[_k] = k;
            debug(_k, k, this->lower_boundaries[_k]);

            Graph G(this->V);

            REP(i, k) {
                REPF(j, i+1, k) G.add_edge(i, j);
            }
            if(k <= this->threshold) {
                REP(i, k) {
                    REPF(j, k, G.size()) G.add_edge(i, j);
                }
            }

            auto degrees = G.degrees();
            debug(degrees);
            this->degrees_sums[k] = degrees.sum();
            // debug(k, this->degrees_sums[k]);
            debug(degrees.max() - degrees.min());

            if(k != 0 and degrees.max() - degrees.min() < 70) {
                this->boost_count = this->V - k;
            }

            return G.to_string();
        }
    }

    int predict(const std::string &H) const  {
        if(this->specialize) {
            return std::min(this->M-1, (int)std::count(ALL(H), '1'));
        }
        else {
            Graph G(this->V);
            G.from_string(H);

            auto degrees = G.degrees();
            std::sort(ALL(degrees));
            std::reverse(ALL(degrees));
            debug(degrees, degrees.sum());

            Lib::AdjacentDifference<int> diff(std::begin(degrees), std::end(degrees), false);
            debug(diff);

            const auto max_deg = std::max_element(ALL(degrees));
            const auto diff_min = std::min_element(ALL(diff));

            int boundary = *max_deg <= 6 ? 0 : diff_min - std::begin(diff);
            if(degrees.sum() - this->degrees_sums[boundary] < -5000)  boundary = 0;
            debug(boundary, degrees.sum(), this->degrees_sums[boundary]);

            const int res = std::lower_bound(ALL(this->lower_boundaries), boundary) - std::begin(this->lower_boundaries);
            // const int res = boundary;
            debug(res);
            return std::clamp(res, 0, this->M-1);
        }
    }
};

constexpr int QUERIES = 100;

signed main() {
    int M; std::cin >> M;
    float eps; std::cin >> eps;

    Solver solver(M, eps);

    std::cout << solver.vertexes() << std::endl;
    REP(i, M) {
        std::cout << solver.generate(i) << std::endl;
    }

    REP(i, QUERIES) {
        debug(i);
        std::string H; std::cin >> H;
        std::cout << solver.predict(H) << std::endl;
    }

    return 0;
}
