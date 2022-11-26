/*********************************************
 * 最小二乗法                                *
 *********************************************/
#include <iostream>
#include <string>
#include <valarray>
#include <algorithm>
#include <cmath>
#include <cassert>
#include <numeric>


#include "val_array.hpp"
#include "numeric/matrix.hpp"
#include "iterable/accumulation.hpp"

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
    F min = 1e100;
    T res = 0;
    {
        T index = 0;
        for(I itr=first; itr != last; ++itr, ++index, sum0 += *itr, prod_sum0 += index**itr) {
            T sum1 = sum_all - sum0;
            if(sum0 <= 0 or sum1 <= 0) continue;
            T prod_sum1 = prod_sum_all - prod_sum0;
            F ave0 = (F)prod_sum0 / sum0;
            F ave1 = (F)prod_sum1 / sum1;

            F w0 = (F)sum0 / sum_all;
            F w1 = (F)sum1 / sum_all;

            F a0 = 0, a1 = 0;
            {
                T e0 = 0, e1 = 0;
                for(I e=first; e!=itr; ++e ) {
                    e0 += (*e - ave0) * (*e - ave0);
                }
                for(I e=itr; e!=last; ++e ) {
                    e1 += (*e - ave1) * (*e - ave1);
                }
                a0 = (F)e0 / sum0;
                a1 = (F)e1 / sum1;
            }

            F val = w0 * (std::log(a0) - std::log(w0)) + w1 * (std::log(a1) - std::log(w1));
            debug(w0, w1, a0, a1, val);

            if(val <= min) {
                min = val;
                res = index+1;
            }
        }
    }
    return res;
}

int main() {

    // int h[] = { 4, 7, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 21, 30, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    int h[] = { 86,84,81,80,79,78,78,77,77,77,77,76,76,76,76,75,75,75,75,75,75,74,74,74,73,73,73,73,73,73,72,71,71,71,71,70,70,69,69,69,68,68,63,60,58,55,54,54,54,53,53,53,52,52,52,51,51,50,50,50,50,49,49,49,49,49,49,49,49,49,48,48,48,48,48,48,48,48,47,47,47,47,46,46,46,45,45,44,44,44,44,44,43,43,42,42,42,41,41,39 };
    std::reverse(ALL(h));
    int t = binarize(ALL(h));
    debug(t);
    debug(std::reduce(std::begin(h), std::begin(h)+t));

    return 0;
}
