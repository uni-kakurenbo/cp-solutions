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

#include "template.hpp"

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
        if(this->has_edge(i, j)) return;
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

constexpr int QUERIES = 100;

signed main() {
    int V; std::cin >> V;

    REP(k, V) {
        Graph G(V/2+1);

        REP(i, (k+1)/2) {
            REPF(j, i+1, (k+1)/2) {
                if(k >= 50 and k%2 and i==0 and j%2) continue;
                G.add_edge(i, j);
            }
        }
        if(k < G.size()) {
            REP(i, (k+1)/2) {
                REPF(j, (k+1)/2, G.size()) {
                    if(k%2 and i==0 and j%2) continue;
                    G.add_edge(i, j);
                }
            }
        }

        debug(k, G.degrees());
    }

    return 0;
}
