/*********************************************
 * 最小二乗法                                *
 *********************************************/
#include <iostream>  // for cout

#include "val_array.hpp"
#include "numeric/matrix.hpp"

class Tuner
{
    int D;
    Lib::ValMatrix<double> a;
    Lib::ValArray<double> s, t;
    double p, d, px;

  public:
    Tuner(const int D) : D(D), a(D+1, D+2), s(2*D+1), t(D+1) {
        FOR(i, 0, 2*D) s[i] = 0;
        FOR(i, 0, D) t[i] = 0;
    };

    double ipow(double x, int n) const {
        double res = 1;
        while(n>0) {
            if(n & 1) res *= x;
            x *= x;
            n >>= 1;
        }
        return res;
    }

    template<class I, class J, class K>
    void approximate(const I x_first, const I x_last, const J y_first, const K res_first) {
        {
            auto itr_x = x_first;
            auto itr_y = y_first;
            for (; itr_x!=x_last; ++itr_x, ++itr_y) {
                FOR(i, 0, 2*D) s[i] += ipow(*itr_x, i);
                FOR(i, 0, D) t[i] += ipow(*itr_x, i) * *itr_y;
            }
        }

        FOR(i, 0, D) {
            FOR(j, 0, D) a(i,j) = s[i + j];
            a(i, D+1) = t[i];
        }

        FOR(k, 0, D) {
            p = a(k,k);
            FOR(j, k, D+1) a(k,j) /= p;
            FOR(i, 0, D) {
                if (i == k) continue;
                d = a(i,k);
                FOR(j, k, D+1) a(i,j) -= d * a(k,j);
            }
        }

        {
            auto itr_res = res_first;
            for(int k=0; k<=D; ++k, ++itr_res) *itr_res = a(k,D+1);
        }
    }
};

int main() {
    Tuner tuner(5);

    double x[] = {-3, -2, -1,  0, 1, 2, 3};
    double y[] = { 5, -2, -3, -1, 1, 4, 5};

    tuner.approximate(x, x+7, y);

    return 0;
}
