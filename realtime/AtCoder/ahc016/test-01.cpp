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

template<class T>
struct BinomialTable : Lib::ValMatrix<T> {
    BinomialTable(const int N) : Lib::ValMatrix<T>(N+1, N+1) {
        FOR(i, 0, N) FOR(j, 0, i) {
            if(j == 0 or j == i) (*this)(i,j) = 1;
            else (*this)(i,j) = (*this)(i-1,j-1) + (*this)(i-1,j);
        }
    }
};

template<class T> T pow(T x, int n) {
    T res = 1;
    while(n>0) {
        if(n & 1) res *= x;
        x *= x;
        n >>= 1;
    }
    return res;
}

std::mt19937 random_engine(998244353);

struct Tuner {
  protected:
    int M;
    double eps;

  public:
    Tuner(const int M, const double eps) : M(M), eps(eps) {}

//   protected:
    int edges_base_best(int *res) const {
        static const BinomialTable<double> binom(100);
        FOR(n, 1, 100) {
            const int range = (int)binom(n,2) / this->M;
            if(range < 1) continue;
            debug(std::ceil((int)binom(n,2) * this->eps) + 1, std::floor(range));
            if(std::ceil((int)binom(n,2) * this->eps) + 1 <= std::floor(range)) {
                *res = n;
                return 1000000000 / n;
            }
        }
        return -1;
    }

    int degrees_base_best(int *res) const {
        FOR(n, this->M, 100) {
            REP(k, this-M) {
                const int diff = std::max(n-k-1, k-1);
                if(diff <)
            }
            return -1;
        }
    }
};

signed main() {
    int M; double eps;
    std::cin >> M >> eps;
    Tuner tuner(M, eps);
    int N = -1;
    debug(tuner.edges_base_best(&N));
    debug(N);
}
