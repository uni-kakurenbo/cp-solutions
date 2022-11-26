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


template<class I, class T = typename std::iterator_traits<I>::value_type, class F = double> T binarize(I first, I last) {
    T sum_all = 0;
    T prod_sum_all = 0;
    {
        T index = 0;
        for(I itr=first; itr != last; ++itr, ++index) {
            sum_all += *itr;
            prod_sum_all += index * *itr;
        }
    }

    T sum0 = 0, prod_sum0 = 0;
    F max = 0.0;
    T res = 0;
    {
        T index = 0;
        for(I itr=first; itr != last; sum0 += *itr, prod_sum0 += index**itr, ++itr, ++index) {
            T sum1 = sum_all - sum0;
            if(sum0 <= 0 or sum1 <= 0) continue;
            T prod_sum1 = prod_sum_all - prod_sum0;
            F m0 = (F)prod_sum0 / sum0;
            F m1 = (F)prod_sum1 / sum1;
            F val = sum0 * sum1 * (m0 - m1) * (m0 - m1);
            // debug(val);
            if(val >= max) {
                max = val;
                res = index+1;
            }
        }
    }
    return res;
}

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

struct Solver {
  private:
    std::string note = "#v";

  protected:
    constexpr static double NO_ERROR = 0.001;
    constexpr static double MANY_ERROR = 0.38;
    int M;
    float eps;
    int V;
    int threshold = -1;
    int trim_size = 0, trim_begin = 101;
    bool unuse0 = 0;

    std::valarray<int> degrees_sums;

  public:
    Solver(const int M, const float eps) : M(M), eps(eps) {
        if(this->eps <= NO_ERROR) {
            this->V = std::ceil((1.0 + std::sqrt(1.0 + 8*M)) / 2);
            const int E = V*(V-1)/2;
            assert(E >= M);
            return;
        }
        if(this->eps >= MANY_ERROR) {
            this->V = 4;
            return;
        }

        this->V = this->M;// + 1/eps;

        if(this->M < 100) {
            this->unuse0 = true;
            ++this->V;
        }

        if(this->eps >= 0.10) chmax(this->V, 20);
        if(this->eps >= 0.12) chmax(this->V, 30);
        if(this->eps >= 0.15) chmax(this->V, 40);
        if(this->eps >= 0.18) chmax(this->V, 60);
        if(this->eps >= 0.20) chmax(this->V, 80);
        if(this->eps >= 0.22) chmax(this->V, 90);
        if(this->eps >= 0.24) chmax(this->V, 100);

        this->V = std::clamp(this->V, 1, 100);

        this->degrees_sums.resize(this->V);

        this->threshold = this->V / 2;
        debug(this->M, this->V, this->threshold);

        this->trim_size = this->V - this->M - this->unuse0;
        this->trim_begin = this->threshold - trim_size/2;
        debug(this->unuse0, this->trim_size, this->trim_begin);

        REP(i, this->V) this->note += " ", this->note += std::to_string(i);
    }

    int vertexes() const { return this->V; }

    std::string generate(const int _k) {
        int k = _k + this->unuse0;
        if(this->eps <= NO_ERROR) {
            const int E = this->V*(this->V-1)/2;
            return std::string(k, '1') + std::string(E-k, '0');
        }
        if(this->eps >= MANY_ERROR) {
            const int E = this->V*(this->V-1)/2;
            if(k == 0) return std::string(E, '0');
            return std::string(E, '1');
            // return std::string(E/2, '1') + std::string(E - E/2, '0');
        }

        if(this->trim_begin <= _k) {
            k += this->trim_size;
        }
        debug(_k, k);

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

        return G.to_string();
    }

    int predict(const std::string &H) const  {
        // std::cout << this->note << std::endl;

        if(this->eps <= NO_ERROR) {
            return std::min(this->M-1, (int)std::count(ALL(H), '1'));
        }
        if(this->eps >= MANY_ERROR) {
            const int cnt0 = (int)std::count(ALL(H), '0');
            const int cnt1 = (int)std::count(ALL(H), '1');
            if(cnt0 == cnt1) return 2;
            return cnt0 > cnt1 ? 0 : 1;
            // if(this->cnt0 > 0)
        }

        Graph G(this->V);
        G.from_string(H);

        auto degrees = G.degrees();

        std::sort(ALL(degrees));
        std::reverse(ALL(degrees));
        debug(degrees, degrees.sum());

        {
            std::vector<std::pair<int,int>> test(G.size());
            std::vector<int> rev(G.size());
            auto degs = G.degrees();
            REP(i, test.size()) {
                test[i] = { degs[i], i };
            }
            std::sort(ALL(test));
            std::reverse(ALL(test));
            REP(i, test.size()) {
                rev[test[i].$S] = i;
            }
            debug(test, rev);
            std::cout << "#v ";
            ITR(t, rev) {
                std::cout << t << " ";
            }
            std::cout << std::endl;
        }

        int res = 0;
        if(this->eps < 0.25){
            std::valarray<int> count(G.size());
            REP(i, G.size()) ++count[degrees[i]];
            debug(count);

            std::valarray<int> leveled(G.size());
            leveled[0] = count[0];
            leveled[G.size()-1] = count[G.size()-1];
            REPF(i, 1, G.size()-1) {
                leveled[i] = (count[i-1] + 2*count[i] + count[i+1]);
            }
            debug(leveled);

            const int t = binarize(ALL(leveled));
            debug(t);
            res = std::reduce(std::begin(count) + (t - 1), std::end(count));
        }
        else {
            std::vector<int> diff(degrees.size());

            std::adjacent_difference(ALL(degrees), diff.begin());
            debug(diff);

            auto diff_min = std::begin(diff);
            if(this->unuse0) diff_min++;
            {
                for(int ind=this->unuse0; ind < (int)diff.size(); ++ind) {
                    if(this->trim_begin < ind and ind < this->trim_begin + this->trim_size) continue;

                        if(diff[ind] <= *diff_min) {
                            diff_min = std::begin(diff) + ind;
                        }
                }
            }

            res = diff_min - std::begin(diff);
        }

        // {
        //     std::valarray<int> x(degrees.size());
        //     std::valarray<double> a(13);
        //     std::iota(ALL(x), 0);
        //     Tuner tuner(12);
        //     tuner.approximate(ALL(x), std::begin(degrees), std::begin(a));
        //     fprintf(stderr, "(%.16f)+(%.16f)x+(%.16f)x^2+(%.16f)x^3+(%.16f)x^4+(%.16f)x^5+(%.16f)x^6+(%.16f)x^7+(%.16f)x^8+(%.16f)x^9+(%.16f)x^{10}+(%.16f)x^{11}+(%.16f)x^{12}", a[0], a[1], a[2], a[3], a[4], a[5], a[6], a[7], a[8], a[9], a[10], a[11], a[12]);
        //     debug(a);
        //     res = -a[2] / (3*a[3]);
        //     debug(res);
        // }

        // if(degrees.sum() - this->degrees_sums[res] < -4000)  res = 0;

        debug(res, degrees.sum(), this->degrees_sums[res]);
        res -= this->unuse0;
        if(res >= this->trim_begin) {
            res -= this->trim_size;
        }

        debug(res);

        return std::clamp(res, 0, this->M-1);
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
