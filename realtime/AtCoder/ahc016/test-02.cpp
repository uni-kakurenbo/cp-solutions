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

#include "template.hpp"
#include "numeric/matrix.hpp"

struct Graph;
struct Solver;

std::mt19937 random_engine(998244353);

struct Tuner {
  protected:
    int M;
    double eps;
    std::normal_distribution<int> distr_s;

  public:
    Tuner(const int M, const double eps) : M(M), eps(eps), distr_s(0, M-1) {}

    template<class E> int test(const int times = 1) {
        E solver(this->M, this->eps);
        const int N = solver.vertrexes();

        std::vector<Graph> G(this->M);
        REP(k, this->M) G[k] = solver.generate(k);

        int err = 0;
        LOOP(times) {
            REP(s, this->M) {
                const int t = solver.predict(s);
                if(s != t) ++err;
            }
        }

        return 1000000 * std::pow(0.9 * err) / N;
    }
};

signed main() {
}
