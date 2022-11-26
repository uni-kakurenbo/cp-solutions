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
    int M, V;
    float eps;
    bool specialize = false;

    std::vector<std::valarray<int>> degrees_list;

  public:
    Solver(const int M, const float eps) : M(M), V(100), eps(eps) {
        if(this->eps == 0) {
            this->specialize = true;
            this->V = std::ceil((1.0 + std::sqrt(1.0 + 8*M)) / 2);
            const int E = V*(V-1)/2;
            assert(E >= M);
        }
        else {
            this->degrees_list.resize(this->M);
        }
    }

    int vertexes() const { return this->V; }

    std::string generate(const int id) {
        debug(id);
        if(this->specialize) {
            const int E = this->V*(this->V-1)/2;
            return std::string(id, '1') + std::string(E-id, '0');
        }
        else {
            const int p = this->M;
            Graph G(this->V);
            REP(i, id) {
                LOOP(p) {
                    int j = -1;
                    do { j = engine() % this->V; } while(i == j);
                    G.add_edge(std::min(i,j), std::max(i,j));
                }
            }
            this->degrees_list[id] = G.degrees();
            std::sort(ALL(this->degrees_list[id]));
            debug(this->degrees_list[id]);
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
            // debug(degrees);

            int min_diff = 1 << 30;
            int res = 0;
            REP(id, this->M) {
                std::valarray<int> diff = degrees - this->degrees_list[id];
                diff = diff.apply([](int x) { return x*x; } );
                const int diff_sum = diff.sum();
                if(diff_sum < min_diff) {
                    min_diff = diff_sum;
                    res = id;
                }
            }

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
        std::string H; std::cin >> H;
        std::cout << solver.predict(H) << std::endl;
    }

    return 0;
}
