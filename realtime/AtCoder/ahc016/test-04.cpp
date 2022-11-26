/*
 * @uni_kakurenbo
 * https://github.com/uni-kakurenbo/competitive-programming-workspace
 *
 * CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja
 */
/* #language C++ GCC */

#include <iostream>
#include <string>
#include <valarray>
#include <algorithm>
#include <cmath>
#include <cassert>
#include <numeric>
#include <random>
#include <map>

#include "template.hpp"
#include "numeric/matrix.hpp"

struct Graph {
  protected:
    int V;
    int E;
    std::valarray<bool> _data;
    std::valarray<int> _degrees;

    inline int pair_tp_id(const int i, const int j) const {
        assert(0 <= i and i < j and j < this->V);
        return this->E - (this->V - i) * (this->V - i - 1) / 2 + j - i - 1;
    }

  public:
    Graph(const int V = 0) : V(V), E(V*(V-1)/2) { _data.resize(this->E, 0), _degrees.resize(this->V, 0); }

    int size() const { return this->V; }

    void add_edge(const int i, const int j) {
        assert(not this->has_edge(i, j));
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

struct Solver;

void list_pattern(const int V, std::map<std::vector<int>,std::string> *res) {
    const int E = V*(V-1)/2;
    REP(mask, 1 << E) {
        std::string s;
        REP(i, E) s += (mask & (1 << i)) ? '1' : '0';
        Graph G(V);
        G.from_string(s);
        auto _degs = G.degrees();
        std::vector<int> degs(ALL(_degs));
        std::sort(ALL(degs));
        (*res)[degs] = s;
    }
    return;
};

signed main() {
    int n; std::cin >> n;
    std::map<std::vector<int>,std::string> ans;

    list_pattern(n, &ans);

    debug(ans.size(), ans);

    return 0;
}
