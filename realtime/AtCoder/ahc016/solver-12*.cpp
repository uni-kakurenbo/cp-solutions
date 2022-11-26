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

struct Solver {
  private:
    std::string note = "#v";

  protected:
    int M;
    float eps;
    int V;
    bool specialize = false, tripartite = false;
    int threshold = -1;
    int trim_size = 0, trim_begin = 101;
    bool unuse0 = 0;

    std::valarray<int> degrees_sums;

  public:
    Solver(const int M, const float eps) : M(M), eps(eps), degrees_sums(0, 200) {
        if(this->eps <= 0.005) {
            this->specialize = true;
            this->V = std::ceil((1.0 + std::sqrt(1.0 + 8*M)) / 2);
            const int E = V*(V-1)/2;
            assert(E >= M);
        }
        else {
            if(false and this->M < 100) {
                this->unuse0 = true;
                this->tripartite = true;
                this->V = this->M / 2 + 2;

                this->threshold = this->V / 2;
            }
            else {
                this->V = this->M;

                if(this->M < 100) this->unuse0 = true;
                ++this->V;

                if(this->eps >= 0.18) chmax(this->V, 70);
                if(this->eps >= 0.20) chmax(this->V, 80);
                if(this->eps >= 0.22) chmax(this->V, 90);
                if(this->eps >= 0.24) chmax(this->V, 100);

                this->V = std::clamp(this->V, 1, 100);

                this->threshold = this->V / 2;

                this->trim_size = this->V - this->M - this->unuse0;
                this->trim_begin = this->threshold - trim_size / 2;
            }
        }

        debug(this->M, this->V, this->threshold);
        debug(this->trim_size, this->trim_begin);

        REP(i, this->V) this->note += " ", this->note += std::to_string(i);
    }

    int vertexes() const { return this->V; }

    std::string generate(const int _k) {
        int k = _k + this->unuse0;
        if(this->specialize) {
            const int E = this->V*(this->V-1)/2;
            return std::string(k, '1') + std::string(E-k, '0');
        }

        Graph G(this->V);
        if(this->tripartite) {
            REP(i, (k+1)/2) {
                REPF(j, i+1, (k+1)/2) {
                    if((k+1)/2 >= this->threshold and k%2 and i==0 and j%2) continue;
                    G.add_edge(i, j);
                }
            }
            if((k+1)/2 < this->threshold) {
                REP(i, (k+1)/2) {
                    REPF(j, (k+1)/2, G.size()) {
                        if(k%2 and i==0 and j%2) continue;
                        G.add_edge(i, j);
                    }
                }
            }
        }
        else {
            if(this->trim_begin <= _k) {
                k += this->trim_size;
            }
            debug(_k, k);

            REP(i, k) {
                REPF(j, i+1, k) G.add_edge(i, j);
            }
            if(k <= this->threshold) {
                REP(i, k) {
                    REPF(j, k, G.size()) G.add_edge(i, j);
                }
            }
        }

        auto degrees = G.degrees();
        debug(degrees);
        this->degrees_sums[k] = degrees.sum();
        // debug(k, this->degrees_sums[k]);
        debug(degrees.max() - degrees.min());

        return G.to_string();
    }

    int predict(const std::string &H) const  {
        // std::cout << this->note << std::endl;

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

            std::vector<int> diff(degrees.size());
            std::adjacent_difference(ALL(degrees), diff.begin());
            debug(diff);
            int res = -1;

            if(this->tripartite) {
                std::vector<std::pair<int,int>> diffp(diff.size());
                REP(i, diff.size()) diffp[i] = { diff[i], i };
                std::sort(ALL(diffp));

                if(diffp[0].$S == 1 and std::abs(degrees[0] - this->V/2) <= 3) {
                    res = 1;
                }
                else {
                    if(std::max(diffp[0].$F, diffp[1].$F) <= -3) {
                        res = std::max(diffp[0].$S, diffp[1].$S) * 2 - 1;
                    }
                    else {
                        res = (diffp[0].$F < diffp[1].$F ? diffp[0].$S : diffp[1].$S) * 2;
                    }
                }
            }
            else {

                const auto diff_min = std::min_element(ALL(diff));
                debug(*diff_min);

                const auto diff_min_rm = std::find(RALL(diff), *diff_min);

                res = diff_min_rm.base() - std::begin(diff) - 1;
            }

            debug(res, degrees.sum(), this->degrees_sums[res]);

            if(degrees.sum() - this->degrees_sums[res] < -4000) res = 0;

            res -= this->unuse0;
            if(res >= this->trim_begin) {
                res -= this->trim_size;
            }

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
