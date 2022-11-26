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
    F max = 0.0;
    T res = 0;
    {
        T index = 0;
        for(I itr=first; itr != last; ++itr, ++index, sum0 += *itr, prod_sum0 += index**itr) {
            T sum1 = sum_all - sum0;
            if(sum0 <= 0 or sum1 <= 0) continue;
            T prod_sum1 = prod_sum_all - prod_sum0;
            F m0 = (F)prod_sum0 / sum0;
            F m1 = (F)prod_sum1 / sum1;
            F val = sum0 * sum1 * (m0 - m1) * (m0 - m1);
            if(val >= max) {
                max = val;
                res = index+1;
            }
        }
    }
    return res;
}

int main() {

    int h[] = { 4, 7, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 21, 30, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    std::reverse(ALL(h));
    int t = binarize(ALL(h));
    debug(t);
    debug(std::reduce(std::begin(h), std::begin(h)+t));

    return 0;
}
