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

#include <atcoder/dsu>

#include "iterable/counter.hpp"

struct Graph {
  protected:
    int V;
    int E;
    std::valarray<bool> data;

    inline int pair_tp_id(const int i, const int j) const {
        assert(0 <= i and i < j and j < this->V);
        return this->E - (this->V - i)*(this->V - i - 1)/2 + j - i - 1;
    }

  public:
    Graph(const int V = 0) : V(V), E(V*(V-1)/2) { data.resize(this->E, 0); }

    int size() const { return this->V; }

    void add_edge(const int i, const int j) {
        data[this->pair_tp_id(i, j)] = true;
    }

    bool has_edge(const int i, const int j) const {
        return data[this->pair_tp_id(i, j)];
    }

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
            res += this->data[this->pair_tp_id(i, j)] ? "1" : "0";
        }
        assert((int)res.size() == this->E);
        return res;
    }
};

struct Solver {
  protected:
    int M, V;
    float eps;

  public:
    Solver(const int M, const float eps) : M(M), V(M), eps(eps) {
        if(eps == 0) {
            this->V = std::ceil((1.0 + std::sqrt(1.0 + 8*M)) / 2);
            const int E = V*(V-1)/2;
            assert(E >= M);
        }
    }

    int vertexes() const { return this->V; }

    std::string generate(const int id) const {
        debug(id);
        if(this->eps == 0) {
            const int E = this->V*(this->V-1)/2;
            return std::string(id, '1') + std::string(E-id, '0');
        }
        else {
            Graph G(this->V);
            REP(i, id) REPF(j, i+1, id) G.add_edge(i, j);
            return G.to_string();
        }
    }

    int predict(const std::string &H) const  {
        if(eps == 0) {
            return std::min(this->M-1, (int)std::count(ALL(H), '1'));
        }
        else {
            Graph G(this->V);
            G.from_string(H);

            std::vector<int> direct_path_cnts(1);

            REP(i, G.size()) {
                REP(j, G.size()) {
                    if(i == j) continue;
                    if(G.has_edge(std::min(i, j), std::max(i, j))) {
                        (*direct_path_cnts.rbegin())++;
                    }
                }
                if(direct_path_cnts.back() > 0) direct_path_cnts.push_back(0);
            }

            Lib::Counter<int> count(ALL(direct_path_cnts));
            debug(count);
            int res = std::max_element(ALL(count), [](auto &a, auto &b) { return a.$S < b.$S; })->$F;
            debug(res);

            return std::clamp(res+1, 0, this->M-1);
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
